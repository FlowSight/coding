# Advanced RAG Techniques

## 1. The RAG Quality Stack

Basic RAG gets you 60-70% accuracy. Advanced RAG gets you to 85-95%.

```
Level 0: Naive RAG (embed → retrieve → generate)
Level 1: + Better chunking + metadata filtering
Level 2: + Query transformation + reranking
Level 3: + Hybrid search + multi-stage retrieval
Level 4: + Adaptive retrieval + self-correction
```

## 2. Query Transformation

The user's query is often NOT the best search query.

### Query Rewriting:
```python
rewrite_prompt = """
Rewrite this user question as a search query optimized for 
semantic similarity search in a financial document database.
Original: {question}
Rewritten:
"""
# "How did Apple do last quarter?" 
# → "Apple Inc quarterly revenue earnings financial performance Q4 2024"
```

### HyDE (Hypothetical Document Embeddings):
```
Step 1: Generate a hypothetical ANSWER to the question
Step 2: Embed the hypothetical answer (not the question)
Step 3: Search with that embedding

Why? The answer is more similar to the actual document than the question is.
```

```python
# User asks: "What caused the 2023 banking crisis?"
# HyDE generates: "The 2023 banking crisis was caused by rapid interest rate 
#   hikes by the Federal Reserve, which decreased the value of long-duration 
#   bonds held by banks like SVB..."
# This hypothetical answer is then used as the search query
```

### Multi-Query / Query Decomposition:
```python
decompose_prompt = """
Break this complex question into 2-4 simpler sub-questions
that can each be answered independently:

Question: {question}
Sub-questions:
"""

# "Compare Apple and Google's AI strategy and investment in 2024"
# → "What is Apple's AI strategy in 2024?"
# → "How much did Apple invest in AI in 2024?"
# → "What is Google's AI strategy in 2024?"
# → "How much did Google invest in AI in 2024?"

# Retrieve for each sub-question, combine results
```

### Step-back Prompting:
```
Original: "What was AAPL's P/E ratio in Q3 2024?"
Step-back: "What were Apple's key financial metrics in 2024?"
# Retrieves broader context that likely contains the specific answer
```

## 3. Reranking

Initial retrieval (vector search) optimizes for recall. Reranking optimizes for precision.

```
Vector Search (fast, approximate) → Top 20-50 candidates
    ↓
Reranker (slow, precise) → Top 5 final results
    ↓
LLM Generation
```

### Cross-Encoder Reranking:
```python
from sentence_transformers import CrossEncoder

reranker = CrossEncoder("cross-encoder/ms-marco-MiniLM-L-6-v2")

# Score each (query, document) pair
pairs = [(query, doc.page_content) for doc in candidates]
scores = reranker.predict(pairs)

# Sort by score, take top-k
reranked = sorted(zip(candidates, scores), key=lambda x: x[1], reverse=True)
top_k = [doc for doc, score in reranked[:5]]
```

### Cohere Rerank (API-based):
```python
import cohere
co = cohere.Client()

results = co.rerank(
    model="rerank-english-v3.0",
    query="quarterly earnings growth",
    documents=[doc.page_content for doc in candidates],
    top_n=5
)
```

### LLM-as-Reranker:
```python
rerank_prompt = """
Given the query: "{query}"

Rate each document's relevance (1-5):
Document 1: {doc1}
Document 2: {doc2}
...

Output JSON: [{{"doc_id": 1, "score": 4, "reason": "..."}}]
"""
# More expensive but most accurate for complex queries
```

### When to use reranking:
- Always in production (marginal cost, big quality gain)
- Especially when initial retrieval has low precision
- Cross-encoder is best quality/cost trade-off

## 4. Hybrid Search

Combine vector similarity with keyword/BM25 search.

```
Vector search: Good at semantic similarity, bad at exact matches
BM25/keyword:  Good at exact terms, bad at paraphrases
Hybrid:        Best of both worlds
```

### Reciprocal Rank Fusion (RRF):
```python
def reciprocal_rank_fusion(results_lists, k=60):
    """Combine multiple ranked lists"""
    scores = {}
    for results in results_lists:
        for rank, doc in enumerate(results):
            doc_id = doc.metadata["id"]
            scores[doc_id] = scores.get(doc_id, 0) + 1 / (k + rank + 1)
    return sorted(scores.items(), key=lambda x: x[1], reverse=True)

# Combine vector + BM25 results
vector_results = vectorstore.similarity_search(query, k=20)
bm25_results = bm25_retriever.get_relevant_documents(query, k=20)
final = reciprocal_rank_fusion([vector_results, bm25_results])
```

### Weighted Hybrid:
```python
# alpha = 1 → pure vector, alpha = 0 → pure keyword
alpha = 0.7
final_score = alpha * vector_score + (1 - alpha) * bm25_score
```

### When keyword search wins:
- Exact entity names ("AAPL", "10-K", "Section 302")
- Numerical queries ("revenue > $100B")
- Acronyms and jargon
- Very short queries (1-2 words)

## 5. Multi-Stage Retrieval

### Two-stage (most common):
```
Stage 1: Broad retrieval (vector + keyword) → 50-100 candidates
Stage 2: Reranking → 5-10 final results
```

### Three-stage (complex systems):
```
Stage 1: Coarse retrieval (IVF/keyword) → 200 candidates
Stage 2: Fine retrieval (HNSW + metadata filter) → 30 candidates
Stage 3: Cross-encoder reranking → 5 final results
```

### Iterative Retrieval:
```
Step 1: Retrieve initial context
Step 2: Generate partial answer
Step 3: Identify knowledge gaps in the answer
Step 4: Formulate new queries for gaps
Step 5: Retrieve additional context
Step 6: Generate final answer with full context
```

## 6. Contextual Compression

Reduce noise in retrieved chunks before passing to LLM:

```python
from langchain.retrievers import ContextualCompressionRetriever
from langchain.retrievers.document_compressors import LLMChainExtractor

compressor = LLMChainExtractor.from_llm(llm)
compression_retriever = ContextualCompressionRetriever(
    base_compressor=compressor,
    base_retriever=retriever
)
# Extracts only the relevant parts from each chunk
```

### Why compress?
- Removes irrelevant sentences from chunks
- Reduces token usage (cost savings)
- Improves answer quality (less noise)
- Trade-off: Added latency from compression LLM call

## 7. Self-RAG (Adaptive Retrieval)

The LLM decides WHETHER to retrieve and evaluates retrieval quality:

```
Step 1: Should I retrieve? (not all questions need retrieval)
Step 2: If yes → retrieve
Step 3: Is the retrieved context relevant? (critique)
Step 4: If no → reformulate query and retrieve again
Step 5: Generate answer
Step 6: Is the answer supported by the context? (verify)
Step 7: If no → regenerate with stricter constraints
```

### Implementation pattern:
```python
def self_rag(question):
    # Decide if retrieval is needed
    needs_retrieval = llm("Does this question need external knowledge? " + question)
    
    if needs_retrieval == "no":
        return llm(question)  # Direct answer
    
    # Retrieve and validate
    docs = retriever.invoke(question)
    relevance = llm(f"Are these docs relevant to '{question}'? {docs}")
    
    if relevance == "no":
        # Reformulate and retry
        new_query = llm(f"Rewrite for better retrieval: {question}")
        docs = retriever.invoke(new_query)
    
    # Generate with faithfulness check
    answer = llm(f"Context: {docs}\nQuestion: {question}")
    is_grounded = llm(f"Is this answer supported by the context? {answer}")
    
    if is_grounded == "no":
        answer = llm(f"Answer ONLY from context: {docs}\nQuestion: {question}")
    
    return answer
```

## 8. CRAG (Corrective RAG)

Evaluate retrieval quality and take corrective action:

```
Retrieved docs → Relevance evaluator
  ├─ All relevant → Use as-is
  ├─ Some relevant → Filter, keep only relevant
  └─ None relevant → Fall back to web search or reject
```

## 9. Graph RAG (Microsoft)

Combine knowledge graphs with vector retrieval:

```
Step 1: Build knowledge graph from documents
  - Extract entities and relationships
  - Create community summaries at different levels

Step 2: At query time:
  - Vector search for relevant entities/nodes
  - Traverse graph for related context
  - Include community summaries for broader context
```

**Best for**: Questions requiring synthesis across many documents ("What are the main themes in our research?")

## 10. Production RAG Patterns

### Routing:
```python
def route_query(question):
    """Route to appropriate retrieval strategy"""
    if is_simple_lookup(question):
        return keyword_search(question)
    elif is_analytical(question):
        return multi_query_rag(question)
    elif is_comparative(question):
        return multi_doc_rag(question)
    else:
        return standard_rag(question)
```

### Caching:
```python
# Cache embeddings for repeated queries
# Cache LLM responses for identical (query + context) pairs
# Semantic cache: return cached answer if query is >0.95 similar
```

### Fallback Chain:
```
Try: RAG with strict grounding
  ├─ Success → Return answer with citations
  └─ Failure (low confidence) →
      Try: RAG with broader retrieval
        ├─ Success → Return with lower confidence flag
        └─ Failure →
            Return: "I couldn't find a reliable answer" + suggest alternatives
```

## 11. RAG Evaluation Framework (RAGAS)

```python
from ragas import evaluate
from ragas.metrics import (
    faithfulness,      # Is answer grounded in context?
    answer_relevancy,  # Does answer address the question?
    context_precision, # Is retrieved context relevant?
    context_recall,    # Does context contain the answer?
)

result = evaluate(
    dataset=eval_dataset,  # questions + ground_truth + contexts + answers
    metrics=[faithfulness, answer_relevancy, context_precision, context_recall]
)
print(result)
# {'faithfulness': 0.87, 'answer_relevancy': 0.91, ...}
```

## 12. D.E. Shaw Interview: "Improve RAG from 70% to 90%"

**Systematic approach:**
1. Identify failure modes (categorize wrong answers)
2. Is it retrieval failure or generation failure?
   - Retrieval: relevant docs not found → fix chunking, hybrid search, reranking
   - Generation: relevant docs found but answer wrong → fix prompt, use CoT
3. Apply targeted fixes based on failure category
4. Measure improvement on test set
5. Iterate

**Common improvements in order of impact:**
1. Reranking (+5-10% accuracy, easy to add)
2. Hybrid search (+5-8%, handles exact matches)
3. Better chunking (+3-7%, often biggest gain)
4. Query transformation (+3-5%, helps complex queries)
5. Metadata filtering (+2-5%, reduces noise)
