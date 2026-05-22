# Time Entry Agent — Project Discussion Slide Deck

---

## Slide 1: Title
- "AI Agent for Autonomous Timesheet Creation"
- Your name, role, team size, timeline
- One-liner: "Scaled from 0 to 200k users, reduced cost 85%, zero human interaction"

---

## Slide 2: Problem Statement
- 1.2M users fill timesheets weekly — manual, repetitive, error-prone
- Business ask: fully automate, no human interaction needed
- Naive math: 50k users × 55sec = 35 days processing → unrealistic
- Why it matters: top 3 highest-usage module in the product

---

## Slide 3: My Role & Scope
- Led design + delivery, e2e ownership
- Team: [X engineers], timeline: [X months]
- Phases: 0 (MVP) → 1 (Scale to 50k) → 2 (MCP platform abstraction)
- Personally designed: action consolidation, metadata table, concurrency model, MCP migration

---

## Slide 4: Architecture — High Level (jargon-free)

```
Scheduled Cron Job (per org)
    ↓ (for each user, throttled to 10 concurrent)
Impersonation Token (acts AS the user)
    ↓
AI Orchestrator
    ↓ (2 tool calls)
┌──────────────────────────────────┐
│  Action 1: Create Time Entries   │
│  - Fetch assignments (parallel)  │
│  - Fetch bookings (parallel)     │
│  - Fetch existing entries (parallel) │
│  - Compute delta                 │
│  - Bulk create                   │
├──────────────────────────────────┤
│  Action 2: Enrich Comments       │
│  - Fetch calendar/email          │
│  - Generate comments (LLM)       │
│  - Update entries                │
└──────────────────────────────────┘
    ↓
Database (per-user RBAC, OCC)
```

- Callout: "Only comment generation uses LLM — rest is deterministic"

---

## Slide 5: Key Design Decision — RAG with Deterministic Tools
- Why NOT pure LLM for everything?
  - Deterministic steps don't need intelligence — just data fetch + math
  - Cost: LLM per-call billing adds up at 200k users
  - Reliability: same input → same output (no hallucination on data ops)
- If rebuilding from scratch: would replace the AI orchestrator with a rule-based tool caller or custom lightweight framework — LLM only for comment gen

---

## Slide 6: Per-User Isolation & Security
- Agent runs as super-user, obtains on-behalf-of token for each user
- All reads/writes execute with user's RBAC permissions
- Audit trail shows the user as actor, not the service
- Tradeoff: per-user iteration is slower than batch, but non-negotiable for security + row-level access

---

## Slide 7: Scaling — What Broke (in sequence)

| Problem | Discovery | Root Cause | Fix |
|---------|-----------|------------|-----|
| 35-day processing time | Customer onboarding math | 5 HTTP calls, no parallelism, new DB connection per call | Merge 5 tools → 1 action: 55s → 12s latency, cost $4 → $0.80 |
| Context window crash | Load test with 30 entries/user | 30 intermediate TEs = 30KB in LLM memory | Metadata table — pass GUIDs (700 bytes) not payloads |

- POC for action consolidation: 1.5 sprints
- Implementation: 3-4 months (architecture change)

---

## Slide 8: Cost Optimization — $6.40 → ~$1

| Step | Change | Cost Impact |
|------|--------|-------------|
| Baseline | 8 orchestrator round-trips × $0.80 | $6.40/user |
| Consolidation (8→2 tools) | Reduce billable round-trips | $1.60/user |
| Deduplication | Cache repeated metadata fetches | ~$1.20/user |
| Batching | Bulk create instead of 1-by-1 | ~$1/user |

- Gained: transactional guarantees (sync custom API runs within a DB transaction)
- Lost: granular per-step observability (mitigated with structured logging + correlation IDs)

---

## Slide 9: Context Window Solution — Metadata Table

```
Before: Tool A → 30KB JSON → LLM context → Tool B → more JSON → CRASH

After:  Tool A → save to DB → return GUID (32 bytes) → LLM context lean
        Tool B → read from DB by GUID → process → save → return GUID
```

- Why not a message queue? Access pattern is random-read by key, not FIFO consume. Data persists for debugging. It's a lookup table, not pub/sub.
- Why not Redis? Outside platform boundary, extra infra, extra failure mode. DB already caches frequent IDs in service memory.

---

## Slide 10: Concurrency Design

```
SemaphoreSlim(10) — 10 users concurrently
    ↓ per user:
    Task.WhenAll(RA, RB, ExistingTE) — parallel fetches
    ↓
    ComputeDelta → CreateEntries (sequential)
```

- Per user: ~10 API calls (7 without comments, 12 with)
- Math: C=10 × 5 req/sec = 50 req/sec (rate limit = 100 → 50% headroom)
- Validated empirically: C=15 → occasional 429s, C=20 → consistent 429s
- Added progressive sleep: later users sleep longer (function of index i) to smooth burst
- Configurable per customer (different API tier = different limit)

---

## Slide 11: Consistency Model
- Agent runs during configured dark hours — project changes in CRM are rare AND coinciding with agent run is rarer
- Accept eventual consistency (READ COMMITTED, not SERIALIZABLE)
- Fetches complete in ~2 seconds, stale-read window is negligible
- Consequence of stale read: user sees an extra entry, deletes in 2 clicks — not a financial error
- Protection: delta logic prevents duplicates, OCC (ETags) prevents write conflicts
- OCC retry: 3 attempts, exponential backoff (200/400/800ms), skip+flag after exhaustion
- Production conflict rate: < 0.1%

---

## Slide 12: Production Metrics

| Metric | Value |
|--------|-------|
| Scale | 0 → 200k users |
| Latency | 55s → 12s per user |
| Cost | $6.40 → ~$1 per user |
| Entries accepted without edit | ~87% |
| Operational failure rate | 20% month 1 → 3% current |
| OCC conflict rate | < 0.1% |
| CEO showcase | Satya's Pinnacle Conference 2025 |

---

## Slide 13: Phase 2 — MCP Migration
- Before: Orchestrator → direct HTTP → backend APIs (hardcoded tool config)
- After: Orchestrator → MCP protocol → MCP servers → same backend APIs
- Real reason: business/leadership pressure + platform deprecation timeline
- Unexpected win: Service Tree ID scoping reduced hallucination (LLM only sees our tools, not global catalog)
- Cost: 3 engineer-weeks + 2 weeks co-dev with MCP server team
- Safety: parallel run with feature flag, fallback to direct APIs if MCP fails
- Regret: migrated 2 months early, spent time debugging their immature platform

---

## Slide 14: What I'd Change (Without Platform Constraints)

| Keep | Change |
|------|--------|
| RAG with deterministic tools | Replace AI orchestrator with rule-based tool caller or custom lightweight framework |
| Per-user isolation | Replace scheduled workflow with job queue (SQS/Kafka) — no 30s timeout |
| Metadata table for context mgmt | Get rid of MCP layer entirely |
| OCC over pessimistic locking | — |

- 60% platform-agnostic good engineering, 40% shaped by enterprise constraints

---

## Slide 15: What I'd Do Differently (Regrets)
- Pick 2-3:
  - Load-tested too late — each scale milestone broke something predictable
  - MCP migration too early — debugged their gaps unnecessarily
  - No user feedback loop for LLM comments — still no direct quality signal
- What I learned from each

---

## Slide 16: Q&A / Deep Dive
- Architecture diagram as background
- "Happy to go deeper on: concurrency model, cost math, security model, MCP trade-offs, or quality metrics"
