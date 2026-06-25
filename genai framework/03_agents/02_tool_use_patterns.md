# Tool Use Patterns

## 1. Function Calling (The Foundation)

Modern LLMs are trained to emit structured tool calls instead of free text.

### How Function Calling Works:
```
1. You describe available tools (name, description, parameters schema)
2. User sends a message
3. LLM decides whether to call a tool (and which one)
4. LLM returns structured JSON: {"name": "...", "arguments": {...}}
5. Your code executes the tool
6. Tool result is sent back to LLM
7. LLM generates final response (or calls another tool)
```

### OpenAI Function Calling:
```python
tools = [
    {
        "type": "function",
        "function": {
            "name": "get_stock_price",
            "description": "Get current stock price and basic stats",
            "parameters": {
                "type": "object",
                "properties": {
                    "ticker": {
                        "type": "string",
                        "description": "Stock ticker symbol (e.g., AAPL)"
                    },
                    "include_history": {
                        "type": "boolean",
                        "description": "Include 52-week high/low",
                        "default": False
                    }
                },
                "required": ["ticker"]
            }
        }
    }
]

response = client.chat.completions.create(
    model="gpt-4o",
    messages=[{"role": "user", "content": "What's AAPL trading at?"}],
    tools=tools,
    tool_choice="auto"  # or "required" or {"type": "function", "function": {"name": "..."}}
)

# response.choices[0].message.tool_calls[0]
# → {"id": "call_123", "function": {"name": "get_stock_price", "arguments": '{"ticker": "AAPL"}'}}
```

### Parallel Function Calling:
```python
# Model can call multiple tools in one response
# "Compare AAPL and GOOGL" → two parallel tool calls

tool_calls = response.choices[0].message.tool_calls
# [
#   {"name": "get_stock_price", "arguments": {"ticker": "AAPL"}},
#   {"name": "get_stock_price", "arguments": {"ticker": "GOOGL"}}
# ]

# Execute both, return results
for call in tool_calls:
    result = execute_tool(call)
    messages.append({"role": "tool", "tool_call_id": call.id, "content": result})

# Send results back for final answer
final = client.chat.completions.create(model="gpt-4o", messages=messages)
```

## 2. Model Context Protocol (MCP)

MCP is a standard protocol for connecting LLMs to tools/data sources, developed by Anthropic.

### Why MCP?
```
Before MCP: Each tool integration is custom per LLM/framework
After MCP:  Universal protocol, any tool works with any LLM client

Tool Provider (MCP Server) ←→ MCP Protocol ←→ LLM Client (MCP Client)
```

### MCP Architecture:
```
┌──────────────┐     ┌──────────────┐     ┌──────────────┐
│  LLM Client  │────▶│  MCP Server  │────▶│  External    │
│  (Claude,    │◀────│  (Tool host) │◀────│  Service     │
│   IDE, App)  │     │              │     │  (API, DB)   │
└──────────────┘     └──────────────┘     └──────────────┘
       ▲                    │
       │                    ▼
       │              ┌──────────┐
       └──────────────│  Tools   │
                      │  Resources│
                      │  Prompts  │
                      └──────────┘
```

### MCP Primitives:
- **Tools**: Functions the LLM can call (like function calling)
- **Resources**: Data sources the LLM can read (files, DBs)
- **Prompts**: Pre-built prompt templates
- **Sampling**: Server can request LLM completions

### MCP Server Example (Python):
```python
from mcp.server import Server
from mcp.types import Tool, TextContent

server = Server("financial-tools")

@server.list_tools()
async def list_tools():
    return [
        Tool(
            name="get_stock_price",
            description="Get current stock price",
            inputSchema={
                "type": "object",
                "properties": {
                    "ticker": {"type": "string", "description": "Stock ticker"}
                },
                "required": ["ticker"]
            }
        )
    ]

@server.call_tool()
async def call_tool(name: str, arguments: dict):
    if name == "get_stock_price":
        price = await fetch_price(arguments["ticker"])
        return [TextContent(type="text", text=f"${price}")]
```

### Key MCP Benefits:
- **Portable**: Same tool works across Claude, VS Code, IDEs, custom apps
- **Secure**: Permission model, sandboxing
- **Discoverable**: Tools self-describe their capabilities
- **Composable**: Multiple MCP servers can be connected

## 3. Tool Design Patterns

### Pattern 1: Retrieval Tools
```python
@tool
def search_knowledge_base(query: str, filters: dict = None) -> str:
    """Search internal knowledge base for relevant information.
    
    Use for: Questions about company policies, procedures, past decisions.
    Returns: Top 3 most relevant passages with source citations.
    """
    results = vectorstore.similarity_search(query, k=3, filter=filters)
    return format_with_citations(results)
```

### Pattern 2: Computation Tools
```python
@tool
def calculate_portfolio_risk(
    holdings: list[dict],  # [{"ticker": "AAPL", "weight": 0.3}, ...]
    period: str = "1Y"
) -> str:
    """Calculate portfolio risk metrics (VaR, Sharpe, max drawdown).
    
    Use when user asks about portfolio risk, volatility, or performance.
    Requires: List of holdings with weights that sum to 1.0.
    """
    # Actual computation (not LLM inference)
    var_95 = compute_var(holdings, period, confidence=0.95)
    sharpe = compute_sharpe(holdings, period)
    return json.dumps({"VaR_95": var_95, "sharpe_ratio": sharpe})
```

### Pattern 3: Action Tools (Side Effects)
```python
@tool
def send_alert(
    channel: str,
    message: str,
    severity: str = "info"
) -> str:
    """Send an alert to a monitoring channel.
    
    CAUTION: This has real side effects. Only use when:
    1. User explicitly requests an alert
    2. A critical threshold is breached
    
    severity: "info", "warning", "critical"
    """
    # Validate before executing
    if severity == "critical" and not user_confirmed:
        return "REQUIRES CONFIRMATION: About to send critical alert. Please confirm."
    
    send_to_channel(channel, message, severity)
    return f"Alert sent to #{channel}: {message}"
```

### Pattern 4: Code Execution Tools
```python
@tool
def run_python_analysis(code: str) -> str:
    """Execute Python code in a sandboxed environment.
    
    Available libraries: pandas, numpy, scipy, matplotlib
    Available data: df_portfolio, df_market_data, df_trades
    
    Returns: stdout output and any generated plots.
    
    SECURITY: Code is sandboxed. No network, no filesystem access.
    """
    result = sandbox.execute(code, timeout=30)
    return result.stdout + "\n" + result.display_data
```

### Pattern 5: Confirmation/Verification Tools
```python
@tool
def verify_calculation(
    calculation: str,
    expected_result: float,
    tolerance: float = 0.01
) -> str:
    """Double-check a numerical calculation.
    
    Use AFTER performing mental math to verify accuracy.
    Helps prevent calculation errors in financial contexts.
    """
    actual = safe_eval(calculation)
    is_correct = abs(actual - expected_result) < tolerance
    return f"Calculation: {calculation} = {actual}. " \
           f"{'✓ Matches' if is_correct else '✗ MISMATCH'} expected {expected_result}"
```

## 4. Tool Composition Patterns

### Sequential Tools:
```
get_ticker("Apple") → "AAPL"
get_price("AAPL") → $198.50
get_pe_ratio("AAPL") → 30.2
```

### Fan-out Tools:
```
search("AI stocks") → [NVDA, MSFT, GOOGL, META]
[get_price(t) for t in results]  → [$950, $430, $180, $510]
```

### Conditional Tools:
```
classify_query(q) → "financial_analysis"
IF financial: use financial_tools
IF research: use search_tools
```

### Tool Chaining with Validation:
```
get_data() → validate(data) → IF valid: analyze(data) ELSE: retry
```

## 5. Tool Selection Optimization

### Problem: Too Many Tools
- LLMs degrade with >15-20 tools (confused, wrong selections)
- Each tool description consumes context tokens

### Solutions:

**1. Semantic Tool Routing:**
```python
# Embed tool descriptions, find most relevant tools for query
tool_embeddings = embed([t.description for t in all_tools])
query_embedding = embed(user_query)

relevant_tools = top_k_similar(query_embedding, tool_embeddings, k=5)
# Only give model the 5 most relevant tools
```

**2. Hierarchical Tools:**
```python
# Level 1: Category tools (always available)
@tool
def financial_data(sub_task: str) -> str:
    """Access financial data tools. Sub-tasks: price, earnings, ratios, history"""
    # Routes to specific tool internally

# Level 2: Specific tools (only available after routing)
```

**3. Tool Groups with Context:**
```python
# Based on conversation state, swap available tools
if state == "research":
    available_tools = search_tools + data_tools
elif state == "analysis":
    available_tools = computation_tools + visualization_tools
elif state == "action":
    available_tools = action_tools + confirmation_tools
```

## 6. Error Recovery

```python
class RobustToolExecutor:
    def execute(self, tool_call):
        try:
            result = tool_call.execute()
            return {"status": "success", "result": result}
        except TimeoutError:
            return {"status": "timeout", "message": "Tool took too long. Try simpler query."}
        except RateLimitError:
            # Wait and retry
            time.sleep(2)
            return self.execute(tool_call)
        except ValidationError as e:
            return {"status": "invalid_input", "message": f"Bad arguments: {e}. Fix and retry."}
        except Exception as e:
            return {"status": "error", "message": f"Tool failed: {e}. Try alternative approach."}
```

## 7. Security Considerations

### Input Validation:
```python
@tool
def query_database(sql: str) -> str:
    """Run read-only SQL query."""
    # NEVER let LLM write raw SQL directly
    # Validate: only SELECT, no DDL/DML
    if not is_read_only(sql):
        return "Error: Only SELECT queries allowed"
    if contains_injection(sql):
        return "Error: Query rejected for safety"
    return execute_readonly(sql)
```

### Permission Levels:
```python
class ToolPermissions:
    READ = ["search", "get_price", "get_data"]
    WRITE = ["create_alert", "save_analysis"]
    DANGEROUS = ["execute_trade", "delete_data", "send_email"]
    
    @classmethod
    def get_allowed(cls, user_role, requires_confirmation=True):
        if user_role == "viewer":
            return cls.READ
        elif user_role == "analyst":
            return cls.READ + cls.WRITE
        elif user_role == "trader" and requires_confirmation:
            return cls.READ + cls.WRITE + cls.DANGEROUS
```

### Audit Trail:
```python
def tool_wrapper(tool_fn):
    def wrapped(*args, **kwargs):
        log_tool_call(tool_fn.__name__, args, kwargs, user=current_user)
        result = tool_fn(*args, **kwargs)
        log_tool_result(tool_fn.__name__, result)
        return result
    return wrapped
```

## 8. Interview Talking Points

- "Function calling turns free-text tool use into structured, type-safe invocations"
- "MCP is the USB of AI tools — one protocol, universal compatibility"
- "Tool descriptions are a form of prompt engineering — the LLM reads them to decide"
- "In finance: action tools always need human-in-the-loop and audit trails"
- "Too many tools confuses the model — use routing and hierarchical organization"
- "The key design question: what's the minimal set of tools to accomplish the task?"
