# Time Entry Agent — Airbnb Senior SWE Project Discussion Questions

## Opening (5 min)

**Q0: Tell me about the most impactful project you've worked on.**
- Need a 90-second elevator pitch: problem → your role → architecture → impact
- **GAP**: Must explain without Microsoft jargon (no MCS, Dataverse, Custom API, BAP RP) — Airbnb interviewer won't know these

### Answer

"The most impactful project I led at Microsoft was an AI agent that automatically fills timesheets for enterprise employees.

**The problem:** In Microsoft's enterprise CRM product, 1.2 million users fill timesheets every week. It's manual, repetitive, and error-prone — employees hate it. The business wanted to fully automate it.

**My role:** I led the design and delivery end-to-end, from zero to 200k users.

**How it works:** It's a scheduled autonomous agent — no human interaction needed. Every weekday, a cron-like scheduler triggers the agent for each user. The agent:
1. Fetches the user's project assignments and capacity bookings from our backend database
2. Checks what time entries already exist — avoids duplicates
3. Computes the delta — what's missing
4. Pulls context from the user's calendar and emails to enrich each entry
5. Uses an LLM to generate a human-readable comment for each entry
6. Bulk-creates the entries

step 5 uses generative AI. The entire orchestration uses GenAI-RAG. 

**Key challenges I solved:**
- **Scale:** Went from processing 1k users to 50k per org. Required parallelizing independent data fetches, throttling to stay under API rate limits, and async I/O to avoid connection pool exhaustion.
- **Cost:** Reduced per-user cost from $6.40 to under $1 by consolidating 8 separate API round-trips into 2 server-side actions, deduplicating redundant data fetches, and batching writes.
- **Context window:** LLM context was bloating as tool outputs accumulated. Solved by storing intermediate results in a metadata table and passing only lightweight references through the LLM — keeping the context lean.

**Impact:** Scaled to 200k users, showcased by our CEO at a company-wide conference, and became one of the flagship AI agents for the platform."

### Jargon Translation Guide
- "Dataverse" → "our backend database"
- "MCS" → "the AI orchestration layer" or "the agent's brain"
- "Custom API" → "server-side API endpoints"
- "Power Automate" → "a scheduled workflow / cron job"
- "BAP RP" → "an impersonation token service"