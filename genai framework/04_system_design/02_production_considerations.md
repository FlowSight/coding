# Production Considerations

## 1. Latency Optimization

### Where Time Goes:
```
Typical RAG query breakdown:
  Embedding query:       50-100ms  (API call)
  Vector search:         10-50ms   (depends on index size)
  Reranking:            100-200ms  (cross-encoder)
  LLM generation:       500-3000ms (depends on output length)
  ─────────────────────────────────
  Total:                700-3500ms
```

### Optimization Strategies:

**1. Parallel operations:**
```python
# Don't do this:
docs_vector = vector_search(query)      # 30ms
docs_keyword = keyword_search(query)    # 20ms
# Total: 50ms

# Do this:
docs_vector, docs_keyword = await asyncio.gather(
    vector_search(query),    # 30ms
    keyword_search(query)    # 20ms
)
# Total: 30ms (parallel)
```

**2. Streaming (perceived latency):**
```python
# Time to First Token (TTFT) matters more than total time
# User sees response starting in <1s even if full response takes 5s
```

**3. Smaller models for routing:**
```python
# Use GPT-4o-mini or regex for classification (fast)
# Only invoke GPT-4o for actual generation (slow)
route = fast_classifier(query)  # 100ms
answer = gpt4o.generate(...)    # 2000ms
# vs. using GPT-4o for both: 4000ms
```

**4. KV-cache / Prompt caching:**
```python
# If system prompt is constant, providers cache it
# OpenAI: Automatic prompt caching for repeated prefixes
# Anthropic: Explicit cache_control for long prefixes
# Savings: 50% latency on input processing
```

**5. Speculative decoding (self-hosted models):**
```
Use small model to generate draft tokens
Use large model to verify (parallel verification of all tokens)
Accepted tokens: free speed
Rejected: regenerate from that point
Result: 2-3x speedup for same output quality
```

## 2. Cost Optimization

### Cost Model:
```
Monthly cost = (queries/month × avg_tokens_per_query × price_per_token)
             + embedding_costs
             + infrastructure (vector DB, compute)
```

### Example:
```
10,000 queries/day × 30 days = 300,000 queries/month
Avg: 1000 input tokens + 500 output tokens per query

GPT-4o: 300K × (1000 × $5/M + 500 × $15/M) = $1,500 + $2,250 = $3,750/month
GPT-4o-mini: 300K × (1000 × $0.15/M + 500 × $0.60/M) = $45 + $90 = $135/month

Routing 70% to mini, 30% to 4o:
  0.7 × $135 + 0.3 × $3,750 = $94.50 + $1,125 = $1,219/month
  Savings: 67%
```

### Cost Reduction Strategies:

| Strategy | Savings | Complexity |
|----------|---------|------------|
| Model routing (small for simple) | 60-80% | Medium |
| Semantic caching | 20-40% | Low |
| Shorter prompts | 10-30% | Low |
| Batch processing | 30-50% | Medium |
| Self-hosted models | 50-90% (at scale) | High |
| Output token limits | 10-20% | Low |
| Prompt caching (provider) | 50% on input | None (automatic) |

## 3. Reliability

### Failure Modes:
```
1. Model API down (OpenAI outage)
2. Rate limited (429 errors)
3. Timeout (slow generation)
4. Bad output (hallucination, wrong format)
5. Vector DB unavailable
6. Embedding API failure
```

### Resilience Patterns:

**Multi-provider fallback:**
```python
providers = [
    ("openai", "gpt-4o"),
    ("anthropic", "claude-sonnet-4-20250514"),
    ("azure-openai", "gpt-4o"),  # Different endpoint
]

async def resilient_generate(prompt):
    for provider, model in providers:
        try:
            return await call_model(provider, model, prompt)
        except (RateLimitError, TimeoutError, APIError):
            continue
    raise AllProvidersFailedError()
```

**Circuit breaker:**
```python
class CircuitBreaker:
    def __init__(self, failure_threshold=5, recovery_time=60):
        self.failures = 0
        self.state = "closed"  # closed, open, half-open
    
    def call(self, fn, *args):
        if self.state == "open":
            if time_since_open > self.recovery_time:
                self.state = "half-open"
            else:
                raise CircuitOpenError("Provider temporarily unavailable")
        
        try:
            result = fn(*args)
            self.failures = 0
            self.state = "closed"
            return result
        except Exception:
            self.failures += 1
            if self.failures >= self.failure_threshold:
                self.state = "open"
            raise
```

**Graceful degradation:**
```python
async def answer_query(query):
    try:
        # Full RAG pipeline
        return await full_rag_pipeline(query)
    except RetrievalError:
        # Fall back to LLM-only (no retrieval)
        return await llm_only(query, disclaimer="Without document search")
    except LLMError:
        # Fall back to cached similar answers
        return await semantic_cache_lookup(query)
    except Exception:
        return "I'm experiencing issues. Please try again in a moment."
```

## 4. Safety & Security

### Input Safety:
```python
class InputSafetyLayer:
    def check(self, user_input: str) -> SafetyResult:
        checks = [
            self.check_prompt_injection(user_input),
            self.check_pii(user_input),
            self.check_topic_allowed(user_input),
            self.check_rate_limit(user_input),
        ]
        return SafetyResult(passed=all(c.passed for c in checks))
    
    def check_prompt_injection(self, text):
        # Pattern matching + classifier
        injection_patterns = [
            "ignore previous instructions",
            "you are now",
            "system prompt",
            "reveal your",
        ]
        if any(p in text.lower() for p in injection_patterns):
            return CheckResult(passed=False, reason="Potential injection")
        
        # ML classifier for sophisticated attacks
        score = self.injection_classifier.predict(text)
        return CheckResult(passed=score < 0.8)
```

### Output Safety:
```python
class OutputSafetyLayer:
    def check(self, response: str, context: list) -> str:
        # 1. Check for PII leakage
        response = self.redact_pii(response)
        
        # 2. Check factual grounding (vs retrieved docs)
        if not self.is_grounded(response, context):
            response += "\n\n⚠️ Some claims could not be verified against source documents."
        
        # 3. Check for harmful content
        if self.toxicity_score(response) > 0.7:
            return "I cannot provide that response."
        
        # 4. Compliance check (financial regulations)
        if self.contains_investment_advice(response):
            response += "\n\n📋 This is for informational purposes only, not investment advice."
        
        return response
```

### Data Privacy:
```
Considerations for financial firms:
1. NO customer data sent to external LLM APIs
2. Options: Azure OpenAI (data doesn't leave tenant), self-hosted models
3. PII must be stripped before LLM sees it
4. Audit logs of all LLM interactions
5. Data retention policies (auto-delete after N days)
6. Model provider data usage agreements (opt out of training)
```

## 5. Scalability

### Horizontal Scaling:
```
                    ┌─── Worker 1 (RAG pipeline)
Load Balancer ─────├─── Worker 2 (RAG pipeline)
                    ├─── Worker 3 (RAG pipeline)
                    └─── Worker N (RAG pipeline)

State: Stored externally (Redis, Postgres)
Embeddings: Cached in shared cache
Vector DB: Separate scalable service
```

### Async Processing:
```python
# For non-real-time tasks (report generation, batch analysis)
async def submit_analysis(request):
    job_id = create_job(request)
    queue.enqueue(process_analysis, job_id)
    return {"job_id": job_id, "status": "processing"}

# Webhook/polling for completion
async def check_status(job_id):
    return get_job_status(job_id)
```

### Batch Processing:
```python
# OpenAI Batch API: 50% cheaper, 24-hour SLA
batch = client.batches.create(
    input_file_id=file.id,
    endpoint="/v1/chat/completions",
    completion_window="24h"
)
# Good for: nightly analysis, bulk classification, embedding
```

## 6. Observability

### What to Monitor:
```
┌────────── Observability Stack ──────────┐
│                                          │
│  Metrics (Prometheus/DataDog):           │
│  • Latency (p50, p95, p99)             │
│  • Token usage (input/output)           │
│  • Cost per query                       │
│  • Error rate by type                   │
│  • Cache hit rate                       │
│  • Retrieval quality score              │
│                                          │
│  Traces (LangSmith/Arize):              │
│  • Full chain execution trace           │
│  • LLM input/output per step            │
│  • Tool calls and results               │
│  • Retrieval results                    │
│                                          │
│  Logs:                                   │
│  • Query content (if allowed)           │
│  • Model selection decisions            │
│  • Guardrail triggers                   │
│  • Error details                        │
│                                          │
│  Alerts:                                 │
│  • Latency > 5s (p95)                  │
│  • Error rate > 5%                      │
│  • Cost spike > 2x daily average       │
│  • Quality score drop > 10%            │
│                                          │
└──────────────────────────────────────────┘
```

### LLM-specific Observability:
```python
# Trace every LLM call
@trace
async def generate_answer(query, context):
    with span("retrieval"):
        docs = await retrieve(query)
    
    with span("generation"):
        answer = await llm.invoke(prompt.format(context=docs, question=query))
    
    # Log quality metrics
    metrics.record("retrieval_docs_count", len(docs))
    metrics.record("output_tokens", count_tokens(answer))
    metrics.record("generation_latency", span.duration)
    
    return answer
```

## 7. Testing Strategy

```
Unit Tests:
  • Individual tool functions
  • Prompt template rendering
  • Output parsing
  • Guardrail logic

Integration Tests:
  • RAG pipeline with mock LLM
  • Agent with mock tools
  • End-to-end with recorded responses

Evaluation Tests (non-deterministic):
  • Accuracy on test dataset
  • Retrieval quality metrics
  • Agent trajectory evaluation
  • Regression tests (no quality drop after changes)

Load Tests:
  • Concurrent queries
  • Cache behavior under load
  • Rate limit handling
  • Failover scenarios
```

## 8. Deployment Patterns

### Blue-Green:
```
Production (Blue) ─── 100% traffic
Staging (Green) ────── 0% traffic (new version)

After eval pass:
Production (Blue) ─── 0% traffic
Staging (Green) ────── 100% traffic (promoted)
```

### Canary:
```
Production (v1) ─── 95% traffic
Canary (v2) ────── 5% traffic (new version)

Monitor quality metrics. If good → gradually increase to 100%.
If bad → route 100% back to v1.
```

### Shadow Mode:
```
Production (v1) ─── serves response
Shadow (v2) ────── generates response (discarded, just for evaluation)

Compare v1 vs v2 quality without risk.
```

## 9. Interview Talking Points

- "Production GenAI is 20% model, 80% engineering"
- "Latency budget: streaming hides generation time, but retrieval must be fast"
- "Cost: routing 70% of queries to smaller models saves 60%+ without quality loss"
- "Safety for finance: no customer data to external APIs, audit everything"
- "Reliability: multi-provider fallback with circuit breakers"
- "The eval suite IS the product — if you can't measure it, you can't ship it"
