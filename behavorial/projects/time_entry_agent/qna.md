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
- **"Same org" = logical boundary, not physical.** "Org" is a config row / tenant ID in the auth token — not a deployment unit. MCS, Power Automate, and Dataverse are independently scaled microservices running on separate clusters. MCS cluster serves ALL orgs, Dataverse cluster serves ALL orgs — they don't share processes or memory.
- Analogy: Gmail and Google Drive are in the same Google account but they're separate services that share your identity — same concept here.

**Q: If orgs are in different regions (e.g., NAM vs Asia), do HTTP calls go cross-region?**
A:
- **No.** Each service (MCS, Dataverse, Power Automate) has **regional deployments**. All HTTP calls stay intra-region.
- Org in NAM → PAF (NAM) → MCS (NAM) → Dataverse (NAM). Org in Asia → all calls within Asia.
- **What IS global**: Tenant identity (Entra ID). Auth token issuance may hit a global endpoint, but data plane calls are regional.
- Cross-region HTTP would add 100-300ms per call — unacceptable with multiple tool calls per user. Architecture ensures data sovereignty + low latency by keeping data plane regional.

**Q: How does PAF (Asia) know MCS (Asia)'s HTTP address? Is there a service registry?**
A:
- **No runtime service registry** (not Consul/Eureka). Endpoint resolution is **deterministic from the region**.
- Three mechanisms:
  1. **Well-known URL patterns**: Services have deterministic regional URLs (e.g., `crm5.dynamics.com` = Asia, `crm.dynamics.com` = NAM). If you know the region, you know the URL.
  2. **Environment metadata**: Each environment stores its region. Any service reading the environment context knows which regional endpoint to call.
  3. **Connectors**: PAF doesn't make raw HTTP calls — it uses connectors (MCS connector, Dataverse connector) that encapsulate endpoint resolution logic internally.
- Flow: PAF starts flow → reads environment context (knows it's Asia) → MCS connector resolves Asia → `https://asia.api.copilot.microsoft.com` → HTTP call → MCS reads tenant/env from auth token, scopes accordingly.
- Key point: endpoints are deterministic from the region, so no runtime discovery is needed.

**Q: give key time breakdowns**

action1 :  6sec median
action 2 : 4sec median
total : 8 sec median  (as most runs are without action2)
action1 breakdown : Ra(2sec) + RB(1sec) + TE(1sec) + intersec (2sec) + creat (1sec)
before optimizing : 10k users = 7days 50k users = 35 days
after optimizing : 1days and 5days