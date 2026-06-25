# RAG Fundamentals - Retrieval Augmented Generation

## 1. What is RAG?

RAG = Give the LLM relevant context BEFORE it generates an answer.

Instead of relying solely on the model's training data (which is static and may hallucinate), we retrieve relevant documents and include them in the prompt.

```
Traditional LLM:
  Question → LLM → Answer (may hallucinate)

RAG:
  Question → Retriever → Relevant Docs → LLM + Docs → Grounded Answer
```

## 2. Why RAG? (vs alternatives)

| Approach | Pros | Cons |
|----------|------|------|
| Fine-tuning | Bakes in knowledge | Expensive, stale data, still hallucinates |
| Long context | Simple, no infra | Cost scales with context, attention degradation |
| RAG | Fresh data, citations, cheaper | More components, retrieval quality matters |

### When to use RAG:
- Knowledge base Q&A (docs, wikis, policies)
- Data changes frequently (news, market data)
- Need citations/provenance
- Domain-specific knowledge not in training data
- Legal/compliance requires traceability

### When NOT to use RAG:
- General knowledge questions (model already knows)
- Pure reasoning tasks (no external knowledge needed)
- Real-time data (use API tools instead)
- Tiny dataset (just put it all in context)

## 3. RAG Architecture

```
┌─────────────────── OFFLINE (Indexing) ────────────────────┐
│                                                            │
│  Documents → Loader → Chunker → Embedder → Vector DB     │
│                                                            │
└────────────────────────────────────────────────────────────┘

┌─────────────────── ONLINE (Querying) ────────────────────┐
│                                                           │
│  Query → Embedder → Vector DB → Top-K docs              │
│    ↓                                                      │
│  [Query + Retrieved Docs] → LLM → Answer                │
│                                                           │
└───────────────────────────────────────────────────────────┘
```

### Components:
1. **Document Loader**: Ingest PDFs, HTML, APIs, databases
2. **Text Splitter/Chunker**: Break docs into retrievable units
3. **Embedding Model**: Convert text → vectors
4. **Vector Store**: Index and search vectors efficiently
5. **Retriever**: Find relevant chunks for a query
6. **Generator (LLM)**: Synthesize answer from retrieved context

## 4. Basic RAG Pipeline (Code)

```python
from langchain_openai import OpenAIEmbeddings, ChatOpenAI
from langchain_community.vectorstores import FAISS
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain_core.prompts import ChatPromptTemplate

# 1. Load documents
docs = load_documents("./data/")

# 2. Split into chunks
splitter = RecursiveCharacterTextSplitter(
    chunk_size=500,
    chunk_overlap=50,
    separators=["\n\n", "\n", ". ", " ", ""]
)
chunks = splitter.split_documents(docs)

# 3. Embed and store
embeddings = OpenAIEmbeddings(model="text-embedding-3-small")
vectorstore = FAISS.from_documents(chunks, embeddings)

# 4. Retrieve
retriever = vectorstore.as_retriever(search_kwargs={"k": 5})
relevant_docs = retriever.invoke("What is our refund policy?")

# 5. Generate
prompt = ChatPromptTemplate.from_template("""
Answer based on the following context only. If the answer is not
in the context, say "I don't know."

Context: {context}
Question: {question}
""")

llm = ChatOpenAI(model="gpt-4o")
chain = prompt | llm
answer = chain.invoke({
    "context": "\n\n".join(d.page_content for d in relevant_docs),
    "question": "What is our refund policy?"
})
```

## 5. RAG Quality Metrics

### Retrieval Quality:
- **Recall@K**: What fraction of relevant docs are in top-K?
- **Precision@K**: What fraction of top-K are actually relevant?
- **MRR** (Mean Reciprocal Rank): How high is the first relevant doc?
- **NDCG**: Normalized discounted cumulative gain

### Generation Quality:
- **Faithfulness**: Does the answer use ONLY the retrieved context? (no hallucination)
- **Answer relevance**: Does the answer address the question?
- **Context relevance**: Is the retrieved context actually useful?

### End-to-end:
- **Answer correctness**: Compared to ground truth
- **Citation accuracy**: Are source references correct?

### Tools for RAG Evaluation:
- **RAGAS**: Open-source RAG evaluation framework
- **LangSmith**: Tracing + evaluation from LangChain
- **Arize Phoenix**: Open-source observability for LLMs

## 6. Common RAG Failure Modes

| Failure | Symptom | Root Cause | Fix |
|---------|---------|------------|-----|
| "I don't know" when it should | Low recall | Bad chunks, wrong embedding model | Better chunking, hybrid search |
| Hallucinated answer | Unfaithful | Context too noisy, weak prompt | Better retrieval, stronger prompt constraints |
| Irrelevant context | Low precision | Embedding mismatch | Query transformation, reranking |
| Contradictory answer | Conflicting docs | Multiple versions, stale data | Metadata filtering, deduplication |
| Partial answer | Missing info | Chunk boundaries split answer | Larger chunks, parent-child retrieval |

## 7. RAG vs Fine-tuning Decision Framework

```
Is the knowledge:
  ├─ Static & small? → Put in system prompt
  ├─ Static & large? → Fine-tune OR RAG
  ├─ Dynamic/changing? → RAG (only option)
  └─ Requires citation? → RAG (only option)

Is the task:
  ├─ Style/tone change? → Fine-tune
  ├─ New knowledge? → RAG
  └─ Both? → RAG + fine-tuned model
```

## 8. D.E. Shaw Specific Considerations

### Financial RAG challenges:
- **Time-sensitivity**: Market data, filings have dates → metadata filtering
- **Numerical reasoning**: RAG retrieves text, but financial analysis needs calculations
- **Multi-document synthesis**: Quarterly reports, analyst notes, news → need to combine
- **Structured + unstructured**: Tables, charts alongside text
- **Low tolerance for hallucination**: Financial decisions need high accuracy

### Scale considerations:
- Millions of documents (SEC filings, research reports)
- Low latency requirements (trading decisions)
- Cost efficiency at scale
- Data freshness (continuous ingestion pipeline)

## 9. Interview Questions

1. "Design a RAG system for internal research report Q&A"
2. "How would you handle conflicting information across documents?"
3. "Your RAG system has 80% accuracy. How do you improve it?"
4. "How do you evaluate whether RAG is working correctly?"
5. "When would you choose fine-tuning over RAG?"
6. "How do you handle documents that are too large for one chunk?"
