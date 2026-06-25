# Chunking Strategies

## 1. Why Chunking Matters

Chunking is the MOST underrated component of RAG. Bad chunking = bad retrieval = bad answers.

**The core tension:**
- Too small → loses context, fragments information
- Too large → dilutes relevance, wastes tokens, retrieval less precise
- Wrong boundaries → splits related information across chunks

## 2. Chunking Methods (Simple → Advanced)

### A. Fixed-Size Chunking
```python
# Split every N characters with overlap
chunk_size = 500  # characters
overlap = 50

chunks = []
for i in range(0, len(text), chunk_size - overlap):
    chunks.append(text[i:i + chunk_size])
```
- **Pros**: Simple, predictable chunk sizes
- **Cons**: Splits mid-sentence, mid-paragraph, mid-idea
- **Use when**: Quick prototype, uniform text

### B. Recursive Character Splitting (LangChain default)
```python
from langchain.text_splitter import RecursiveCharacterTextSplitter

splitter = RecursiveCharacterTextSplitter(
    chunk_size=500,
    chunk_overlap=50,
    separators=["\n\n", "\n", ". ", " ", ""]
)
# Tries to split on paragraph, then sentence, then word
```
- **Pros**: Respects natural boundaries, good default
- **Cons**: Chunk sizes vary, may still split ideas
- **Use when**: General purpose, good starting point

### C. Semantic Chunking
```python
# Split based on embedding similarity between sentences
from langchain_experimental.text_splitter import SemanticChunker

chunker = SemanticChunker(
    embeddings=OpenAIEmbeddings(),
    breakpoint_threshold_type="percentile",
    breakpoint_threshold_amount=95
)
# Groups sentences that are semantically similar
```
- **Pros**: Chunks align with topic boundaries
- **Cons**: Slower (requires embedding each sentence), variable sizes
- **Use when**: Documents with clear topic shifts

### D. Document-Structure-Aware Chunking
```python
# Markdown/HTML: split by headers
from langchain.text_splitter import MarkdownHeaderTextSplitter

headers_to_split_on = [
    ("#", "Header 1"),
    ("##", "Header 2"),
    ("###", "Header 3"),
]
splitter = MarkdownHeaderTextSplitter(headers_to_split_on)
```
- **Pros**: Respects document structure
- **Cons**: Sections may be too large/small
- **Use when**: Structured documents (docs, wikis, reports)

### E. Agentic/LLM-based Chunking
```
Prompt: "Split this document into self-contained chunks, 
each about one specific topic or concept. Mark boundaries."
```
- **Pros**: Best semantic boundaries
- **Cons**: Expensive, slow, non-deterministic
- **Use when**: High-value documents where quality matters most

## 3. Chunk Size Selection

### Guidelines:
```
Embedding model context limit → hard upper bound
Typical sweet spots:
  - Short passages (100-200 tokens): Best for Q&A with specific answers
  - Medium chunks (200-500 tokens): Best general purpose
  - Long chunks (500-1000 tokens): Best for summarization, context-heavy tasks
```

### Empirical approach:
1. Create test set of (question, expected_answer, source_doc) triples
2. Try chunk sizes: 128, 256, 512, 1024 tokens
3. Measure retrieval recall@5 for each
4. Pick the size with best recall

### The Overlap Question:
- Overlap prevents information loss at boundaries
- Typical: 10-20% of chunk size
- Too much overlap → redundant storage, diluted search results
- Too little → context lost at boundaries

## 4. Advanced Chunking Patterns

### Parent-Child (Small-to-Big):
```
Index: Small chunks (100-200 tokens) for precise retrieval
Return: Parent chunk/document (500-1000 tokens) for full context

Query → Match small chunk → Return parent chunk to LLM
```

```python
from langchain.retrievers import ParentDocumentRetriever
from langchain.storage import InMemoryStore

# Small chunks for search, large chunks for context
child_splitter = RecursiveCharacterTextSplitter(chunk_size=200)
parent_splitter = RecursiveCharacterTextSplitter(chunk_size=1000)

retriever = ParentDocumentRetriever(
    vectorstore=vectorstore,
    docstore=InMemoryStore(),
    child_splitter=child_splitter,
    parent_splitter=parent_splitter,
)
```

### Sentence Window:
```
Index: Individual sentences
Return: Sentence + N surrounding sentences (window)

"The revenue grew 25%" → return surrounding 5 sentences for context
```

### Proposition-based Chunking:
```
Step 1: Extract atomic propositions from text
  "Company X was founded in 2010. It's headquartered in NYC."
  → ["Company X was founded in 2010", 
     "Company X is headquartered in NYC"]
  
Step 2: Index propositions (very precise retrieval)
Step 3: On match, return original paragraph
```

### Hierarchical/Recursive:
```
Level 1: Document summary (1 chunk per doc)
Level 2: Section summaries (1 chunk per section)  
Level 3: Detailed chunks (standard splitting)

Search: Start at Level 1, drill into Level 3 for relevant sections
```

## 5. Document-Type Specific Strategies

### Code:
```python
from langchain.text_splitter import Language, RecursiveCharacterTextSplitter

splitter = RecursiveCharacterTextSplitter.from_language(
    language=Language.PYTHON,
    chunk_size=1000,
    chunk_overlap=100
)
# Splits on class/function boundaries
```

### Tables (Financial Reports):
- DON'T split tables across chunks
- Serialize table as markdown or JSON
- Include table caption/title in the chunk
- Consider: one chunk per table + surrounding context

### PDFs:
- Use layout-aware extraction (not just text extraction)
- Tools: Unstructured.io, LlamaParse, DocTR
- Preserve headers, footers, page numbers as metadata
- Handle multi-column layouts

### Conversations/Threads:
- Keep full conversation turns together
- Include speaker attribution in chunk
- Time-window based splitting

## 6. Metadata Enrichment

Every chunk should have metadata for filtering:

```python
chunk = {
    "content": "Revenue grew 25% year-over-year...",
    "metadata": {
        "source": "AAPL_10K_2024.pdf",
        "page": 15,
        "section": "Financial Highlights",
        "doc_type": "10-K filing",
        "company": "AAPL",
        "year": 2024,
        "quarter": None,
        "chunk_index": 42,
        "total_chunks": 156
    }
}
```

### Auto-enrichment with LLM:
```
For each chunk, ask LLM:
- What topics does this cover? → topic tags
- What time period is discussed? → temporal metadata
- Generate a summary/title → alternate search text
- What questions would this chunk answer? → hypothetical queries
```

## 7. Evaluation Framework for Chunking

```python
def evaluate_chunking_strategy(strategy, test_set):
    """
    test_set: List of (question, ground_truth_answer, source_doc_id)
    """
    chunks = strategy.split(documents)
    vectorstore = embed_and_index(chunks)
    
    metrics = {
        "retrieval_recall@5": [],
        "answer_in_context": [],
        "context_precision": []
    }
    
    for question, answer, source_id in test_set:
        retrieved = vectorstore.similarity_search(question, k=5)
        
        # Does the answer appear in retrieved chunks?
        answer_found = any(answer in chunk.page_content for chunk in retrieved)
        metrics["answer_in_context"].append(answer_found)
        
        # Are retrieved chunks from the correct source?
        correct_source = sum(1 for c in retrieved if c.metadata["source"] == source_id)
        metrics["context_precision"].append(correct_source / 5)
    
    return {k: mean(v) for k, v in metrics.items()}
```

## 8. Interview Talking Points

- "Chunking is where most RAG systems fail silently"
- "I always start with recursive splitting, then evaluate and iterate"
- "The right chunk size depends on the question type, not just the document"
- "Metadata filtering is as important as vector similarity"
- "For financial docs: tables need special handling, never split a table"
- "Parent-child retrieval gives you precision AND context"
