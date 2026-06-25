# Vector Databases

## 1. What is a Vector Database?

A specialized database optimized for storing, indexing, and querying high-dimensional vectors (embeddings). Unlike traditional DBs that match on exact values, vector DBs find "similar" items.

```
Traditional DB:  SELECT * FROM docs WHERE category = 'finance'
Vector DB:       Find 10 documents most similar to this query vector
```

## 2. Landscape (2024-2025)

### Purpose-built Vector DBs:

| Database | Type | Key Feature | Best For |
|----------|------|-------------|----------|
| **Pinecone** | Managed cloud | Zero-ops, fast | Production, teams without infra expertise |
| **Weaviate** | Open source + cloud | Hybrid search native | Complex queries, multi-modal |
| **Qdrant** | Open source + cloud | Rust-based, fast | Performance-critical apps |
| **Milvus/Zilliz** | Open source + cloud | Billion-scale | Very large datasets |
| **ChromaDB** | Open source | Developer-friendly | Prototyping, small scale |

### Vector extensions on existing DBs:

| Database | Extension | When to Use |
|----------|-----------|-------------|
| **PostgreSQL** | pgvector | Already using Postgres, <10M vectors |
| **Redis** | Redis Vector | Need caching + vectors together |
| **Elasticsearch** | Dense vector field | Already using ES for search |
| **MongoDB** | Atlas Vector Search | Already using MongoDB |

### In-memory / Local:

| Library | Use Case |
|---------|----------|
| **FAISS** (Meta) | Research, prototyping, embedded |
| **Annoy** (Spotify) | Read-heavy, memory-mapped |
| **HNSWlib** | Simple HNSW implementation |

## 3. Key Features to Evaluate

### Must-haves for production:
1. **Metadata filtering**: Filter vectors by attributes BEFORE similarity search
2. **Hybrid search**: Combine vector similarity + keyword search
3. **Scalability**: Handle growth (10K → 10M → 1B vectors)
4. **CRUD operations**: Update/delete vectors without reindexing
5. **High availability**: Replication, failover

### Nice-to-haves:
- Multi-tenancy (namespace isolation)
- RBAC (access control)
- Backup/restore
- Monitoring/observability
- Tunable consistency

## 4. Architecture Deep Dive

### How Vector Search Works Internally:

```
┌────────────────────────────────────────────┐
│           Query Processing                  │
│                                            │
│  Query Vector → Pre-filter (metadata)      │
│       ↓                                    │
│  ANN Index Traversal (HNSW/IVF)           │
│       ↓                                    │
│  Candidate Set (approximate)               │
│       ↓                                    │
│  Post-filter + Reranking (optional)        │
│       ↓                                    │
│  Top-K Results + Scores                    │
└────────────────────────────────────────────┘
```

### Index Types:

**HNSW (default for most DBs):**
- Navigable graph with skip-list-like hierarchy
- Parameters: `M` (connections per node), `efConstruction` (build quality)
- Trade-off: More memory, best recall
- Query: O(log n)

**IVF (Inverted File):**
- K-means clustering of vectors into cells
- Parameters: `nlist` (number of clusters), `nprobe` (clusters to search)
- Trade-off: Less memory, need to tune nprobe

**Quantization (PQ, SQ):**
- Compress vectors to reduce memory
- Product Quantization: split into subspaces, codebook per subspace
- Scalar Quantization: reduce precision (float32 → int8)

### Memory Estimation:
```
Memory = num_vectors × (dimensions × bytes_per_dim + overhead)

Example (1M vectors, 1536-dim, float32, HNSW):
  Vectors: 1,000,000 × 1536 × 4 bytes = ~6 GB
  HNSW graph: ~2-4 GB overhead
  Total: ~8-10 GB
```

## 5. Practical Usage Patterns

### Metadata Filtering (Critical for RAG):
```python
# Pinecone example
results = index.query(
    vector=query_embedding,
    top_k=10,
    filter={
        "source": {"$eq": "10-K filing"},
        "year": {"$gte": 2023},
        "company": {"$in": ["AAPL", "GOOGL", "MSFT"]}
    }
)
```

### Hybrid Search (Vector + Keyword):
```python
# Weaviate example - combines BM25 + vector similarity
results = client.query.get("Document", ["content", "source"]) \
    .with_hybrid(
        query="quarterly earnings growth",
        alpha=0.7  # 0 = pure keyword, 1 = pure vector
    ) \
    .with_limit(10) \
    .do()
```

### Namespace/Multi-tenancy:
```python
# Pinecone - separate namespaces per customer/use-case
index.upsert(vectors=vectors, namespace="customer_123")
index.query(vector=q, namespace="customer_123", top_k=5)
```

## 6. pgvector (PostgreSQL Extension)

Most practical for teams already using Postgres:

```sql
-- Enable extension
CREATE EXTENSION vector;

-- Create table with vector column
CREATE TABLE documents (
    id SERIAL PRIMARY KEY,
    content TEXT,
    embedding vector(1536),
    metadata JSONB,
    created_at TIMESTAMP DEFAULT NOW()
);

-- Create HNSW index
CREATE INDEX ON documents 
USING hnsw (embedding vector_cosine_ops)
WITH (m = 16, ef_construction = 64);

-- Query: find 5 most similar documents
SELECT id, content, 
       1 - (embedding <=> query_embedding) as similarity
FROM documents
WHERE metadata->>'year' = '2024'
ORDER BY embedding <=> query_embedding
LIMIT 5;
```

### pgvector operators:
- `<=>` : Cosine distance
- `<->` : L2 (Euclidean) distance
- `<#>` : Inner product (negative, for ordering)

### Limitations:
- Single-node (no distributed search)
- Performance degrades past ~5-10M vectors
- Index build can be slow for large datasets

## 7. FAISS (Facebook AI Similarity Search)

In-memory, great for prototyping and medium scale:

```python
import faiss
import numpy as np

# Create index
dimension = 1536
index = faiss.IndexFlatL2(dimension)  # Exact search (brute force)

# For scale, use HNSW:
index = faiss.IndexHNSWFlat(dimension, 32)  # 32 = M parameter

# Or IVF for billion-scale:
quantizer = faiss.IndexFlatL2(dimension)
index = faiss.IndexIVFFlat(quantizer, dimension, 1000)  # 1000 clusters
index.train(training_vectors)  # Must train on sample

# Add vectors
index.add(vectors)  # numpy array, shape (n, 1536)

# Search
distances, indices = index.search(query_vector, k=10)
```

## 8. Choosing a Vector DB

### Decision Matrix:

```
Prototyping / <100K vectors:
  → ChromaDB or FAISS (zero cost, minimal setup)

Production / <5M vectors / already have Postgres:
  → pgvector (no new infrastructure)

Production / <50M vectors / need managed:
  → Pinecone or Qdrant Cloud (managed, reliable)

Production / >100M vectors:
  → Milvus/Zilliz or Weaviate (distributed)

Need hybrid search (vector + full-text):
  → Weaviate or Elasticsearch

Financial services (compliance, on-prem):
  → Milvus (self-hosted) or pgvector
```

## 9. Performance Optimization

### Indexing:
- Batch inserts (don't insert one-by-one)
- Pre-warm index after build
- Choose right index type for your read/write ratio

### Querying:
- Use metadata pre-filtering to reduce search space
- Tune `ef_search` (HNSW) or `nprobe` (IVF) for recall/speed trade-off
- Cache frequent queries
- Use quantization if memory is constrained

### Monitoring:
- Track p50/p95/p99 query latency
- Monitor recall (periodic comparison with brute-force)
- Index fragmentation (after many updates)
- Memory/disk usage growth

## 10. Interview Questions

1. "How would you choose between Pinecone and pgvector?"
2. "Your vector search returns irrelevant results. How do you debug?"
3. "How does HNSW work and what are its trade-offs?"
4. "Design a vector search system for 1 billion documents"
5. "How do you handle real-time updates to the vector index?"
6. "Explain the trade-off between recall and latency in ANN search"
