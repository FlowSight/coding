# Agents & Tools in LangChain

## 1. What is an Agent?

An agent is an LLM that can **decide which actions to take** and **use tools** to accomplish tasks. Unlike chains (fixed sequence), agents have dynamic control flow.

```
Chain:  Input → Step1 → Step2 → Step3 → Output (fixed path)
Agent:  Input → Think → Act → Observe → Think → Act → ... → Output (dynamic)
```

## 2. Agent Loop (ReAct Pattern)

```
while not done:
    1. THINK: LLM reasons about what to do next
    2. ACT: LLM selects a tool and provides arguments
    3. OBSERVE: Tool executes, returns result
    4. THINK: LLM evaluates result, decides next step
```

```python
# Example trace:
# Thought: I need to find AAPL's current price
# Action: stock_price_lookup(ticker="AAPL")
# Observation: AAPL is trading at $198.50
# Thought: Now I need to calculate the P/E ratio. I need earnings.
# Action: get_financials(ticker="AAPL", metric="EPS_TTM")
# Observation: AAPL trailing 12-month EPS is $6.57
# Thought: P/E = Price / EPS = 198.50 / 6.57 = 30.2
# Final Answer: AAPL's current P/E ratio is approximately 30.2
```

## 3. Tools

A tool is a function the LLM can call. It has:
- **Name**: How the LLM refers to it
- **Description**: When to use it (LLM reads this!)
- **Schema**: Input parameters (JSON Schema / Pydantic)
- **Function**: The actual implementation

```python
from langchain_core.tools import tool
from pydantic import BaseModel, Field

# Simple tool
@tool
def get_stock_price(ticker: str) -> str:
    """Get the current stock price for a given ticker symbol.
    Use this when the user asks about current prices."""
    # In production: call actual API
    return f"{ticker} is trading at $198.50"

# Tool with structured input
class TradeInput(BaseModel):
    ticker: str = Field(description="Stock ticker symbol")
    action: str = Field(description="buy or sell")
    quantity: int = Field(description="Number of shares")

@tool(args_schema=TradeInput)
def execute_trade(ticker: str, action: str, quantity: int) -> str:
    """Execute a stock trade. Only use when user explicitly confirms."""
    return f"Executed: {action} {quantity} shares of {ticker}"
```

### Built-in Tools:
```python
from langchain_community.tools import (
    DuckDuckGoSearchRun,   # Web search
    WikipediaQueryRun,     # Wikipedia
    PythonREPLTool,        # Execute Python code
)
from langchain_community.utilities import SQLDatabase
from langchain_community.tools.sql_database import QuerySQLDatabaseTool
```

## 4. Function Calling (Modern Approach)

Modern LLMs natively support "function calling" / "tool use" — structured tool invocation.

```python
from langchain_openai import ChatOpenAI

# Bind tools to model
llm = ChatOpenAI(model="gpt-4o")
llm_with_tools = llm.bind_tools([get_stock_price, execute_trade])

# Model returns tool calls (not free text)
response = llm_with_tools.invoke("What's AAPL trading at?")
# response.tool_calls = [{"name": "get_stock_price", "args": {"ticker": "AAPL"}}]
```

### Why function calling > free-text tool use:
- Structured JSON output (no parsing errors)
- Model trained specifically for this
- Can call multiple tools in one turn
- Type-safe arguments

## 5. Building an Agent (Modern LangChain)

```python
from langchain_openai import ChatOpenAI
from langchain_core.messages import HumanMessage, SystemMessage
from langgraph.prebuilt import create_react_agent

# Define tools
tools = [get_stock_price, get_financials, search_news]

# Create agent
model = ChatOpenAI(model="gpt-4o")
agent = create_react_agent(
    model=model,
    tools=tools,
    state_modifier="You are a financial analyst assistant. "
                   "Always cite your sources."
)

# Run
result = agent.invoke({
    "messages": [HumanMessage(content="Analyze AAPL's valuation")]
})
```

### Agent with Memory:
```python
from langgraph.checkpoint.memory import MemorySaver

memory = MemorySaver()
agent = create_react_agent(model, tools, checkpointer=memory)

config = {"configurable": {"thread_id": "session_1"}}
agent.invoke({"messages": [HumanMessage("What's AAPL at?")]}, config)
agent.invoke({"messages": [HumanMessage("Compare it to MSFT")]}, config)
# Second call has context from first
```

## 6. Tool Design Best Practices

### Good tool descriptions (LLM reads these!):
```python
@tool
def search_sec_filings(
    company: str,
    filing_type: str = "10-K",
    year: int = 2024
) -> str:
    """Search SEC EDGAR for company filings.
    
    Use this tool when:
    - User asks about financial statements, earnings, or regulatory filings
    - You need official financial data (not news or opinions)
    
    Do NOT use when:
    - User asks about stock price (use get_stock_price instead)
    - User asks about news or sentiment (use search_news instead)
    
    Args:
        company: Company name or ticker (e.g., "Apple" or "AAPL")
        filing_type: Type of filing - "10-K" (annual), "10-Q" (quarterly), "8-K" (current)
        year: Filing year (default: current year)
    """
    pass
```

### Tool Design Principles:
1. **Clear description**: Tell LLM WHEN to use (and when NOT to)
2. **Minimal parameters**: Fewer args = fewer mistakes
3. **Typed inputs**: Use Pydantic for validation
4. **Error handling**: Return helpful error messages (LLM will retry)
5. **Idempotent when possible**: Safe to retry
6. **Scoped permissions**: Don't give tools more access than needed

## 7. Tool Error Handling

```python
@tool
def risky_operation(params: str) -> str:
    """Perform a risky operation."""
    try:
        result = do_something(params)
        return f"Success: {result}"
    except ValidationError as e:
        return f"Error: Invalid parameters - {e}. Please check the input format."
    except NotFoundError:
        return f"Error: No results found for '{params}'. Try a different query."
    except Exception as e:
        return f"Error: Operation failed - {str(e)}. Please try again."
    # Return error as string so agent can reason about it and retry
```

## 8. Human-in-the-Loop

```python
from langgraph.prebuilt import create_react_agent

# Interrupt before executing dangerous tools
agent = create_react_agent(
    model=model,
    tools=tools,
    interrupt_before=["execute_trade"]  # Pause for human approval
)

# Run until interruption
result = agent.invoke({"messages": [HumanMessage("Buy 100 AAPL")]})
# Agent proposes trade → pauses

# Human reviews and approves
agent.invoke(None, config)  # Resume execution
```

## 9. Multi-tool Orchestration

### Tool Selection Strategies:
```python
# The LLM decides which tools to use. Help it with:

# 1. Clear tool categories
financial_tools = [get_stock_price, get_financials, get_earnings]
research_tools = [search_news, search_sec_filings, search_analyst_reports]
action_tools = [execute_trade, set_alert, create_watchlist]

# 2. Tool routing (pre-classify query, then give relevant tools)
def route_tools(query):
    if needs_research(query):
        return research_tools
    elif needs_action(query):
        return action_tools + financial_tools  # Need data for actions
    else:
        return financial_tools

# 3. Limit tool count (too many tools confuses the LLM)
# Ideal: 5-10 tools. Max: ~20. Beyond that: route first.
```

### Parallel Tool Calls:
```python
# Modern models can call multiple tools in one turn
# GPT-4o: "Get AAPL and MSFT prices" → two parallel tool calls

response = llm_with_tools.invoke("Compare AAPL and MSFT prices")
# response.tool_calls = [
#   {"name": "get_stock_price", "args": {"ticker": "AAPL"}},
#   {"name": "get_stock_price", "args": {"ticker": "MSFT"}}
# ]
```

## 10. Agent Architectures

### Simple ReAct:
```
LLM → Tool → LLM → Tool → ... → Final Answer
Best for: Single task with clear tool needs
```

### Plan-then-Execute:
```
LLM (Planner) → [Plan: Step1, Step2, Step3]
    → Execute Step1 → Execute Step2 → Execute Step3
    → LLM (Synthesizer) → Final Answer
Best for: Complex multi-step tasks
```

### Router Agent:
```
LLM (Router) → Classify query type
    → Financial Agent (if financial)
    → Research Agent (if research)
    → General Agent (if general)
Best for: Diverse query types, specialized sub-agents
```

## 11. Limitations and Gotchas

| Issue | Description | Mitigation |
|-------|-------------|------------|
| Infinite loops | Agent keeps calling tools without converging | Max iterations limit |
| Wrong tool selection | LLM picks wrong tool | Better descriptions, fewer tools |
| Hallucinated tool args | LLM invents parameters | Strict schema validation |
| Cost explosion | Agent makes too many LLM calls | Budget limits, simpler models for routing |
| Slow execution | Sequential tool calls | Allow parallel calls, cache results |
| Security | Agent access to dangerous tools | Permissions, human-in-the-loop |

### Safety Pattern:
```python
# Always limit iterations and cost
agent = create_react_agent(
    model=model,
    tools=tools,
    # Safety limits
    recursion_limit=10,  # Max tool call rounds
)
```

## 12. Interview Talking Points

- "Agents are about giving LLMs agency — dynamic control flow vs fixed chains"
- "Function calling is the modern approach — structured, reliable, type-safe"
- "Tool descriptions are prompts — they determine if the LLM picks the right tool"
- "In production: limit iterations, require human approval for actions, track cost"
- "The key question: does the task need dynamic decisions? If fixed steps work, use a chain"
- "For D.E. Shaw: an agent could dynamically gather market data, run analysis, and propose trades — but execution always needs human approval"
