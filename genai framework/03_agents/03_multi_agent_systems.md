# Multi-Agent Systems

## 1. Why Multi-Agent?

Single agents hit limits:
- Context window too small for complex tasks
- One agent can't be expert at everything
- Complex tasks benefit from division of labor
- Specialization → better quality per sub-task

**When to use multi-agent:**
- Task requires diverse expertise (research + analysis + writing)
- Workflow has distinct phases (plan → execute → review)
- You want checks and balances (one agent verifies another)
- Scale: parallel execution of sub-tasks

## 2. Multi-Agent Architectures

### A. Supervisor / Orchestrator Pattern

```
┌─────────────────┐
│   Supervisor    │ ← Decides who works on what
│   (Manager)     │
└───────┬─────────┘
        │
   ┌────┼────┬────────┐
   ▼    ▼    ▼        ▼
┌─────┐┌─────┐┌─────┐┌─────┐
│Res. ││Anal.││Write││Code │
│Agent││Agent││Agent││Agent│
└─────┘└─────┘└─────┘└─────┘
```

```python
# Supervisor decides which agent handles each sub-task
def supervisor(state):
    decision = llm.with_structured_output(RouterDecision).invoke(
        f"Given this task, which agent should handle it?\n"
        f"Task: {state['current_task']}\n"
        f"Available: researcher, analyst, writer, coder\n"
        f"Completed so far: {state['completed_work']}"
    )
    return {"next_agent": decision.agent, "instructions": decision.instructions}
```

**Pros**: Central control, clear delegation, easy to debug
**Cons**: Supervisor is bottleneck, single point of failure

### B. Hierarchical Pattern

```
          ┌──────────┐
          │  Manager │
          └────┬─────┘
        ┌──────┼──────┐
        ▼      ▼      ▼
   ┌────────┐ ┌────────┐ ┌────────┐
   │Team    │ │Team    │ │Team    │
   │Lead A  │ │Lead B  │ │Lead C  │
   └──┬──┬──┘ └──┬──┬──┘ └────────┘
      ▼  ▼       ▼  ▼
    W1  W2     W3  W4
```

- Like org charts: executives → managers → workers
- Each level makes decisions at appropriate granularity
- Scales to complex workflows

### C. Peer-to-Peer / Collaboration

```
Agent A ←→ Agent B ←→ Agent C
  ↕            ↕            ↕
  └────────────┴────────────┘
      Shared message bus
```

```python
# Agents pass messages to each other
class CollaborativeAgent:
    def step(self, message):
        response = self.think(message)
        if response.needs_input_from:
            return Message(to=response.target_agent, content=response.question)
        elif response.done:
            return FinalAnswer(content=response.answer)
```

**Pros**: Flexible, no single point of failure
**Cons**: Hard to control, potential infinite loops

### D. Debate / Adversarial

```
┌────────┐    ┌────────┐    ┌────────┐
│  Bull  │───▶│  Bear  │───▶│ Judge  │──▶ Final Decision
│  Agent │◀───│  Agent │◀───│ Agent  │
└────────┘    └────────┘    └────────┘
```

- Two agents argue opposing positions
- Third agent evaluates and decides
- Best for: analysis where bias is a risk

### E. Assembly Line / Pipeline

```
Research → Analysis → Drafting → Review → Output
Agent       Agent      Agent     Agent
```

- Each agent handles one phase
- Output of one feeds input of next
- Simple, predictable, easy to test per stage

## 3. Communication Patterns

### Shared State:
```python
# All agents read/write to shared state dict
class SharedState(TypedDict):
    task: str
    research_findings: list[str]
    analysis_result: dict
    draft: str
    review_notes: list[str]
    final_output: str
```

### Message Passing:
```python
class Message:
    sender: str
    recipient: str  # or "broadcast"
    content: str
    message_type: str  # "request", "response", "update", "complete"
```

### Blackboard Pattern:
```python
# Central "blackboard" that agents read from and write to
blackboard = {
    "problem": "Analyze NVDA investment thesis",
    "constraints": ["risk tolerance: medium", "time horizon: 2 years"],
    "findings": [],      # Agents append here
    "questions": [],     # Agents can ask questions
    "conclusions": []    # Final outputs
}
# Any agent can read the blackboard and add to it
```

## 4. Implementation with LangGraph

```python
from langgraph.graph import StateGraph, END, START
from typing import TypedDict, Annotated
from langgraph.graph.message import add_messages

class MultiAgentState(TypedDict):
    messages: Annotated[list, add_messages]
    current_agent: str
    research: str
    analysis: str
    recommendation: str

def researcher_node(state):
    """Research agent: gathers data"""
    response = researcher_llm.invoke(
        f"Research task: {state['messages'][-1].content}\n"
        "Use tools to find relevant financial data and news."
    )
    return {"research": response.content}

def analyst_node(state):
    """Analyst agent: interprets data"""
    response = analyst_llm.invoke(
        f"Analyze this research:\n{state['research']}\n"
        "Provide quantitative analysis with key metrics."
    )
    return {"analysis": response.content}

def recommender_node(state):
    """Recommender: synthesizes into action"""
    response = recommender_llm.invoke(
        f"Research: {state['research']}\n"
        f"Analysis: {state['analysis']}\n"
        "Provide a clear buy/hold/sell recommendation with rationale."
    )
    return {"recommendation": response.content}

# Build graph
workflow = StateGraph(MultiAgentState)
workflow.add_node("researcher", researcher_node)
workflow.add_node("analyst", analyst_node)
workflow.add_node("recommender", recommender_node)

workflow.add_edge(START, "researcher")
workflow.add_edge("researcher", "analyst")
workflow.add_edge("analyst", "recommender")
workflow.add_edge("recommender", END)

app = workflow.compile()
```

## 5. Agent Specialization

### Giving Agents Different Capabilities:

```python
# Each agent has different:
# 1. System prompt (persona/expertise)
# 2. Tools (capabilities)
# 3. Model (GPT-4 for reasoning, GPT-4o-mini for simple tasks)

researcher = create_agent(
    system="You are a senior financial researcher with 20 years experience.",
    tools=[search_sec, search_news, get_analyst_reports],
    model="gpt-4o"
)

quant_analyst = create_agent(
    system="You are a quantitative analyst. Use math and statistics rigorously.",
    tools=[python_repl, calculate_risk, get_historical_data],
    model="gpt-4o"  # Best for math
)

writer = create_agent(
    system="You are a financial writer. Be concise, clear, and actionable.",
    tools=[],  # No tools, just writing
    model="gpt-4o-mini"  # Writing doesn't need biggest model
)
```

## 6. Coordination Challenges

### 1. Infinite Loops:
```python
# Agent A asks Agent B, Agent B asks Agent A, forever
# Fix: Max iterations, loop detection
def detect_loop(history):
    # If same agent called 3 times without progress
    recent = history[-6:]  # Last 3 exchanges
    if len(set(m.sender for m in recent)) == 2:
        return True  # Two agents going back and forth
    return False
```

### 2. Contradictory Results:
```python
# Two agents disagree
def resolve_contradiction(agent_a_result, agent_b_result):
    # Option 1: Use a judge agent
    judge_response = judge_llm.invoke(
        f"Agent A says: {agent_a_result}\n"
        f"Agent B says: {agent_b_result}\n"
        "Who is more likely correct and why?"
    )
    # Option 2: Ask for evidence/citations
    # Option 3: Present both to user
```

### 3. Context Passing:
```python
# Challenge: How much context to pass between agents?
# Too much → context overflow
# Too little → lost information

def summarize_for_next_agent(full_output, target_agent):
    """Compress output to only what next agent needs"""
    return llm.invoke(
        f"Summarize for the {target_agent}: {full_output}\n"
        f"Only include information relevant to their role."
    )
```

### 4. Failure Handling:
```python
def resilient_multi_agent(task):
    for agent in pipeline:
        result = agent.invoke(task)
        if result.failed:
            # Option 1: Retry same agent with modified input
            result = agent.invoke(modify_input(task, result.error))
            if result.failed:
                # Option 2: Skip to next agent with partial results
                task["skipped"].append(agent.name)
                continue
        task["results"][agent.name] = result
```

## 7. Scaling Multi-Agent Systems

### Parallel Execution:
```python
import asyncio

async def parallel_research(topics):
    """Run multiple research agents in parallel"""
    tasks = [
        researcher.ainvoke({"topic": topic}) 
        for topic in topics
    ]
    results = await asyncio.gather(*tasks)
    return results
```

### Dynamic Agent Spawning:
```python
def dynamic_crew(task_complexity):
    """Spawn agents based on task needs"""
    agents = [supervisor]  # Always have supervisor
    
    if task_complexity.needs_data:
        agents.append(create_researcher())
    if task_complexity.needs_math:
        agents.append(create_quant_analyst())
    if task_complexity.needs_code:
        agents.append(create_coder())
    
    # Only use agents you need (saves cost)
    return Crew(agents=agents)
```

## 8. Real-World Examples

### Investment Research Pipeline:
```
1. Macro Analyst → Market context, sector trends
2. Fundamental Analyst → Financials, valuation metrics
3. Technical Analyst → Price patterns, momentum
4. Risk Analyst → Downside scenarios, correlation
5. Portfolio Manager → Synthesize, size position, recommend
```

### Customer Support:
```
1. Classifier Agent → Route to department
2. FAQ Agent → Try simple answers
3. Research Agent → Search knowledge base
4. Escalation Agent → Prepare for human handoff
```

### Code Review:
```
1. Style Agent → Check formatting, naming
2. Logic Agent → Analyze correctness
3. Security Agent → Find vulnerabilities
4. Performance Agent → Identify bottlenecks
5. Summarizer → Combine all reviews
```

## 9. Frameworks Comparison

| Framework | Architecture | Best For |
|-----------|-------------|----------|
| LangGraph | Graph-based, explicit state | Production, complex workflows |
| CrewAI | Role-based, sequential/hierarchical | Rapid prototyping, clear roles |
| AutoGen (Microsoft) | Conversation-based | Research, flexible interaction |
| Swarm (OpenAI) | Lightweight, handoff-based | Simple multi-agent routing |
| MetaGPT | Software company simulation | Code generation workflows |

## 10. Interview Talking Points

- "Multi-agent is about separation of concerns — not just splitting work, but specialized reasoning"
- "The supervisor pattern gives predictability; peer-to-peer gives flexibility"
- "Key challenge: managing context between agents without overflow"
- "For D.E. Shaw: research → quant analysis → risk assessment → recommendation pipeline"
- "Always consider: could a single well-prompted agent do this? Multi-agent adds complexity"
- "Debate pattern is powerful for investment decisions — forces consideration of both sides"
