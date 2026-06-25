# Tokens & Embeddings

## 1. Tokenization

### What is a Token?
A token is the atomic unit that LLMs process. NOT characters, NOT words — subword units.

```
"Hello, world!" → ["Hello", ",", " world", "!"]  (4 tokens)
"unbelievable"  → ["un", "believ", "able"]        (3 tokens)
```

### Tokenization Algorithms:

**BPE (Byte Pair Encoding)** - Used by GPT, Llama:
1. Start with character-level vocabulary
2. Iteratively merge most frequent adjacent pairs
3. Result: common words = 1 token, rare words = multiple tokens

**SentencePiece** - Used by T5, Llama:
- Language-agnostic, treats input as raw bytes
- No pre-tokenization needed

**Tiktoken** (OpenAI's implementation):
```python
import tiktoken
enc = tiktoken.encoding_for_model("gpt-4")
tokens = enc.encode("Hello, world!")  # [9906, 11, 1917, 0]
len(tokens)  # 4
```

### Why Tokenization Matters:
- **Cost**: You pay per token (not per character)
- **Context limits**: 128K tokens ≠ 128K words (~1 token ≈ 4 chars in English)
- **Code is expensive**: Variable names, syntax → more tokens
- **Non-English text**: Often 2-3x more tokens than English equivalent
- **Rule of thumb**: 1 page of English ≈ 500-700 tokens

## 2. Embeddings

### What are Embeddings?
Dense vector representations of text in continuous high-dimensional space where semantic similarity corresponds to geometric proximity.

```
"king"  → [0.2, -0.4, 0.7, ..., 0.1]   (1536 dimensions for text-embedding-3-small)
"queen" → [0.3, -0.3, 0.6, ..., 0.2]   (nearby in vector space)
"car"   → [-0.5, 0.8, -0.1, ..., 0.9]  (far away)
```

### Types of Embeddings:

| Type | Use Case | Example Models |
|------|----------|---------------|
| Token embeddings | Inside LLM (first layer) | Part of GPT-4 |
| Sentence embeddings | Similarity, search, RAG | text-embedding-3, BGE, E5 |
| Document embeddings | Clustering, classification | Voyage, Cohere Embed |
| Multi-modal | Image + text search | CLIP, SigLIP |

### Embedding Models (2024-2025):

| Model | Dimensions | Context | Use Case |
|-------|-----------|---------|----------|
| OpenAI text-embedding-3-small | 1536 | 8K tokens | General purpose, cheap |
| OpenAI text-embedding-3-large | 3072 | 8K tokens | Higher quality |
| Cohere embed-v3 | 1024 | 512 tokens | Multilingual |
| BGE-M3 (BAAI) | 1024 | 8K tokens | Open source, multilingual |
| Voyage-3 | 1024 | 32K tokens | Long documents |
| GTE-Qwen2 | 768-1536 | 8K tokens | Open source, high quality |

### How Embeddings are Created:

**Contrastive Learning** (most common for retrieval embeddings):
```
Training: (query, positive_doc, negative_doc) triplets
Objective: Minimize distance(query, positive), Maximize distance(query, negative)
```

**Matryoshka Representation Learning (MRL)**:
- Embeddings are useful at ANY prefix length
- Can truncate 3072-dim → 256-dim with minimal quality loss
- Used by text-embedding-3-* models

## 3. Similarity Metrics

### Cosine Similarity (most common for embeddings):
```
cos_sim(A, B) = (A · B) / (||A|| × ||B||)
Range: [-1, 1], where 1 = identical direction
```

### Dot Product:
```
dot(A, B) = Σ(a_i × b_i)
Faster but sensitive to magnitude
If vectors are normalized → dot product = cosine similarity
```

### Euclidean Distance (L2):
```
L2(A, B) = √(Σ(a_i - b_i)²)
Lower = more similar
```

### When to use which:
- **Cosine**: Default for semantic similarity (magnitude-invariant)
- **Dot product**: When vectors are normalized (faster)
- **L2**: When magnitude matters (rare for text)

## 4. Embedding in Practice

### Semantic Search Pipeline:
```
Offline (indexing):
  Documents → Chunking → Embedding Model → Vector DB

Online (querying):
  Query → Embedding Model → Vector DB (ANN search) → Top-K results
```

### Code Example:
```python
from openai import OpenAI
client = OpenAI()

# Generate embeddings
response = client.embeddings.create(
    model="text-embedding-3-small",
    input=["How does RAG work?", "Retrieval augmented generation explained"]
)
vec1 = response.data[0].embedding  # List[float], len=1536
vec2 = response.data[1].embedding

# Compute similarity
import numpy as np
similarity = np.dot(vec1, vec2) / (np.linalg.norm(vec1) * np.linalg.norm(vec2))
# ≈ 0.89 (high similarity)
```

## 5. Approximate Nearest Neighbor (ANN) Search

Exact nearest neighbor search is O(n) - too slow for millions of vectors.

### ANN Algorithms:

**HNSW (Hierarchical Navigable Small World)**:
- Graph-based, state-of-the-art for recall
- Build time: O(n log n), Query: O(log n)
- Used by: Pinecone, Weaviate, pgvector
- Trade-off: High memory usage

**IVF (Inverted File Index)**:
- Cluster vectors, search only relevant clusters
- Faster build, lower memory
- Trade-off: Lower recall

**Product Quantization (PQ)**:
- Compress vectors by splitting into subspaces
- Dramatic memory reduction (32x or more)
- Trade-off: Approximate distances

**ScaNN (Google)**:
- Combines quantization + reranking
- Best in class for billion-scale

### Performance characteristics:
```
                Build Time    Query Time    Memory    Recall
HNSW            Slow          Fast          High      95-99%
IVF-PQ          Fast          Medium        Low       85-95%
Flat (exact)    None          Slow          Medium    100%
```

## 6. Key Interview Points

### "How do you choose an embedding model?"
1. **Benchmark on YOUR data** (MTEB leaderboard is directional only)
2. **Context length**: Does it cover your document sizes?
3. **Dimensions**: Higher = more expressive but slower search
4. **Latency**: Cloud API vs self-hosted
5. **Cost**: Per-token pricing vs GPU cost
6. **Domain**: Financial text may need specialized models

### "What happens when you change embedding models?"
- ALL vectors must be re-computed (they're incompatible between models)
- Plan for this: store raw text + metadata alongside vectors
- Version your embedding model

### "How do embeddings relate to LLM understanding?"
- Embeddings capture semantic similarity but NOT reasoning
- Two texts can be semantically similar but logically contradictory
- Embeddings are for RETRIEVAL, LLM is for REASONING

## 7. Financial Domain Considerations (D.E. Shaw)

- Standard embedding models may not understand financial jargon well
- Consider: FinBERT embeddings or fine-tuned models for financial text
- SEC filings, earnings calls → long documents → need long-context embeddings
- Ticker symbols, dates, numbers → poor embedding quality (use hybrid search)
- Structured data (tables, time series) → embeddings are NOT the right tool
