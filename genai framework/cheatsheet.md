# GenAI Frameworks Cheat Sheet — D.E. Shaw Interview

## 1-Minute Concepts (Know These Cold)

### RAG Pipeline
```
Query → Embed → Retrieve (top-k) → Rerank → Generate (with context) → Answer
```

### Agent Loop (ReAct)
```
Thought → Action → Observation → Thought → ... → Final Answer
```

### LangChain LCEL
```python
chain = prompt | model | output_parser  # pipe = compose
```

### Embedding + Similarity
```
Text → Embedding model → Vector [768 or 1536 dims]
Similarity = cosine(v1, v2)  # 1 = identical, 0 = unrelated
```

---

## Key Numbers to Know

| Metric | Value | Context |
|--------|-------|---------|
| GPT-4o context | 128K tokens | ~300 pages |
| GPT-4o-mini cost | $0.15/1M input tokens | 100x cheaper than GPT-4 |
| Embedding dim (OpenAI) | 1536 (large) / 256 (small) | text-embedding-3 |
| HNSW recall | >95% at 10ms | Best ANN algorithm |
| Typical RAG latency | 2-5 seconds | End-to-end |
| Token ≈ | 0.75 words (English) | 4 chars ≈ 1 token |
| Context window cost | Grows linearly with length | Attention is O(n²) compute |

---

## Chunking Decision Tree

```
Document type?
├── Code → AST-based chunking
├── Tables → Keep table intact as one chunk
├── Structured (HTML/MD) → Split on headers (recursive)
├── Unstructured prose → Recursive text splitter (512-1024 tokens)
└── Mixed → Combine strategies, tag metadata by section type
```

---

## When to Use What

| Problem | Solution | Why |
|---------|----------|-----|
| Q&A over docs | RAG | Standard pattern |
| Complex multi-step task | Agent with tools | Needs planning + execution |
| Fixed workflow | Chain (LCEL) | Predictable, reliable |
| Multi-doc synthesis | Advanced RAG (query decomposition) | Single query won't cover it |
| Dynamic routing | LangGraph | Need conditional logic + state |
| High accuracy required | RAG + reranking + confidence scoring | Reduce hallucination |
| Real-time analysis | Streaming + caching + fast model | Latency matters |
| Compliance/audit | RAG + citations + audit log | Traceability required |

---

## Vector Database Comparison

| DB | Best For | Hosted? | Notes |
|----|----------|---------|-------|
| **Pinecone** | Managed simplicity | Yes | Serverless, auto-scales |
| **Weaviate** | Hybrid search | Both | BM25 + vector natively |
| **pgvector** | Already using Postgres | Self | No extra infra |
| **FAISS** | Research/prototyping | No | In-memory, fastest |
| **Qdrant** | High performance | Both | Rust-based, filtering |

---

## Advanced RAG Patterns (Acronyms)

- **HyDE**: Generate hypothetical answer → embed that → retrieve (better match)
- **CRAG**: Corrective RAG — web fallback if retrieval confidence low
- **Self-RAG**: LLM decides when to retrieve and self-evaluates relevance
- **Graph RAG**: Entity extraction → knowledge graph → graph traversal + vector
- **RAPTOR**: Hierarchical summarization tree for multi-level abstraction

---

## Agent Architectures

```
ReAct:         Thought-Action-Observation loop (most common)
Plan-Execute:  Make full plan first, then execute steps
Reflexion:     Execute → Self-critique → Retry with learnings
LATS:          Tree search over possible action paths (Monte Carlo)
Multi-Agent:   Supervisor assigns to specialist workers
```

---

## LangGraph Key Concepts

```python
# State = TypedDict
class State(TypedDict):
    messages: list
    next_step: str

# Node = function that takes state, returns partial state
def retrieve(state): return {"documents": [...]}

# Edge = conditional routing
def route(state):
    if state["confidence"] > 0.8: return "generate"
    else: return "rewrite_query"

# Graph
graph = StateGraph(State)
graph.add_node("retrieve", retrieve)
graph.add_conditional_edges("evaluate", route)
```

---

## Cost Optimization Playbook

1. **Route by complexity**: Simple → GPT-4o-mini, Complex → GPT-4o
2. **Cache**: Semantic cache (similar questions → same answer)
3. **Reduce tokens**: Trim context, compress, use short prompts
4. **Batch**: Group similar requests
5. **Smaller models where possible**: 90% of tasks don't need GPT-4

```
Cost formula: (input_tokens × input_price + output_tokens × output_price) × calls/day × 30
```

---

## Evaluation Quick Reference

| What to Measure | Tool/Metric |
|----------------|-------------|
| Is answer correct? | Compare to ground truth, LLM-as-judge |
| Is answer grounded? | Faithfulness score (RAGAS) |
| Is retrieval good? | Context precision + recall |
| Is it fast enough? | P95 latency |
| Is it cheap enough? | Cost per query |
| Do users like it? | Thumbs up/down rate, CSAT |

---

## Safety & Guardrails

```python
# Input guardrails (before LLM)
- Prompt injection detection
- PII redaction
- Topic classification (block off-topic)

# Output guardrails (after LLM)
- Hallucination detection (claim verification)
- Toxicity check
- Compliance filter (no investment advice without disclaimer)
- Citation verification
```

---

## System Design Template

```
1. Requirements: Users, scale, latency, accuracy
2. Data pipeline: Ingest → Process → Store
3. Query pipeline: Query → Retrieve → Generate → Validate
4. Model selection: Speed vs quality trade-off
5. Evaluation: Offline metrics + online monitoring
6. Operations: Tracing, alerting, cost tracking
7. Safety: Guardrails, human-in-the-loop
8. Evolution: Feedback loop, eval dataset growth
```

---

## D.E. Shaw Talking Points

**Why GenAI in Finance:**
- Research automation (10-Ks, earnings, news) → faster alpha generation
- Compliance Q&A → reduce legal cost and risk
- Report generation → free analyst time for higher-value work
- NOT for direct trading decisions (regulatory + accuracy risk)

**Red Flags to Avoid:**
- ❌ "Just use GPT-4 for everything" (cost + latency)
- ❌ "The model is 95% accurate" (what happens in the 5%?)
- ❌ "We can fine-tune our way to accuracy" (often wrong approach)
- ❌ Ignoring data freshness (stale embeddings = wrong answers)
- ❌ No evaluation strategy

**Green Flags to Hit:**
- ✅ Cost-aware architecture ($ per query breakdown)
- ✅ Risk-aware (what if it's wrong? guardrails)
- ✅ Practical evaluation strategy (not just vibes)
- ✅ Understand trade-offs (latency vs accuracy vs cost)
- ✅ Security-first (data isolation, audit trails)
- ✅ Incremental deployment (canary → gradual rollout)

---

## Quick Prompt Patterns

```python
# Chain of Thought
"Think step by step before answering."

# Self-consistency
Run N times, take majority vote.

# Few-shot
"Here are 3 examples of good answers: ..."

# Structured output
"Output valid JSON with fields: answer, confidence, citations"

# Grounded generation
"Answer ONLY based on the provided context. If unsure, say 'I don't know.'"
```

---

## Final Prep Reminders

1. **Every system design answer needs**: scale numbers, cost estimate, failure modes
2. **Always mention evaluation** — how do you know it works?
3. **Show you understand trade-offs** — there's no single right answer
4. **Financial context**: accuracy > speed, audit trails, data security
5. **Be concrete**: "I'd use GPT-4o-mini at $0.15/1M tokens" not "I'd use a model"
