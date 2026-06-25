# Agent Fundamentals

## 1. What Makes an Agent Different from a Chain?

| Aspect | Chain | Agent |
|--------|-------|-------|
| Control flow | Fixed, predetermined | Dynamic, LLM-decided |
| Tool use | None or fixed sequence | Chosen at runtime |
| Iteration | Single pass | Can loop, retry, backtrack |
| Autonomy | None | Self-directed reasoning |
| Complexity | Predictable | Emergent behavior |

**An agent = LLM + Tools + Reasoning Loop + Memory**

## 2. Agent Reasoning Patterns

### ReAct (Reasoning + Acting) — Most common

```
Thought: I need to find the quarterly revenue for AAPL
Action: search_financials(ticker="AAPL", period="Q4_2024")
Observation: Apple reported $119.6B revenue in Q4 2024
Thought: Now I need to compare with Q4 2023 for growth rate
Action: search_financials(ticker="AAPL", period="Q4_2023")
Observation: Apple reported $117.2B revenue in Q4 2023
Thought: Growth = (119.6 - 117.2) / 117.2 = 2.05%
Final Answer: Apple's Q4 2024 revenue was $119.6B, growing 2.05% YoY.
```

**Why ReAct works:**
- Interleaving reasoning with action reduces hallucination
- Each observation grounds the next thought
- Explicit reasoning is inspectable/debuggable

### Plan-and-Execute

```
Step 1 (Plan): 
  "To analyze AAPL valuation:
   1. Get current price
   2. Get TTM earnings
   3. Calculate P/E
   4. Compare to sector average
   5. Assess if over/undervalued"

Step 2 (Execute): Run each step, potentially re-plan if needed
```

**When to use:**
- Complex multi-step tasks
- When you want to minimize LLM calls (plan once, execute without LLM)
- When steps can be parallelized

### Reflexion (Self-critique)

```
Attempt 1: Generate answer
Self-critique: "The answer doesn't address the time period"
Attempt 2: Generate improved answer using critique
Self-critique: "Better, but missing the comparison aspect"
Attempt 3: Generate final answer addressing all points
```

### LATS (Language Agent Tree Search)

```
Root: Initial approach
├── Branch A: Conservative analysis
│   ├── Score: 0.7
│   └── Continue? No (below threshold)
├── Branch B: Quantitative analysis
│   ├── Score: 0.9
│   └── Continue → expand further
└── Branch C: Qualitative analysis
    ├── Score: 0.6
    └── Prune
```

- Explores multiple reasoning paths (like beam search for agents)
- Scores each path
- Expands most promising
- Best for: complex problems where first approach might fail

## 3. Agent Execution Frameworks

### OpenAI Assistants API:
```python
from openai import OpenAI
client = OpenAI()

# Create assistant with tools
assistant = client.beta.assistants.create(
    name="Financial Analyst",
    instructions="You analyze financial data.",
    tools=[
        {"type": "code_interpreter"},
        {"type": "file_search"},
        {"type": "function", "function": {
            "name": "get_stock_price",
            "parameters": {"type": "object", "properties": {...}}
        }}
    ],
    model="gpt-4o"
)

# Create thread and run
thread = client.beta.threads.create()
client.beta.threads.messages.create(thread_id=thread.id, role="user", content="Analyze AAPL")
run = client.beta.threads.runs.create(thread_id=thread.id, assistant_id=assistant.id)
```

### LangGraph (covered in previous module)

### CrewAI:
```python
from crewai import Agent, Task, Crew

researcher = Agent(
    role="Senior Financial Researcher",
    goal="Find accurate financial data",
    tools=[search_tool, sec_tool]
)

analyst = Agent(
    role="Quantitative Analyst",
    goal="Perform rigorous quantitative analysis",
    tools=[calculator, python_repl]
)

crew = Crew(agents=[researcher, analyst], tasks=[...])
result = crew.kickoff()
```

### Comparison:
```
OpenAI Assistants: Simplest, vendor lock-in, managed state
LangGraph: Most flexible, complex setup, full control
CrewAI: Best for multi-agent, high-level abstraction
Autogen: Research-focused, conversation-based agents
```

## 4. Agent Memory Architecture

```
┌─────────────────────────────────────────┐
│            Agent Memory                   │
├─────────────────────────────────────────┤
│                                          │
│  Working Memory (context window)         │
│  ├── Current task + instructions         │
│  ├── Recent conversation turns           │
│  └── Tool results from this session      │
│                                          │
│  Short-term Memory (session)             │
│  ├── Conversation history                │
│  ├── Decisions made                      │
│  └── Intermediate results                │
│                                          │
│  Long-term Memory (persistent)           │
│  ├── User preferences                   │
│  ├── Past analyses (vector store)        │
│  ├── Learned patterns                    │
│  └── Entity knowledge graph              │
│                                          │
│  Procedural Memory (skills)              │
│  ├── Tool descriptions                   │
│  ├── Workflow templates                  │
│  └── Domain-specific procedures          │
│                                          │
└─────────────────────────────────────────┘
```

## 5. Planning Strategies

### Task Decomposition:
```python
decompose_prompt = """
Break down this task into subtasks that can each be completed independently:
Task: {task}

Output format:
1. [subtask] - tools needed: [tools]
2. [subtask] - tools needed: [tools]
...
Dependencies: [which tasks depend on which]
"""
```

### Adaptive Planning:
```python
def adaptive_agent(task):
    plan = create_plan(task)
    
    for step in plan:
        result = execute_step(step)
        
        if result.success:
            continue
        elif result.partial:
            # Modify remaining plan based on partial result
            plan = replan(plan, result)
        else:
            # Step failed entirely - try alternative approach
            alternative = find_alternative(step)
            result = execute_step(alternative)
    
    return synthesize_results(results)
```

## 6. Agent Grounding and Safety

### Grounding (Preventing Hallucination):
```python
# Rule 1: Always cite sources
# Rule 2: Distinguish "retrieved fact" from "inference"
# Rule 3: Confidence levels on all claims

system_prompt = """
Rules:
1. Only state facts that come from tool results
2. Clearly mark any inference with [INFERENCE]
3. If you don't have data, say "I don't have data on this"
4. Never make up numbers or statistics
"""
```

### Safety Guardrails:
```python
class SafeAgent:
    def __init__(self, agent, guardrails):
        self.agent = agent
        self.guardrails = guardrails
    
    def invoke(self, input):
        # Pre-check: Is the request safe?
        if not self.guardrails.check_input(input):
            return "I cannot help with that request."
        
        # Run agent
        result = self.agent.invoke(input)
        
        # Post-check: Is the output safe?
        if not self.guardrails.check_output(result):
            return "I generated a response but it was flagged. Let me try again."
        
        return result
```

### Budget Controls:
```python
class BudgetedAgent:
    def __init__(self, agent, max_tokens=50000, max_iterations=10, max_cost=0.50):
        self.max_tokens = max_tokens
        self.max_iterations = max_iterations
        self.max_cost = max_cost
        self.used = {"tokens": 0, "iterations": 0, "cost": 0.0}
    
    def step(self, state):
        if self.used["iterations"] >= self.max_iterations:
            return force_final_answer(state)
        if self.used["cost"] >= self.max_cost:
            return force_final_answer(state)
        
        result = self.agent.step(state)
        self.used["iterations"] += 1
        self.used["tokens"] += count_tokens(result)
        self.used["cost"] += estimate_cost(result)
        return result
```

## 7. Real-World Agent Examples

### Research Agent (Financial):
```
Task: "Analyze if NVIDIA is overvalued"
→ Search recent earnings (tool)
→ Get P/E, P/S ratios (tool)
→ Compare to semiconductor sector averages (tool)
→ Search for analyst price targets (tool)
→ Search for risk factors (tool)
→ Synthesize into buy/hold/sell recommendation (LLM reasoning)
```

### Code Agent:
```
Task: "Fix the failing test in auth_service.py"
→ Read the test file (tool)
→ Read the error message (tool)
→ Read the source code (tool)
→ Identify the bug (reasoning)
→ Write a fix (code generation)
→ Run tests (tool)
→ If still failing, iterate
```

### Data Analysis Agent:
```
Task: "Find anomalies in this quarter's trading data"
→ Load dataset (code interpreter)
→ Compute statistics (code)
→ Apply anomaly detection (code)
→ Visualize results (code)
→ Summarize findings (LLM)
```

## 8. Interview Questions

1. "Design an agent that can analyze a portfolio and suggest rebalancing"
2. "How would you prevent an agent from making harmful decisions?"
3. "How do you debug an agent that gives wrong answers?"
4. "When should you use an agent vs a chain vs a simple API call?"
5. "How do you handle agent failures in production?"
6. "Explain the trade-offs between ReAct and Plan-and-Execute"

### Decision Framework:
```
Does the task need dynamic decisions?
  No → Use a chain (fixed pipeline)
  Yes →
    Is it a single-turn reasoning task?
      Yes → ReAct agent
      No →
        Is it multi-step with dependencies?
          Yes → Plan-and-Execute / LangGraph
          No →
            Multiple specialists needed?
              Yes → Multi-agent (supervisor pattern)
              No → Simple ReAct with more tools
```
