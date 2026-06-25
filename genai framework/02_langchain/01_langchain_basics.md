# LangChain Basics

## 1. What is LangChain?

LangChain is the most popular framework for building LLM-powered applications. Think of it as the "Spring Boot of GenAI" — it provides abstractions, composability, and integrations.

**Core value prop:**
- Standardized interfaces for LLMs, embeddings, vector stores
- Composability (chain components together)
- 700+ integrations (every LLM, vector DB, tool)
- Built-in patterns for RAG, agents, etc.

**Ecosystem:**
```
langchain-core    → Base abstractions (LCEL, Runnables)
langchain         → Chains, agents, retrieval strategies
langchain-openai  → OpenAI integration
langchain-community → Third-party integrations
langgraph         → Stateful multi-actor workflows
langsmith         → Observability, evaluation, tracing
```

## 2. LCEL (LangChain Expression Language)

The modern way to compose LangChain components. Uses the `|` (pipe) operator.

```python
from langchain_core.prompts import ChatPromptTemplate
from langchain_openai import ChatOpenAI
from langchain_core.output_parsers import StrOutputParser

# Define components
prompt = ChatPromptTemplate.from_messages([
    ("system", "You are a financial analyst."),
    ("human", "{question}")
])
model = ChatOpenAI(model="gpt-4o")
parser = StrOutputParser()

# Compose with pipe operator
chain = prompt | model | parser

# Invoke
result = chain.invoke({"question": "Explain P/E ratio"})
```

### Why LCEL?
- Declarative composition (read left to right)
- Automatic streaming support
- Automatic batch/async support
- Built-in retry and fallback
- Easy to inspect and debug

### LCEL Primitives:

```python
from langchain_core.runnables import (
    RunnablePassthrough,   # Pass input through unchanged
    RunnableLambda,        # Wrap any function
    RunnableParallel,      # Run multiple chains in parallel
    RunnableBranch,        # Conditional routing
)

# Parallel execution
chain = RunnableParallel(
    summary=summary_chain,
    sentiment=sentiment_chain,
    entities=entity_chain
)
# All three run concurrently, result is a dict

# Conditional routing
chain = RunnableBranch(
    (lambda x: x["type"] == "technical", technical_chain),
    (lambda x: x["type"] == "business", business_chain),
    default_chain  # fallback
)
```

## 3. Core Abstractions

### Chat Models:
```python
from langchain_openai import ChatOpenAI
from langchain_anthropic import ChatAnthropic

# All implement the same interface
gpt4 = ChatOpenAI(model="gpt-4o", temperature=0)
claude = ChatAnthropic(model="claude-sonnet-4-20250514")

# Structured output (function calling)
from pydantic import BaseModel

class StockAnalysis(BaseModel):
    ticker: str
    sentiment: str  # "bullish" | "bearish" | "neutral"
    confidence: float
    reasoning: str

structured_llm = gpt4.with_structured_output(StockAnalysis)
result = structured_llm.invoke("Analyze AAPL earnings beat")
# Returns StockAnalysis object, not free text
```

### Prompts:
```python
from langchain_core.prompts import ChatPromptTemplate, MessagesPlaceholder

# Simple template
prompt = ChatPromptTemplate.from_template("Summarize: {text}")

# Chat messages with history
prompt = ChatPromptTemplate.from_messages([
    ("system", "You are a helpful assistant."),
    MessagesPlaceholder(variable_name="chat_history"),
    ("human", "{input}")
])

# With few-shot examples
from langchain_core.prompts import FewShotChatMessagePromptTemplate

examples = [
    {"input": "AAPL up 5%", "output": "Bullish"},
    {"input": "Revenue miss", "output": "Bearish"},
]
few_shot = FewShotChatMessagePromptTemplate(
    example_prompt=ChatPromptTemplate.from_messages([
        ("human", "{input}"), ("ai", "{output}")
    ]),
    examples=examples
)
```

### Output Parsers:
```python
from langchain_core.output_parsers import (
    StrOutputParser,       # Raw string
    JsonOutputParser,      # Parse JSON
    PydanticOutputParser,  # Parse to Pydantic model
)

# JSON with schema
from langchain_core.pydantic_v1 import BaseModel, Field

class Analysis(BaseModel):
    summary: str = Field(description="Brief summary")
    risk_level: str = Field(description="low, medium, high")

parser = PydanticOutputParser(pydantic_object=Analysis)
# parser.get_format_instructions() → adds schema to prompt
```

### Retrievers:
```python
from langchain_openai import OpenAIEmbeddings
from langchain_community.vectorstores import FAISS

# Any vector store becomes a retriever
vectorstore = FAISS.from_documents(docs, OpenAIEmbeddings())
retriever = vectorstore.as_retriever(
    search_type="mmr",          # Maximum Marginal Relevance (diversity)
    search_kwargs={"k": 5, "fetch_k": 20}
)

# Use in a chain
docs = retriever.invoke("quarterly earnings")
```

## 4. RAG Chain Pattern

```python
from langchain_core.prompts import ChatPromptTemplate
from langchain_core.runnables import RunnablePassthrough
from langchain_openai import ChatOpenAI, OpenAIEmbeddings
from langchain_community.vectorstores import FAISS

# Setup
vectorstore = FAISS.from_documents(docs, OpenAIEmbeddings())
retriever = vectorstore.as_retriever(search_kwargs={"k": 5})

# Prompt
prompt = ChatPromptTemplate.from_template("""
Answer based on the context below. If unsure, say "I don't know."

Context: {context}
Question: {question}
""")

# Chain
def format_docs(docs):
    return "\n\n".join(d.page_content for d in docs)

rag_chain = (
    {"context": retriever | format_docs, "question": RunnablePassthrough()}
    | prompt
    | ChatOpenAI(model="gpt-4o")
    | StrOutputParser()
)

answer = rag_chain.invoke("What was Q4 revenue?")
```

## 5. Streaming

```python
# Stream tokens as they're generated
async for chunk in rag_chain.astream("What was Q4 revenue?"):
    print(chunk, end="", flush=True)

# Stream events (for complex chains)
async for event in rag_chain.astream_events("query", version="v2"):
    if event["event"] == "on_chat_model_stream":
        print(event["data"]["chunk"].content, end="")
    elif event["event"] == "on_retriever_end":
        print(f"\nRetrieved {len(event['data']['output'])} docs")
```

## 6. Document Loaders

```python
from langchain_community.document_loaders import (
    PyPDFLoader,
    UnstructuredHTMLLoader,
    CSVLoader,
    WebBaseLoader,
    DirectoryLoader,
)

# PDF
loader = PyPDFLoader("earnings_report.pdf")
docs = loader.load()  # List[Document] with page_content + metadata

# Directory of files
loader = DirectoryLoader("./reports/", glob="**/*.pdf", loader_cls=PyPDFLoader)
docs = loader.load()

# Web
loader = WebBaseLoader("https://example.com/article")
docs = loader.load()
```

## 7. Key Patterns

### Fallback:
```python
# If primary model fails, fall back to secondary
primary = ChatOpenAI(model="gpt-4o")
fallback = ChatAnthropic(model="claude-sonnet-4-20250514")

model_with_fallback = primary.with_fallbacks([fallback])
```

### Retry:
```python
from langchain_core.runnables import RunnableRetry

chain_with_retry = chain.with_retry(
    stop_after_attempt=3,
    wait_exponential_jitter=True
)
```

### Batch Processing:
```python
# Process multiple inputs concurrently
questions = ["Q1?", "Q2?", "Q3?"]
results = chain.batch(questions, config={"max_concurrency": 5})
```

## 8. LangSmith (Observability)

```python
import os
os.environ["LANGCHAIN_TRACING_V2"] = "true"
os.environ["LANGCHAIN_API_KEY"] = "..."

# Now every chain invocation is traced automatically
# See: latency, tokens, cost, intermediate steps, errors
```

**What LangSmith gives you:**
- Full trace of every LLM call (inputs, outputs, latency)
- Token usage and cost tracking
- Error debugging with full context
- Evaluation datasets and automated testing
- Comparison between prompt versions

## 9. When to Use LangChain (and when NOT to)

### Use LangChain when:
- Rapid prototyping (get to working demo fast)
- Need many integrations (switch between providers)
- Standard patterns (RAG, agents, chains)
- Team needs shared abstractions

### Don't use LangChain when:
- Simple API call to one LLM (just use the SDK directly)
- Need full control over prompts and retries
- Performance-critical (extra abstraction overhead)
- Minimal dependencies preferred

### Alternatives:
- **LlamaIndex**: Better for complex RAG specifically
- **Raw SDK** (openai, anthropic): Maximum control, minimal deps
- **Haystack**: More opinionated, pipelines-first
- **Semantic Kernel** (Microsoft): .NET/Python, enterprise focus

## 10. Interview Talking Points

- "LangChain is about composability — snap together components with |"
- "LCEL gives you streaming, batching, and async for free"
- "In production, I'd use LangSmith for observability from day 1"
- "The with_structured_output() is key for reliable function calling"
- "For simple use cases, LangChain is overhead — I'd use the raw SDK"
- "The real value is integrations and switching between providers"
