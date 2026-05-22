# Airbnb — Project Discussion (Cross-Functional Collaboration)
**Date**: May 13, 2025  
**Role**: Senior Software Engineer  
**Duration**: ~55 min  
**Format**: Presentation (~30 min) + Deep dive questions (~25 min)  
**Status**: Waiting  
**Vibe**: Positive  

---

## Part 1: Presentation (~30 min)

- Deliberate pacing: explained at a high level, didn't go too deep
- Interviewer set expectations upfront: "Don't go too deep, there will be other aspects I'd like to ask you after"
- Explained the ERP domain context:
  - What Dynamics 365 Project Operations is (licensed solution, paid, installed on tenant)
  - Interviewer asked: "Is this available in D365 cloud?" → Answered: No, it's a paid license, your tenant has the solution installed
  - Domain entities: Project → Contract → Contract Line → Task → Time Entry
- Explained the agent: components, steps, architecture (with diagrams from PPT)

---

## Part 2: Deep Dive Questions (~25 min)

### Q1: "Is there any time you improved or scaled something in the product?"
**My answer:**
- Yes — did a POC that changed the roadmap and concluded the future of the product
- Reduced per-user agent run latency from **55 seconds → 12 seconds**
- Also solved the cost problem: **$6.40 → $0.80 per run**
- (This was the action consolidation — merging 8 tools into 2 Custom API actions)

### Q2: "What did you spend the most time on during this entire project?"
**My answer:** POC creation, design documents, architecture, and concluding benchmarks.

**Probe: "What benchmarks? Why did it take so much time?"**
- Multiple configurations to test the agent against:
  - Simulate 500–1000 users in a tenant
  - Different org structures: 1 org with 500 users vs. multiple orgs with 500 users
  - Distribution of users across projects
  - How many Resource Bookings and Resource Assignments coincide
  - How many time entries per user
  - All these combinations took ~1–1.5 months at the end of every phase
- **Responsible AI testing** — manually fine-tuning prompts, which took significant time
- Later carried **A/B experiments** with different prompt variants — took more than a sprint or two at end of each of the 3 phases
- **Ranking of time spent:** (1) Benchmarking, (2) Experimentation/RAI, (3) Core development

### Q3: "Were there any conflicts you had with someone along the way?"
**My answer:** Used the architect PR revert story (from [maxim_conflict_v2.md](../../../behavorial/stories/maxim_conflict_v2.md)):
- Phase 3, week before eng-complete deadline
- Architect M (who had previously signed off the design) reverted my PR introducing a framework for tracking human-edited vs AI-edited fields
- His concern: "should not use stringified JSON in table column" — suggested separate table or full-text index instead
- Escalated to M2 to delay feature release
- **My approach:** Didn't argue — ran experiments:
  - Option 1 (separate table): 100-200ms WORSE latency per lookup
  - Option 2 (full-text index): 100ms FASTER than non-clustered index
- Called larger forum (M1, M2, stakeholders, architect M), presented data, let forum decide
- Forum agreed with my recommendation: keep current approach + add full-text index
- Un-reverted the commit, got 1-week extension, shipped on time
- **Key message:** "Data over debates" — didn't pull rank, didn't escalate emotionally, ran the experiment and let numbers settle it

### Q4: "If there's something you want to change about the project, what would it be?"
**My answer:**
1. Would NOT start with 8 separate tools — would merge them into consolidated actions from the start (as we eventually did)
2. Would get rid of MCP from the get-go — or at least not involve it in a POC while it was still immature
3. Would clarify limitations early from the MCS (orchestration) team — context window limits, memory constraints, etc. — instead of discovering them in production

### Q5: "If you had to redesign the agent with current/latest AI models or tools, how would you do it?"
**My answer:**
- The core use case is automating time entry creation — it's deterministic, well-scoped, doesn't need a stronger model
- Comment generation is optional, low churn, low usage — not why customers use the agent
- With **700K MAU already**, re-architecting with a stronger model (e.g., Claude) wouldn't give meaningful upside for the core workflow
- **I would keep it as-is** for time entry creation
- Would potentially use a stronger model for: comment generation enhancement, or the MCS RAG capability — but that's abstracted away from us anyway
- Bottom line: don't over-engineer a working system that's already at scale for a marginal gain

---

## Assessment

**Positive signals:**
- Presentation was polished (PPT + diagrams = prepared, senior-level communication)
- 30 min uninterrupted presentation = interviewer was engaged, not cutting you off
- Questions were forward-looking and reflective — they're evaluating senior maturity
- Positive vibe throughout

**What the questions map to (Airbnb values):**
| Question | Value Being Assessed |
|----------|---------------------|
| Data-driven decisions | Champion the Mission (metrics-driven impact) |
| Conflicts along the way | Be a Host (collaboration, handling disagreement) |
| What would you change | Self-awareness, growth mindset |
| Redesign with latest tools | Technical vision, staying current |

---

## Pipeline Status

| Round | Result |
|-------|--------|
| Coding 1 (Technical Screen) | Hire |
| Coding 2 | NoHire |
| System Design | Solid Hire |
| Project Discussion | Waiting (positive vibe) |
| Core Values? | Unknown if separate round exists |
