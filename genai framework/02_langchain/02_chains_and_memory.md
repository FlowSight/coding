# Chains & Memory

## 1. What are Chains?

Chains are sequences of operations composed together. In modern LangChain, chains are built with LCEL (pipe operator), but understanding the concept matters.

```
Simple chain:    Prompt → LLM → Parser
RAG chain:       Retriever → Format → Prompt → LLM → Parser
Sequential:      Chain1 → Chain2 → Chain3
Branching:       Router → [Chain A | Chain B | Chain C]
```

## 2. Chain Patterns

### Sequential Chain:
```python
# Step 1: Extract entities
extract_chain = extract_prompt | llm | JsonOutputParser()

# Step 2: Analyze each entity
analyze_chain = analyze_prompt | llm | StrOutputParser()

# Step 3: Combine - output of step 1 feeds into step 2
full_chain = extract_chain | analyze_chain
```

### Parallel Chain (Fan-out):
```python
from langchain_core.runnables import RunnableParallel

# Run multiple analyses simultaneously
analysis = RunnableParallel(
    sentiment=sentiment_chain,
    entities=entity_chain,
    summary=summary_chain,
    risk=risk_chain
)

result = analysis.invoke({"text": "AAPL earnings report..."})
# result = {"sentiment": "...", "entities": [...], "summary": "...", "risk": "..."}
```

### Router Chain (Conditional):
```python
from langchain_core.runnables import RunnableBranch

# Route based on query type
router = RunnableBranch(
    (lambda x: "price" in x["query"].lower(), price_lookup_chain),
    (lambda x: "compare" in x["query"].lower(), comparison_chain),
    (lambda x: "risk" in x["query"].lower(), risk_analysis_chain),
    general_qa_chain  # default fallback
)
```

### Map-Reduce Chain:
```python
# Process each document independently, then combine
map_chain = map_prompt | llm | StrOutputParser()  # Per document

def map_reduce(docs, question):
    # Map: summarize each doc
    summaries = map_chain.batch([
        {"doc": d.page_content, "question": question} for d in docs
    ])
    # Reduce: combine summaries into final answer
    return reduce_chain.invoke({
        "summaries": "\n".join(summaries),
        "question": question
    })
```

### Refine Chain:
```python
# Iteratively refine answer with each document
def refine(docs, question):
    answer = ""
    for doc in docs:
        answer = refine_chain.invoke({
            "existing_answer": answer,
            "new_context": doc.page_content,
            "question": question
        })
    return answer
```

## 3. Memory (Conversation State)

Memory allows chains to maintain state across interactions (multi-turn conversations).

### The Problem:
LLMs are stateless. Each API call has NO memory of previous calls. We must explicitly include conversation history.

### Modern Approach (Message History):
```python
from langchain_core.prompts import ChatPromptTemplate, MessagesPlaceholder
from langchain_core.chat_history import BaseChatMessageHistory
from langchain_community.chat_message_histories import ChatMessageHistory
from langchain_core.runnables.history import RunnableWithMessageHistory

# 1. Define prompt with history placeholder
prompt = ChatPromptTemplate.from_messages([
    ("system", "You are a financial advisor."),
    MessagesPlaceholder(variable_name="chat_history"),
    ("human", "{input}")
])

chain = prompt | ChatOpenAI(model="gpt-4o") | StrOutputParser()

# 2. Store for message histories (keyed by session_id)
store = {}

def get_session_history(session_id: str) -> BaseChatMessageHistory:
    if session_id not in store:
        store[session_id] = ChatMessageHistory()
    return store[session_id]

# 3. Wrap chain with message history
chain_with_history = RunnableWithMessageHistory(
    chain,
    get_session_history,
    input_messages_key="input",
    history_messages_key="chat_history"
)

# 4. Use with session ID
config = {"configurable": {"session_id": "user_123"}}
chain_with_history.invoke({"input": "What's a good ETF?"}, config=config)
chain_with_history.invoke({"input": "What about bonds?"}, config=config)
# Second call has context of first
```

## 4. Memory Types

### Buffer Memory (Full History):
```
Store: All messages verbatim
Pros: Complete context
Cons: Grows unbounded, hits context limit
Use: Short conversations (<20 turns)
```

### Window Memory (Last N turns):
```python
from langchain.memory import ConversationBufferWindowMemory

memory = ConversationBufferWindowMemory(k=10)  # Last 10 exchanges
# Pros: Bounded size
# Cons: Forgets earlier context
# Use: Customer support, general chat
```

### Summary Memory:
```python
from langchain.memory import ConversationSummaryMemory

memory = ConversationSummaryMemory(llm=ChatOpenAI())
# After each turn, LLM summarizes the conversation so far
# Pros: Unbounded history in fixed tokens
# Cons: Lossy, extra LLM call per turn, latency
# Use: Long conversations where gist matters
```

### Summary + Buffer (Hybrid):
```python
from langchain.memory import ConversationSummaryBufferMemory

memory = ConversationSummaryBufferMemory(
    llm=ChatOpenAI(),
    max_token_limit=2000
)
# Recent messages: kept verbatim
# Older messages: summarized
# Best of both worlds
```

### Entity Memory:
```python
from langchain.memory import ConversationEntityMemory

memory = ConversationEntityMemory(llm=ChatOpenAI())
# Tracks entities mentioned in conversation
# "AAPL price is $198" → stores {AAPL: {price: $198}}
# Use: When tracking facts about specific things
```

### Vector Store Memory:
```python
# Store all messages in vector DB
# Retrieve only relevant past messages for current query
# Pros: Scales to very long histories, relevance-based
# Cons: May miss important sequential context
# Use: Very long conversations, knowledge workers
```

## 5. Memory in Production

### Persistent Storage:
```python
# Don't use in-memory dicts in production!
# Options:
# - Redis (fast, TTL support)
# - PostgreSQL (durable, queryable)
# - MongoDB (flexible schema)
# - DynamoDB (serverless scale)

from langchain_community.chat_message_histories import RedisChatMessageHistory

def get_session_history(session_id: str):
    return RedisChatMessageHistory(
        session_id=session_id,
        url="redis://localhost:6379"
    )
```

### Memory Management Strategies:
```
1. Token budget: Keep history within X tokens (e.g., 4000)
2. Relevance filtering: Only include messages relevant to current query
3. Hierarchical: Summary of old + verbatim recent
4. Time-based: Expire old conversations after N hours
5. User-triggered: Let user "start fresh" or "remember this"
```

### Context Window Budget:
```
Total context window: 128K tokens (GPT-4o)

Allocation:
  System prompt:     500 tokens (fixed)
  Conversation history: 2000-4000 tokens (managed)
  Retrieved context: 3000-5000 tokens (from RAG)
  User message:      200 tokens (current turn)
  Output reserve:    1000 tokens (for response)
  ─────────────────────────────────
  Available for docs: ~118K tokens (rarely used fully)
```

## 6. State Management Patterns

### Conversation with RAG:
```python
# RAG chain that also maintains conversation history
rag_with_memory = (
    RunnablePassthrough.assign(
        chat_history=lambda x: get_formatted_history(x["session_id"]),
        context=lambda x: retriever.invoke(x["input"])
    )
    | prompt  # Includes chat_history + context + input
    | llm
    | StrOutputParser()
)
```

### Contextualizing Questions (History-aware Retrieval):
```python
# Problem: "What about their revenue?" - "their" refers to previous context
# Solution: Rewrite question using history

contextualize_prompt = ChatPromptTemplate.from_messages([
    ("system", "Rewrite the question to be standalone, using chat history for context."),
    MessagesPlaceholder("chat_history"),
    ("human", "{input}")
])

# "What about their revenue?" + history mentioning Apple
# → "What was Apple's revenue?"
contextualize_chain = contextualize_prompt | llm | StrOutputParser()
```

## 7. Callbacks and Hooks

```python
from langchain_core.callbacks import BaseCallbackHandler

class CostTracker(BaseCallbackHandler):
    def __init__(self):
        self.total_tokens = 0
        self.total_cost = 0
    
    def on_llm_end(self, response, **kwargs):
        usage = response.llm_output.get("token_usage", {})
        self.total_tokens += usage.get("total_tokens", 0)
        # Calculate cost based on model pricing
        
    def on_chain_error(self, error, **kwargs):
        # Alert, log, retry logic
        pass

tracker = CostTracker()
chain.invoke(input, config={"callbacks": [tracker]})
```

## 8. Anti-patterns to Avoid

| Anti-pattern | Problem | Fix |
|-------------|---------|-----|
| Unbounded history | Context window overflow | Use window or summary memory |
| History in prompt template | Mixing concerns | Use MessagesPlaceholder |
| No session isolation | Users see each other's history | Key history by session ID |
| Memory in application state | Lost on restart | Use persistent store (Redis/DB) |
| Including all history for RAG | Retrieval noise | Contextualize question first |
| No token counting | Silent truncation | Monitor and manage budget |

## 9. Interview Talking Points

- "Memory is about managing the context window budget efficiently"
- "In production, I'd use summary+buffer: recent messages verbatim, older ones summarized"
- "History-aware retrieval is crucial — 'it' and 'they' references need resolution"
- "I'd persist to Redis with TTL for session management"
- "The key insight: LLMs are stateless, we must engineer state explicitly"
- "For long conversations, vector store memory with relevance retrieval scales best"
