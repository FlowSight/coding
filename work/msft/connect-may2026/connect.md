# Connect Self-Assessment — May 2026

## 1. What results did you deliver, and how did you do it?

### a. Fundamentals

#### ICM / Incidents

**15+ incidents** handled actively for the Time team.
- **Severity breakdown:** 6× Sev 3, 3× Sev 4, 2× Sev 2
- **Customer tier:** 3 Strategic escalations, 2 Premier escalations
- **Area:** CE, F&O

**Specific highlights:**

- **#21000000790928 (Sev 3, Strategic):** Long-running. Authored novel production script to fix corrupted period IDs from manual customer data corruption — no prior mitigation pattern existed for this class of issue.

- **#21000000789706 (Sev 3, Strategic, 54+ days):** Proved a loop creating temp variables caused OOM. Cross-team with Shreedhar (AX Runtime – Memory/CPU) to validate and mitigate. Created tech debt to rewrite batch posting logic.

- **#1716530 (EU, 100+ days):** Evolving problem statement throughout lifetime. Authored new intercompany transaction clearing script. Multiple mitigation iterations as requirements shifted.

- **Siemens (Sev 2):** Partnered with Sutanu to deliver end-to-end fix over 3 weeks: stopped new corruption + batch-corrected existing records. Cross-team collaboration, brainstorming and learning with Vinay , Sudhanshu , Naushad . Adopted LongRunningJob framework. 5–8 test rounds with PM (Mohit). Saved 500+ TE records.

#### Bugs
**16+ bugs** fixed across CE (Project Operations) and F&O (Timesheet).
- **Area:** CE, F&O

**Specific highlights:**

- **#6225699 — Time off entry data corruption (Siemens).** 1500+ lines across 15 C# files + 30 solution artifacts. 3 redesigns to arrive at final architecture. Shipped across UR64 HF1, UR65, UR66 — 8+ PRs with multi-release cherry-picks. 7–8 rounds of testing with PM, saved 500+ corrupted Time off Entries.
- **30+ flaky tests fixed** — multiple PRs in msdyneng/FinOps across master + release branches. Required multiple iterations to stabilize. Created base test helper methods reused by PMRM team (Dunhill) and Budget team (Saurabh). Helped Nikita mitigate additional flaky tests.
- **#5950549 — Intercompany Timesheet Cost Account ignores posting profile.** Resolved 3 customer issues. Required collaboration with Expense team (Priyanka) and PM (Mukesh), plus redesign of ledger picking logic.
- **Accessibility:** 3 bugs fixed — ARIA button/link accessible names, "More Options" button missing name.

#### CSS Queries

Handled CSS queries promptly — timely responses with accurate RCA and mitigations.

#### Prior Connect Goals Addressed

- **Main deliverable without major issues** → Modern Time Entry Grid (Dec–Feb, on-time)
- **Significant AI usage** → Used AI (Copilot) as a core part of my workflow across Modern Grid + Change Order: refining feature specs, exploring design alternatives, generating PR code, and conducting code review. Contributed to 10+ PRs and 10k+ LOC with AI assistance.
- **Cross-functional impact** → Change Order Management (cross-team with Budget)
- **Mentorship/support** → Guided Nikita  (Modern Grid + flaky tests), Rupal (Bugs, ramp up).
- **New topic learnt** → Budgeting model ramp-up, LongRunningJob framework adoption, AI Skillup L200 course.

### b. Features

**Modern Time Entry Grid (#6067408)**

Led feature end-to-end to on-time completion. 3k+ lines across 10+ PRs. Guided Nikita on implementation — designed column visibility control pattern together. Iterative testing with PM (Mohit); shipped, reverted on feedback, re-shipped. Default grid switch for UR65. Feature flag for staged rollout. Leveraged AI throughout — spec refinement, design exploration, PR creation, code review. Delivered all of this within a compressed Dec–Feb timeline through the holiday season — fulfilling prior Connect goal: *deliver at least 1 main Time Management deliverable successfully without major issues.*

**Change Order Management (cross-team with Budget)**

Co-leading design and development with Anshul and Sunil since Mar 2026. Enables amendments to approved contracts — change orders update contract/contract line attributes and actuals on approval.Ramped up on budgeting model, refined the spec multiple iterations with Pooja, then contributed design decisions, corner-case analysis, alternative approaches. 7k+ lines across 12+ PRs: staging tables, change order item forms, price lists, chargeable roles, customer entities. Phase 1 design ~80% finalized, active development ongoing.

---

## 2. Reflect on recent setbacks — what did you learn and how did you grow?

**Siemens Sev 2 — Time Off corruption fix:**

- **Review miss:** Approved Nikita's RCA PR without unit tests under time pressure — the gap was caught later. I've since made it a practice to enforce test coverage on high-stakes changes regardless of urgency.
- **Redesign churn:** Went through 3 redesigns as stakeholders had conflicting opinions on approach. This taught me to drive design alignment upfront before committing to code by analyzing pros/cons before the call to help the team align instead of gathering opinions and deciding on spot.
- **Late-stage testing gaps:** Timezone bugs surfaced only in the final testing round by PM. I now explicitly test edge cases (TZ boundaries, DST) early in the cycle rather than relying on happy-path validation, by listing down corner cases from PM early on, which I'm practicing in Chnage Order feature.

---
*Draft in progress — last updated: 2026-05-26*