# Time Entry Agent — Q&A

## Technical Questions

**Q: How does RAG work in this context? What's the retrieval source?**
A: TODO

**Q: How did you handle hallucinations or incorrect entries?**
A: TODO

**Q: How did you scale from 1k to 50k users? What was the bottleneck?**
A: TODO (perf scaling — Phase 1)

**Q: What was the architecture? Microservices? Monolith?**
A: TODO

**Q: How do you handle multi-tenancy?**
A: TODO

**Q: What LLM model do you use? How do you manage model deployments?**
A: TODO

---

## Design Questions

**Q: Why agent vs copilot? Why build both?**
A: Copilot: interactive, user-driven. Agent: autonomous, scheduled. Different use cases — some users want control, some want zero-touch.

**Q: How do you ensure data privacy across tenants?**
A: TODO

---

## Impact Questions

**Q: What was the business impact?**
A: MAU growth, user engagement, time saved per user, showcased at Ignite + Pinnacle

**Q: How did you measure success?**
A: Business: MAU, revenue, no. of users. Eng: usage patterns, no. of TEs created with/without agent.

**Q: What would you do differently?**
A: TODO

----
## Fundamental Questions

**Q: How does MCS work? is it a service? is a new rag deployed per org?**
A:
- MCS is a **hosted multi-tenant SaaS** — separate service from Dataverse, communicates over HTTP
- You configure an "agent" (Knowledge + Instructions + Actions + GPT params) — MCS hosts and runs it
- At runtime: MCS builds a prompt (system prompt + RAG retrieval from Knowledge + tool definitions + history) → sends to Azure OpenAI → LLM responds with text or tool call → MCS executes tool → feeds result back → repeat (managed ReAct loop)
- **No, a new RAG is NOT deployed per org.** Shared MCS infra, but Knowledge/Instructions are tenant-isolated per environment
- Hierarchy: Tenant → Environment (≈ Dataverse org) → Agent config → Conversation (ephemeral, one per user invocation)
- Customer with 3 orgs = 3 separate agent configs + 3 flows + 3 environments. Deployed via solution packaging.

**Q: how does update multiple or xmultiple work?**
A: TODO

**Q: what is custom api exactly? why http call is required? isnt it in same org as flow/mcs?**
A:
- Custom API = server-side C#/.NET endpoint registered in Dataverse, callable via HTTP (e.g., `POST /api/data/v9.2/msdyn_CreateTimeEntries`)
- **MCS is a separate service from Dataverse** — different compute, different infra. Even though both are "Microsoft cloud," they communicate over HTTP. Not co-located.
- Same reason Power Automate → Dataverse is HTTP — they're all separate services in the Microsoft cloud backbone
