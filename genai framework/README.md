# GenAI Frameworks - Crash Course (Basic → Advanced)

## Target: D.E. Shaw Principal Engineer - GenAI Round

## Learning Path (Recommended Order)

### Module 0: Foundations
1. [LLM Basics](00_foundations/01_llm_basics.md) - How LLMs work, transformer architecture, inference
2. [Tokens & Embeddings](00_foundations/02_tokens_embeddings.md) - Tokenization, embedding spaces, similarity
3. [Prompt Engineering](00_foundations/03_prompt_engineering.md) - Techniques from basic to advanced

### Module 1: RAG (Retrieval Augmented Generation)
1. [RAG Fundamentals](01_rag/01_rag_fundamentals.md) - Core pipeline, why RAG, architecture
2. [Vector Databases](01_rag/02_vector_databases.md) - Pinecone, Weaviate, pgvector, FAISS
3. [Chunking Strategies](01_rag/03_chunking_strategies.md) - Document processing, splitting approaches
4. [Advanced RAG](01_rag/04_advanced_rag.md) - Hybrid search, reranking, query transformation

### Module 2: LangChain & LangGraph
1. [LangChain Basics](02_langchain/01_langchain_basics.md) - Components, LCEL, prompts
2. [Chains & Memory](02_langchain/02_chains_and_memory.md) - Composition patterns, state management
3. [Agents & Tools](02_langchain/03_agents_and_tools.md) - Agent types, tool binding
4. [LangGraph](02_langchain/04_langgraph.md) - Stateful multi-actor workflows

### Module 3: Agents Deep Dive
1. [Agent Fundamentals](03_agents/01_agent_fundamentals.md) - ReAct, planning, reasoning loops
2. [Tool Use Patterns](03_agents/02_tool_use_patterns.md) - Function calling, MCP, tool design
3. [Multi-Agent Systems](03_agents/03_multi_agent_systems.md) - Orchestration, communication, patterns
4. [Agent Evaluation](03_agents/04_agent_evaluation.md) - Testing, benchmarking, safety

### Module 4: System Design for GenAI
1. [Architecture Patterns](04_system_design/01_genai_architecture_patterns.md) - Production designs
2. [Production Considerations](04_system_design/02_production_considerations.md) - Latency, cost, safety
3. [Evaluation & Observability](04_system_design/03_evaluation_observability.md) - Metrics, monitoring
4. [Interview Scenarios](04_system_design/04_interview_scenarios.md) - D.E. Shaw style problems

### Cheat Sheet
- [Interview Quick Reference](cheatsheet.md) - Key concepts, patterns, and talking points

---

## Study Plan (1-2 weeks)
| Day | Focus | Time |
|-----|-------|------|
| 1 | Module 0 (all 3 files) | 2-3 hrs |
| 2 | Module 1 (RAG fundamentals + vector DBs) | 2-3 hrs |
| 3 | Module 1 (chunking + advanced RAG) | 2 hrs |
| 4 | Module 2 (LangChain basics + chains) | 2-3 hrs |
| 5 | Module 2 (agents + LangGraph) | 2-3 hrs |
| 6 | Module 3 (agent deep dive, all) | 3 hrs |
| 7 | Module 4 (system design, all) | 3 hrs |
| 8 | Cheat sheet review + mock problems | 2 hrs |

## Key Insight for D.E. Shaw
They care about:
- **Depth of understanding** (not just API usage, but WHY)
- **System design at scale** (latency, cost, reliability)
- **Trade-offs** (when NOT to use GenAI)
- **Data privacy & security** (financial data sensitivity)
- **Evaluation rigor** (how do you know it works?)
