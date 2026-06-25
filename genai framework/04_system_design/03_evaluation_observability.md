# Evaluation & Observability

## 1. The Evaluation Problem

GenAI outputs are non-deterministic. Traditional testing (expected == actual) doesn't work.

```
Traditional: assert output == "Paris"
GenAI:       assert is_correct(output, reference="Paris")
             assert is_grounded(output, sources)
             assert is_safe(output)
             assert meets_quality_bar(output)
```

## 2. Evaluation Taxonomy

### Offline Evaluation (Before Deployment):
```
Dev evals:       Run during development, fast feedback
CI evals:        Run on every PR, gate deployment
Benchmark evals: Periodic, comprehensive quality assessment
```

### Online Evaluation (In Production):
```
Sample-based:    Judge random sample of real queries
User feedback:   Thumbs up/down, explicit ratings
Implicit signals: Click-through, time-on-page, follow-up questions
A/B testing:     Compare versions with real traffic
```

## 3. Metrics Framework

### RAG Metrics:

| Metric | What it Measures | How to Compute |
|--------|-----------------|----------------|
| **Context Precision** | Are retrieved docs relevant? | LLM judges each doc's relevance |
| **Context Recall** | Is the answer info in retrieved docs? | Compare needed facts vs found facts |
| **Faithfulness** | Is answer grounded in context? | Check each claim against sources |
| **Answer Relevancy** | Does answer address the question? | LLM judges relevance |
| **Answer Correctness** | Is the answer right? | Compare to ground truth |

### Agent Metrics:

| Metric | What it Measures | How to Compute |
|--------|-----------------|----------------|
| **Task Completion** | Did it accomplish the goal? | Binary or graded |
| **Tool Accuracy** | Right tools with right args? | Compare to expected trajectory |
| **Efficiency** | How many steps? | Count steps vs optimal |
| **Cost** | Total tokens used | Sum across all LLM calls |
| **Latency** | End-to-end time | Wall clock time |
| **Consistency** | Same answer across runs? | Run N times, measure variance |

### Business Metrics:

| Metric | Example |
|--------|---------|
| User satisfaction | CSAT score, NPS |
| Adoption | DAU, queries/user/day |
| Deflection | % questions answered without human |
| Time saved | Avg time to get answer vs manual |
| Cost per query | Total infra cost / queries served |

## 4. LLM-as-Judge

The most practical approach for scalable evaluation.

```python
judge_prompt = """
You are evaluating an AI assistant's response.

[Question]: {question}
[Context Provided]: {context}
[AI Response]: {response}
[Reference Answer]: {reference}

Evaluate on these criteria (1-5 each):

1. CORRECTNESS: Is the factual content accurate?
   1=Wrong, 2=Mostly wrong, 3=Partially correct, 4=Mostly correct, 5=Fully correct

2. COMPLETENESS: Does it address all aspects of the question?
   1=Misses everything, 3=Partial, 5=Comprehensive

3. FAITHFULNESS: Is every claim supported by the provided context?
   1=Hallucinated, 3=Mix, 5=Fully grounded

4. CONCISENESS: Is it appropriately concise without losing information?
   1=Way too verbose/short, 3=OK, 5=Perfect length

Output JSON:
{{"correctness": N, "completeness": N, "faithfulness": N, "conciseness": N, "explanation": "..."}}
"""

class LLMJudge:
    def __init__(self, model="gpt-4o"):
        self.judge = ChatOpenAI(model=model, temperature=0)
    
    def evaluate(self, question, context, response, reference=None):
        result = self.judge.invoke(judge_prompt.format(
            question=question,
            context=context,
            response=response,
            reference=reference or "Not provided"
        ))
        return json.loads(result.content)
```

### Calibrating LLM-as-Judge:
```python
# Validate judge agrees with human evaluators
human_labels = load_human_evaluations()  # 100+ examples
judge_labels = [judge.evaluate(ex) for ex in human_labels]

agreement = compute_agreement(human_labels, judge_labels)
# Target: >80% agreement (Cohen's kappa > 0.6)

# If low agreement: improve judge prompt or use different judge model
```

### Pairwise Comparison (A/B judging):
```python
pairwise_prompt = """
Which response is better for this question?

Question: {question}
Response A: {response_a}
Response B: {response_b}

Output: "A", "B", or "TIE" with explanation.
"""
# More reliable than absolute scoring
# Use for comparing prompt versions, model versions, pipeline versions
```

## 5. Evaluation Dataset Design

### Building a Good Eval Set:
```python
eval_dataset = [
    {
        "question": "What was Apple's Q4 2024 revenue?",
        "expected_answer": "$124.3 billion",
        "category": "factual_lookup",
        "difficulty": "easy",
        "source_doc": "AAPL_10Q_2024.pdf",
        "tags": ["financial", "specific_number"]
    },
    {
        "question": "Compare Apple and Microsoft's cloud strategy",
        "expected_answer": "Apple focuses on device ecosystem... Microsoft on Azure...",
        "category": "analysis",
        "difficulty": "hard",
        "acceptance_criteria": [
            "Mentions Apple's device-first approach",
            "Mentions Azure and enterprise focus",
            "Provides meaningful comparison"
        ]
    }
]
```

### Coverage Matrix:
```
Ensure your eval set covers:
  ✓ Different question types (factual, analytical, comparative)
  ✓ Different difficulty levels
  ✓ Edge cases (no answer available, ambiguous query)
  ✓ Different document types (tables, text, mixed)
  ✓ Temporal queries (latest vs historical)
  ✓ Multi-document synthesis
  ✓ Adversarial (trick questions, prompt injection)
```

### Size Guidelines:
```
MVP evaluation: 50 examples
Good evaluation: 200-500 examples
Robust evaluation: 1000+ examples

Split: 70% regression tests, 30% new/hard cases
Refresh: Add 10% new cases monthly from production failures
```

## 6. RAGAS Framework

```python
from ragas import evaluate
from ragas.metrics import (
    faithfulness,
    answer_relevancy,
    context_precision,
    context_recall,
    answer_correctness
)
from datasets import Dataset

# Prepare dataset
eval_data = Dataset.from_dict({
    "question": questions,
    "answer": generated_answers,
    "contexts": retrieved_contexts,  # List[List[str]]
    "ground_truth": reference_answers
})

# Run evaluation
result = evaluate(
    dataset=eval_data,
    metrics=[
        faithfulness,      # Is answer grounded in context?
        answer_relevancy,  # Does answer address question?
        context_precision, # Are retrieved docs relevant?
        context_recall,    # Do retrieved docs contain needed info?
        answer_correctness # Is answer correct vs ground truth?
    ]
)

print(result)
# {'faithfulness': 0.87, 'answer_relevancy': 0.92, 
#  'context_precision': 0.78, 'context_recall': 0.85,
#  'answer_correctness': 0.81}
```

## 7. Observability in Production

### Tracing with LangSmith:
```python
# Every chain/agent invocation gets a trace:
# - Full input/output at each step
# - Token counts and costs
# - Latency per step
# - Retrieval results
# - Tool call arguments and returns

# Automatic with environment variable
os.environ["LANGCHAIN_TRACING_V2"] = "true"
```

### Custom Metrics Collection:
```python
import prometheus_client as prom

# Define metrics
query_latency = prom.Histogram(
    "genai_query_latency_seconds",
    "Query latency",
    buckets=[0.5, 1, 2, 5, 10, 30]
)
query_cost = prom.Counter("genai_query_cost_dollars", "Query cost")
retrieval_count = prom.Histogram("genai_retrieval_docs", "Docs retrieved")
quality_score = prom.Histogram("genai_quality_score", "Response quality")
cache_hits = prom.Counter("genai_cache_hits_total", "Cache hits")
errors = prom.Counter("genai_errors_total", "Errors", ["error_type"])

# Instrument pipeline
@query_latency.time()
async def handle_query(query):
    docs = retrieve(query)
    retrieval_count.observe(len(docs))
    
    answer = generate(query, docs)
    query_cost.inc(estimate_cost(answer))
    
    score = async_evaluate(query, answer)
    quality_score.observe(score)
    
    return answer
```

### Alerting:
```yaml
# Prometheus alerting rules
groups:
  - name: genai_alerts
    rules:
      - alert: HighLatency
        expr: histogram_quantile(0.95, genai_query_latency_seconds) > 5
        for: 5m
        
      - alert: QualityDrop
        expr: avg(genai_quality_score) < 0.7
        for: 15m
        
      - alert: CostSpike
        expr: rate(genai_query_cost_dollars[1h]) > 2 * avg_over_time(genai_query_cost_dollars[7d])
        
      - alert: HighErrorRate
        expr: rate(genai_errors_total[5m]) > 0.05
```

## 8. Debugging GenAI Systems

### Common Debugging Workflow:
```
1. Identify bad output (user report or automated detection)
2. Find trace in LangSmith/logs
3. Examine each step:
   - Was the prompt correct?
   - Was retrieval relevant?
   - Did the model follow instructions?
   - Were tool results correct?
4. Root cause: retrieval failure? prompt issue? model limitation?
5. Add failing case to eval dataset
6. Fix and verify
```

### Retrieval Debugging:
```python
def debug_retrieval(query):
    """Why wasn't the right doc retrieved?"""
    # 1. Check if doc exists in index
    all_docs = vectorstore.list()
    
    # 2. Check embedding similarity
    query_embedding = embed(query)
    target_embedding = embed(expected_doc)
    similarity = cosine_similarity(query_embedding, target_embedding)
    print(f"Query-to-target similarity: {similarity}")  # Should be > 0.7
    
    # 3. Check what WAS retrieved
    results = vectorstore.similarity_search_with_scores(query, k=10)
    for doc, score in results:
        print(f"Score: {score:.3f} | Source: {doc.metadata['source']}")
    
    # 4. Check chunk boundaries
    # Is the answer split across chunk boundaries?
```

## 9. Continuous Improvement Loop

```
┌─────────────────── Improvement Cycle ─────────────────────┐
│                                                            │
│  1. Monitor production quality metrics                     │
│  2. Identify failure patterns (cluster bad responses)      │
│  3. Add failing cases to eval dataset                      │
│  4. Diagnose root cause:                                   │
│     - Retrieval miss? → improve chunking/embedding         │
│     - Generation error? → improve prompt                   │
│     - Tool failure? → fix tool implementation              │
│  5. Implement fix                                          │
│  6. Run eval suite (ensure no regression)                  │
│  7. Deploy with canary                                     │
│  8. Monitor again                                          │
│                                                            │
└────────────────────────────────────────────────────────────┘
```

## 10. Interview Talking Points

- "I treat the eval dataset as a living artifact — it grows with every production failure"
- "LLM-as-judge is scalable but must be calibrated against human judgments"
- "Three critical metrics: faithfulness (no hallucination), relevancy, and latency"
- "Observability isn't optional — every LLM call needs tracing in production"
- "For financial systems: I'd add compliance-specific evaluation criteria"
- "The debugging workflow: trace → isolate step → identify root cause → fix → eval"
