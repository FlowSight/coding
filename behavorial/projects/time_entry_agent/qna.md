# Time Entry Agent — Q&A

## Technical Questions

**Q: How does the agent decide what time entries to create?**
A: TODO

**Q: What tools does the agent use?**
A: TODO

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

**Q: How do you handle failures / retries?**
A: TODO

---

## Impact Questions

**Q: What was the business impact?**
A: MAU growth, user engagement, time saved per user, showcased at Ignite + Pinnacle

**Q: How did you measure success?**
A: Business: MAU, revenue, no. of users. Eng: usage patterns, no. of TEs created with/without agent.

**Q: What would you do differently?**
A: TODO
