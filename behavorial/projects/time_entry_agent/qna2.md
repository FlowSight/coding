# Time Entry Agent — Hard Technical Questions (Q1-Q6)

---

## Q1: You scaled from 1k to 50k users. What broke first?

### Answer Framework (tell a STORY, not a list)

"When we first deployed to a real customer org with 10k users, three things broke in sequence:

**Break #1: scale exhaustion + cost explosion**
- **How I found it:** during onboarding a customer, got an idea of their scale, 10k users, 50k users -> 35days, unrealistic
- **Root cause:** 5 HTTP calls for  5 action call. Each call created a new database connection + pessimistic locking, no paralleism.
- **Fix:** POC to merge actions into 1 action. 1 db connection creation + 1 http call => resulted in 55sec e2e lat -> 12sec e2e lat
        5 tool calls : 0.8x5=4usd => 1 tool call : 80cent : 75% reduction
- **Time to fix:** POC 1.5 sprints - then implementation 3-4 months — architecture change

**Break #2: RAG context window full+crash**
- **How I found it:** Load test with 30 entries per user. Saw MCS crashing with context full error.
- **Root cause:** one intermediate TE = 1b, 30te = 30kb, cant fit in memory
- **Fix:** used intermediate table, passed GUID in conversation = 32byte x 30 = 700byte
- **Validation:** ran with 40 TE, no error.


### Follow-up traps to prepare for:
-

---

## Q2: You consolidated 8 tools into 2 actions. Walk me through how you decided what to merge. What did you lose?

### Answer

"The 8 tools mapped to the pipeline steps: get assignments, get bookings, get existing entries, compute delta, get calendar/email signals, generate comments, create entries, plus a metadata logging step.

**How I decided what to merge:**

I grouped by data dependency:
- **Action 1 (Create Time Entries):** Steps 1-4 + 7. Fetch assignments, bookings, existing entries → compute delta → bulk create. These are sequential anyway — each depends on the previous. No reason to round-trip back to the orchestrator between them.
- **Action 2 (Enrich Comments):** Steps 5-6. Fetch M365 signals → generate comments via LLM → update entries. This is independent of Action 1's internal steps.

**What we gained:**
- 8 HTTP round-trips → 2 round-trips (75% reduction)
- Cost: $6.40 → ~$1 per user (each round-trip was a billable orchestrator call)
- Latency: 8 sec → 3 sec (eliminated network overhead)
- DV guarantees any sync customapi is run within a transaction.

**What we lost:**


1. **Granular observability:** Before, we could see exactly which tool failed in the orchestrator logs. Now, we see 'Action 1 failed' and have to look at server-side logs for the specific step.
   - **Mitigation:** Added structured logging with step markers inside each action. Correlation ID traces through all sub-steps.

2. **Flexibility:** Adding a new step means modifying the server-side action code (C#), not just adding a tool in the orchestrator config.
   - **Mitigation:** Acceptable — we don't add steps frequently. Stability > flexibility at this maturity.

**Would I make the same choice again?** Yes. The cost and latency improvements at 50k users far outweigh the debugging convenience of 8 separate tools."

---

## Q3: The Agent Metadata table — isn't that just reinventing a message queue? Why not use one?

### Answer

"Good challenge. Here's why it's not a message queue, and why a message queue wouldn't work here:

**What Agent Metadata does:**
- Tool A executes → stores full JSON result → returns a GUID to the orchestrator
- Orchestrator passes GUID to Tool B → Tool B reads the full result by GUID → processes it
- Purpose: Keep LLM context window lean (GUIDs instead of large JSON payloads)

**Why it's NOT a message queue:**
1. **Access pattern is random read, not FIFO consume.** Tool B needs to read Tool A's specific output by key. A queue is consumed in order — you can't say 'give me message with ID X.'
2. **Data needs to persist across the run.** We use it for debugging after the fact. A queue message is consumed and gone.
3. **It's a lookup table, not a communication channel.** Tools don't subscribe — they do a point lookup by GUID.
4. cost of azure kafka is outside Dynamics 365 boundary and costlier than plain DB usage. Overengineering.

**Why not Redis/Memcached?**
- We're already inside the database platform. Adding an external cache means another service to manage, another network hop, another failure mode.
- The metadata table is just a Dataverse table — same auth, same RBAC, same connection. Zero infrastructure overhead.
- outside dynamics boundary. but DV usually caches freq ids in service memory.

**Why not Kafka/SQS?**
- Massive overkill. We're storing 7 intermediate results per user per run, each read exactly once. No pub/sub, no fan-out, no ordering guarantees needed.
- Adding a message broker for what is essentially a key-value lookup would add infrastructure complexity for no benefit.

**The honest answer:** It's a platform constraint turned into a feature. We were already in Dataverse, so using a Dataverse table was the lowest-friction option. But even without that constraint, a simple key-value table is the right tool for this access pattern — not a queue."

---

## Q4: You mentioned SemaphoreSlim(10). How did you arrive at 10? Show me the math.

### Answer

"It wasn't a guess — it was empirical tuning:

**The constraint:** Our backend API enforces a rate limit of 100 requests/sec per service connection.

**The math:**
- RA : fetch calender, fetch RA : 2 DB calls + 2 service call
- RB : fetch RB using calender above : 1 db  call
- existing TE : 1 db  call
- creat TE : 1db call
- fetch TE : 2 DB calls + 2 service call
- create capi comment : 1 service call
- total: without comment : 7 call , with comment : 12 calls
- Each user's processing involves ~10 API calls (within the 2 consolidated actions)
- Each call takes ~200ms average
- At concurrency = C, we fire C × (1/0.2) = C × 5 requests/sec
- To stay under 100 req/sec: C × 5 ≤ 100 → C ≤ 20

**So why 10, not 20?**
- 20 is the theoretical max. In practice, API response times vary (P99 can spike to 500ms+)
- At C=20, any latency spike pushes us over the rate limit → 429 errors → retries → cascading delays
- At C=10, we're at ~50 req/sec steady state — 50% headroom for spikes

**How we validated:**
1. Load test at C=5: No 429s, but throughput was unnecessarily low (25 req/sec)
2. Load test at C=10: No 429s, good throughput (50 req/sec), 50% headroom
3. Load test at C=15: Occasional 429s during spikes
4. Load test at C=20: Consistent 429s at P99 latency spikes

**C=10 was the sweet spot — maximum throughput without hitting rate limits under realistic conditions.**

We also made it configurable (not hardcoded) so we can tune per-customer if their API tier has different limits."
We also added a sleep for each user iteration start function of i, the more i, the more it slept.

---

## Q5: What happens when a user's data changes mid-run? You fetch assignments, then bookings, then compute delta — but assignments could change between fetches.

### Answer

NOTE: we usually run it in manually configured dark hours, and project changes in CRM is rare and more rare is that it will coincide with agent run.
"This is a great consistency question. Short answer: we accept eventual consistency, and here's why it's fine:

**The scenario you're describing:**
1. We fetch assignments at T=0 (User has Project A, 8h)
2. At T=0.5, project manager removes the user from Project A
3. We fetch bookings at T=1 (still shows Project A booking)
4. We compute delta and create a time entry for Project A — which is now invalid

**Why we accept this:**
1. **The window is tiny.** All fetches happen within ~2 seconds. The chance of a data change in that exact window is negligible in practice.
2. **The consequence is minor.** An extra time entry for a removed assignment is visible to the user. They can delete it in 2 clicks. It's not a financial transaction — it's a timesheet entry.
3. **The agent runs daily.** Tomorrow's run will see the corrected state and not recreate the deleted entry (the delta logic handles this).
4. **The alternative is worse.** Wrapping all fetches in a distributed transaction would require locking rows across multiple tables. This would block other users and the project manager from making changes. For a timesheet system, that's unacceptable.

**What we DO protect against:**
- **Duplicate entries:** The delta computation checks existing entries. Even if assignments change, we never create a duplicate.
- **Concurrent writes:** We use OCC (optimistic concurrency control) with ETags. If two processes try to write the same entry, one gets a conflict error and retries.

**In database terms:** We chose READ COMMITTED isolation, not SERIALIZABLE. The tradeoff is worth it."

---

## Q6: You use OCC (ETags). What happens on a conflict? Do you retry? How many times? What if the conflict is persistent?

### Answer

"Our OCC strategy:

**How it works:**
- Every entity in the database has a RowVersion (ETag)
- When we read an entry, we get its ETag
- When we write/update, we include the ETag in the request header
- If someone else modified the entry between our read and write, the ETag won't match → 412 Precondition Failed

**Our retry strategy:**
1. **On 412 conflict:** Re-read the entity (get fresh ETag + current state), re-evaluate if our change is still valid, then retry the write
2. **Max retries:** 3 attempts
3. **Backoff:** Exponential — 200ms, 400ms, 800ms
4. **After 3 failures:** Log the conflict, skip this entry, continue with the next user. The entry goes into a 'failed' state in our metadata table.

**Why exponential backoff:**
- If another process is also retrying, fixed intervals cause repeated collisions (thundering herd)
- Exponential backoff with jitter spreads out retries

**What if the conflict is persistent?**
- This means another process is continuously modifying the same entity. In practice, this doesn't happen — time entries are owned by one user, and only one agent run processes a user at a time.
- But if it did: after 3 retries, we skip and flag it. Next daily run picks it up (the conflicting process will have finished by then).

**Edge case we handle:** If the re-read shows the entry already has the value we wanted to write (someone else made the same change), we skip the write entirely — idempotent behavior.

**In production:** Conflict rate is < 0.1% of writes. Most conflicts resolve on first retry."
