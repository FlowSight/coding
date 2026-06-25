# GenAI Architecture Patterns

## 1. Reference Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                      Client Layer                             │
│  (Web App, Mobile App, API consumers, Internal Tools)        │
└─────────────────────────────┬───────────────────────────────┘
                              │
┌─────────────────────────────▼───────────────────────────────┐
│                    API Gateway / Load Balancer                │
│  (Rate limiting, auth, request routing)                      │
└─────────────────────────────┬───────────────────────────────┘
                              │
┌─────────────────────────────▼───────────────────────────────┐
│                   Orchestration Layer                         │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐  │
│  │  Router  │  │  Chain   │  │  Agent   │  │  Guard   │  │
│  │          │  │  Engine  │  │  Runtime │  │  Rails   │  │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘  │
└─────────────────────────────┬───────────────────────────────┘
                              │
┌─────────────────────────────▼───────────────────────────────┐
│                    Model Layer                                │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐                  │
│  │  GPT-4o  │  │  Claude  │  │  Llama   │  (model pool)   │
│  │  (complex)│  │  (long)  │  │  (fast)  │                  │
│  └──────────┘  └──────────┘  └──────────┘                  │
└─────────────────────────────┬───────────────────────────────┘
                              │
┌─────────────────────────────▼───────────────────────────────┐
│                    Data Layer                                 │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐  │
│  │  Vector  │  │  Cache   │  │  Doc     │  │  Feature │  │
│  │  Store   │  │  (Redis) │  │  Store   │  │  Store   │  │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘  │
└─────────────────────────────────────────────────────────────┘
```

## 2. Pattern: RAG Service

The most common production GenAI pattern.

```
┌──────────────────── Ingestion Pipeline ─────────────────────┐
│                                                              │
│  Sources → Extract → Chunk → Embed → Store                  │
│  (S3,API)  (parsers)  (split)  (model)  (vector DB)        │
│                                                              │
│  + Metadata enrichment                                       │
│  + Deduplication                                             │
│  + Quality filtering                                         │
└──────────────────────────────────────────────────────────────┘

┌──────────────────── Query Pipeline ──────────────────────────┐
│                                                              │
│  Query → Preprocess → Retrieve → Rerank → Generate → Post  │
│          (rewrite,    (vector+   (cross   (LLM +    (cite, │
│           classify)    keyword)   encoder)  prompt)   filter)│
│                                                              │
└──────────────────────────────────────────────────────────────┘
```

### Production RAG Architecture:
```python
class ProductionRAG:
    def __init__(self):
        self.cache = SemanticCache(threshold=0.95)
        self.router = QueryRouter()
        self.retriever = HybridRetriever(vector_store, bm25_index)
        self.reranker = CrossEncoderReranker()
        self.generator = ChatOpenAI(model="gpt-4o")
        self.guardrails = OutputGuardrails()
    
    async def answer(self, query: str, user_context: dict) -> Response:
        # 1. Cache check
        cached = self.cache.get(query)
        if cached:
            return cached
        
        # 2. Route (simple lookup vs complex analysis)
        route = self.router.classify(query)
        
        # 3. Retrieve (with user-specific filters)
        docs = await self.retriever.search(
            query, 
            filters={"access_level": user_context["role"]}
        )
        
        # 4. Rerank
        docs = self.reranker.rerank(query, docs, top_k=5)
        
        # 5. Generate
        answer = await self.generator.generate(query, docs)
        
        # 6. Guardrails (PII, accuracy, safety)
        answer = self.guardrails.check(answer, docs)
        
        # 7. Cache and return
        self.cache.set(query, answer)
        return answer
```

## 3. Pattern: Model Router

Route queries to the optimal model based on complexity/cost.

```
┌─────────┐     ┌─────────────┐     ┌──────────────────┐
│  Query  │────▶│   Router    │────▶│  GPT-4o ($$$)    │ Complex
└─────────┘     │  (classifier │     │  Claude ($$$)    │ reasoning
                │   or rules)  │     └──────────────────┘
                │              │     ┌──────────────────┐
                │              │────▶│  GPT-4o-mini ($) │ Simple tasks
                │              │     │  Llama 3 8B ($)  │
                └─────────────┘     └──────────────────┘
```

```python
class ModelRouter:
    def route(self, query: str) -> str:
        complexity = self.estimate_complexity(query)
        
        if complexity == "simple":
            return "gpt-4o-mini"  # Fast, cheap
        elif complexity == "medium":
            return "gpt-4o"  # Good balance
        elif complexity == "complex":
            return "gpt-4o"  # Best reasoning
        elif complexity == "long_context":
            return "claude-3.5-sonnet"  # 200K context
    
    def estimate_complexity(self, query: str) -> str:
        # Rules-based or classifier
        if len(query.split()) < 10 and "?" in query:
            return "simple"
        if any(kw in query for kw in ["analyze", "compare", "design"]):
            return "complex"
        return "medium"
```

**Cost savings**: 60-80% reduction by routing simple queries to cheap models.

## 4. Pattern: Agent Orchestration Platform

```
┌─────────────────── Agent Platform ───────────────────────┐
│                                                           │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  │
│  │  Task Queue  │  │  State Store │  │  Tool Registry│  │
│  │  (priorities,│  │  (checkpoints│  │  (available   │  │
│  │   scheduling)│  │   per session)│  │   tools)     │  │
│  └──────────────┘  └──────────────┘  └──────────────┘  │
│                                                           │
│  ┌──────────────────────────────────────────────────┐   │
│  │              Agent Runtime                        │   │
│  │  ┌────────┐  ┌────────┐  ┌────────┐            │   │
│  │  │Agent 1 │  │Agent 2 │  │Agent 3 │  (pool)    │   │
│  │  └────────┘  └────────┘  └────────┘            │   │
│  └──────────────────────────────────────────────────┘   │
│                                                           │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  │
│  │  Guardrails  │  │  Monitoring  │  │  Cost Control│  │
│  └──────────────┘  └──────────────┘  └──────────────┘  │
└───────────────────────────────────────────────────────────┘
```

## 5. Pattern: Streaming Architecture

For real-time responses (critical for UX):

```python
async def stream_rag_response(query):
    # Phase 1: Show retrieval status (instant feedback)
    yield {"type": "status", "message": "Searching documents..."}
    
    docs = await retrieve(query)
    yield {"type": "sources", "data": [d.metadata for d in docs]}
    
    # Phase 2: Stream LLM generation token-by-token
    yield {"type": "status", "message": "Generating answer..."}
    
    async for token in llm.astream(prompt.format(context=docs, question=query)):
        yield {"type": "token", "data": token.content}
    
    # Phase 3: Post-processing (citations, confidence)
    yield {"type": "metadata", "data": {"confidence": 0.87, "citations": [...]}}
```

### Server-Sent Events (SSE) pattern:
```
Client                          Server
  │──── GET /chat?q=... ──────▶│
  │◀─── event: status ─────────│ "Searching..."
  │◀─── event: sources ────────│ [{doc1}, {doc2}]
  │◀─── event: token ──────────│ "Based"
  │◀─── event: token ──────────│ " on"
  │◀─── event: token ──────────│ " the"
  │◀─── event: token ──────────│ " data"
  │◀─── event: done ───────────│ {metadata}
```

## 6. Pattern: Evaluation-Driven Development

```
┌─────────────────── Development Loop ─────────────────────┐
│                                                           │
│  1. Define eval dataset (questions + expected answers)    │
│  2. Build/modify pipeline                                │
│  3. Run evals (automated)                                │
│  4. Analyze failures                                     │
│  5. Fix (prompt, retrieval, model selection)             │
│  6. Run evals again                                      │
│  7. Deploy if metrics pass gates                         │
│                                                           │
└───────────────────────────────────────────────────────────┘

CI/CD for GenAI:
  Push code → Run unit tests → Run eval suite → 
  Compare to baseline → Deploy if improvement (or no regression)
```

## 7. Pattern: Guardrails Architecture

```
┌────── Input Guardrails ─────┐    ┌──── Output Guardrails ────┐
│                              │    │                            │
│  • PII detection/redaction   │    │  • Hallucination check    │
│  • Prompt injection detect   │    │  • PII in output          │
│  • Topic classification      │    │  • Toxicity filter        │
│  • Rate limiting             │    │  • Factual grounding      │
│  • Input validation          │    │  • Compliance check       │
│                              │    │  • Citation verification  │
└──────────────────────────────┘    └────────────────────────────┘
```

```python
class GuardrailsPipeline:
    def __init__(self):
        self.input_checks = [
            PIIDetector(),
            PromptInjectionDetector(),
            TopicFilter(allowed=["finance", "general"]),
        ]
        self.output_checks = [
            HallucinationChecker(),
            PIIFilter(),
            ComplianceChecker(rules=SEC_RULES),
        ]
    
    def process(self, query, generate_fn):
        # Input checks
        for check in self.input_checks:
            result = check.evaluate(query)
            if result.blocked:
                return SafeResponse(reason=result.reason)
            query = result.sanitized_input  # May redact PII
        
        # Generate
        response = generate_fn(query)
        
        # Output checks
        for check in self.output_checks:
            result = check.evaluate(response)
            if result.blocked:
                return SafeResponse(reason="Response filtered for safety")
            response = result.sanitized_output
        
        return response
```

## 8. Pattern: Caching Layers

```
┌─────────────────── Cache Hierarchy ─────────────────────┐
│                                                          │
│  L1: Exact match cache (Redis)                          │
│      Key: hash(query + context)                         │
│      Hit rate: ~10-20%                                  │
│                                                          │
│  L2: Semantic cache (Vector similarity)                 │
│      If query embedding > 0.95 similar to cached query  │
│      Hit rate: ~20-40%                                  │
│                                                          │
│  L3: Prompt cache (provider-level)                      │
│      OpenAI/Anthropic cache common prefixes             │
│      Savings: 50% on input tokens for repeated prompts  │
│                                                          │
│  L4: Embedding cache                                    │
│      Cache embedding vectors for repeated texts         │
│      Savings: 100% embedding cost for cached texts      │
│                                                          │
└──────────────────────────────────────────────────────────┘
```

## 9. Pattern: Multi-Model Ensemble

```python
class EnsembleGenerator:
    """Use multiple models and combine results"""
    
    async def generate(self, query, context):
        # Run multiple models in parallel
        responses = await asyncio.gather(
            self.gpt4.generate(query, context),
            self.claude.generate(query, context),
            self.llama.generate(query, context),
        )
        
        # Consensus: if 2+ agree, high confidence
        if self.check_consensus(responses):
            return self.merge_responses(responses)
        
        # Disagreement: use the most detailed response
        return self.select_best(responses, query)
```

**When to use:**
- High-stakes decisions (financial, medical)
- When you need confidence calibration
- When individual models have complementary strengths

## 10. Architecture for D.E. Shaw (Financial Use Cases)

### Investment Research Platform:
```
                    ┌───────────────┐
                    │  Analyst UI   │
                    └───────┬───────┘
                            │
                    ┌───────▼───────┐
                    │   API Layer   │
                    │  (auth, rate  │
                    │   limiting)   │
                    └───────┬───────┘
                            │
           ┌────────────────┼────────────────┐
           │                │                │
    ┌──────▼──────┐ ┌──────▼──────┐ ┌──────▼──────┐
    │   Q&A RAG   │ │  Analysis   │ │   Alert     │
    │   Service   │ │   Agent     │ │   System    │
    └──────┬──────┘ └──────┬──────┘ └──────┬──────┘
           │                │                │
    ┌──────▼──────────────────────────────────────┐
    │              Shared Infrastructure           │
    │  • Vector Store (research reports)           │
    │  • Market Data API (real-time + historical)  │
    │  • SEC EDGAR (filings)                       │
    │  • News feeds                                │
    │  • Internal models (quant signals)           │
    └─────────────────────────────────────────────┘
```

### Key Design Decisions:
1. **On-prem vs Cloud**: Financial data sensitivity → likely hybrid
2. **Model selection**: May need on-prem Llama for sensitive queries
3. **Latency budget**: Trading decisions need sub-second routing
4. **Audit trail**: Every LLM call logged for compliance
5. **Data isolation**: Chinese walls between departments

## 11. Anti-Patterns

| Anti-Pattern | Problem | Better Approach |
|-------------|---------|-----------------|
| Monolithic LLM call | Single point of failure, hard to debug | Break into composable stages |
| No caching | Repeated work, high cost | Multi-layer caching |
| Synchronous only | Slow for complex tasks | Stream partial results |
| Single model | No fallback, vendor dependency | Multi-model with routing |
| No guardrails | Unsafe outputs in production | Input/output guardrails |
| No evaluation | Can't measure quality | Automated eval suite |
| Embedding at query time | Slow ingestion | Pre-compute, batch embed |

## 12. Interview Design Question Template

When asked "Design a GenAI system for X":
```
1. CLARIFY: What's the use case? Who are the users? Scale?
2. HIGH-LEVEL: Draw the major components (ingest, serve, monitor)
3. DATA: What data sources? How fresh? How much?
4. RETRIEVAL: Vector search? Hybrid? Structured queries?
5. GENERATION: Which model? Why? Streaming?
6. SAFETY: Guardrails? PII? Compliance?
7. SCALE: Caching? Async? Cost optimization?
8. EVAL: How do you know it works? Metrics?
9. ITERATION: How do you improve over time?
```
