# Phase 0-1: Foundations Interview Prep

**Project Phase:** Phase 0-1 (Architectural Foundation & Initial Scaling)  
**Scale:** 1k → 50k users  
**Key Metrics:** 7 days → 5 days processing (10k → 50k users)  
**Focus:** RAG architecture, tool design, per-user isolation, S2S impersonation  
**Interview Level:** Senior → Staff (foundational architecture mastery)

---

## Table of Contents

1. [Phase 0-1 Overview](#phase-0-1-overview)
2. [Architecture & Design Questions (12)](#architecture--design-questions-12)
3. [Scaling & Performance Questions (8)](#scaling--performance-questions-8)
4. [Security & Isolation Questions (6)](#security--isolation-questions-6)
5. [RAG & LLM Integration Questions (6)](#rag--llm-integration-questions-6)

---

## Phase 0-1 Overview

### What Makes Phase 0-1 Unique

**Phase 0-1 is the architectural foundation.** You built from scratch:

- **RAG with deterministic tools:** Not just LLM generation—fetch data, compute logic, then generate
- **Per-user iteration isolation:** One user's failure doesn't cascade
- **S2S impersonation:** Running as service principal but respecting per-user RBAC
- **Tool-based orchestration:** Each step (assignments, bookings, existing entries, delta, enrichment, comments, create) is a discrete Custom API

**Scaling journey:**
- Naive: Sequential per-user processing (50k users × 8 sec/user = 46+ days)
- Optimized Phase 0-1: Parallelization + SemaphoreSlim + org-level batching = 5 days

### Key Architectural Decisions Made in Phase 0-1

| Decision | What | Why | Trade-off |
|----------|------|-----|-----------|
| **RAG with tools** | Separate data fetch from LLM | Deterministic, cost-efficient | More complex orchestration |
| **Per-user iteration** | Process users independently | Isolation, RBAC respect | Sequential by default (slow) |
| **S2S impersonation** | Run as service principal, act as user | Security compliance, audit trails | Token management complexity |
| **Custom API tools** | HTTP endpoints for each step | Standardized, Dataverse-native | HTTP latency overhead |
| **Async/await pattern** | Non-blocking I/O, SemaphoreSlim | Scale to 50k concurrent | Thread pool tuning needed |

---

## Architecture & Design Questions (12)

### Q1: "Walk me through the entire flow from Power Automate to time entry creation. Don't simplify—include every HTTP call and why."

**Why interviewers ask this:**
- Tests if you understand the full stack (Flow → MCS → Custom API → Dataverse → M365)
- Shows if you know where latency hides
- Reveals architectural thinking (why each component exists)

**Depth indicators:**

❌ **Junior:**
"Flow calls MCS, MCS creates time entries."

❌ **Senior:**
"Flow iterates users, calls MCS, MCS fetches data and creates entries."

✅ **Staff:**
"Let me trace every step:

**Step 0: Trigger (Power Automate)**
```
Schedule: Every weekday at 8 AM
Trigger: Start execution
Action: Fetch all active users from Dataverse
Loop: FOR EACH user in list
```

**Step 1: User Iteration (Flow)**
```
FOR user in users:
  - Prepare context: userId, dateRange (Mon-Fri)
  - Create correlationId = UUID (tracing)
  - Call Custom API with impersonation token
```

**Step 2: Custom API (C#/.NET, runs as service principal)**
```
POST /api/data/v9.2/msdyn_CreateTimeEntries
Headers: X-User-Token: <S2S on-behalf-of token>, X-Correlation-ID: <ID>
Body: { userId, startDate, endDate, correlationId }

This endpoint:
1. Validates user (exists, not deactivated)
2. Calls MCS orchestrator (HTTP)
3. Collects results, logs to Agent Metadata table
4. Returns status (success/failure)
```

**Step 3: MCS Orchestrator (calls pipeline of tools)**

Each tool = HTTP call to Custom API:

```
Tool 1: Get Resource Assignments
  POST /api/data/v9.2/msdyn_GetAssignments
  Result: [Task1 (Project A, 8h), Task2 (Project B, 4h), ...]

Tool 2: Get Resource Bookings
  POST /api/data/v9.2/msdyn_GetBookings
  Result: [ProjectA (40h this week), ProjectB (0h), ...]

Tool 3: Get Existing Time Entries
  POST /api/data/v9.2/msdyn_GetTimeEntries
  Result: [ProjectA Monday 8h (already exists), ...]

Tool 4: Calculate Delta (Business logic)
  POST /api/data/v9.2/msdyn_CalculateDelta
  Inputs: assignments, bookings, existing
  Result: [ProjectA Tuesday 8h (missing), ProjectB Friday 4h (missing), ...]

Tool 5: Get M365 Signals
  GET https://graph.microsoft.com/v1.0/me/calendar/events
  Result: [Team standup Monday 1h, PM meeting Wednesday 0.5h, ...]

Tool 6: Generate Comments (LLM call)
  POST /api/data/v9.2/msdyn_GenerateComments
  Input: delta entries + M365 signals
  LLM call: 'Create human-readable descriptions'
  Result: Comments for each entry

Tool 7: Create Time Entries
  POST /api/data/v9.2/msdyn_CreateBatch
  Body: [{ projectId, hours, description, comment }, ...]
  Result: Created time entries or errors
```

**Step 4: Write to Agent Metadata**
```
Log entry created:
- userId, timestamp, correlation ID
- Entries created count
- Errors if any
- Duration (6-8 sec for this user)
```

**Complete latency breakdown (8 sec median):**
- Ra (2 sec): Custom API calls (HTTP + DB query)
- Rb (1 sec): Custom API calls (HTTP + DB query)
- TE (1 sec): Custom API calls (HTTP + DB query)
- Intersect (2 sec): Compute logic + M365 Graph call
- Comments (0.5 sec): LLM call (Azure Model, cached prompt)
- Create (1.5 sec): Batch insert to Dataverse

**Total: 8 sec per user**

**At 50k users:**
- Sequential: 50k × 8 sec = 400k sec = 111 hours = 4.6 days
- But we parallelize (SemaphoreSlim(10)): 10 concurrent
- Actual: 111 hours ÷ 10 threads = 11 hours per instance
- With 2 instances: 5.5 hours
- With scheduling (nights/weekends): Fits in 1-night window
- Actual Phase 0-1: 5 days (I think you meant this is total duration including retries/failures, not continuous time)"

**Follow-up to probe deeper:**
- "Why is Tool 4 (delta calculation) 2 seconds when it's just set operations?"
- "Where's the SemaphoreSlim throttling? Which component enforces it?"
- "What happens if Tool 5 (M365 Graph) times out? Does the whole entry fail?"

---

### Q2: "Design the per-user iteration. Why iterate per-user instead of processing all users in one batch?"

**Why interviewers ask:**
- Tests understanding of isolation, RBAC, and failure modes
- Shows if you think about user-level vs. org-level tradeoffs
- Reveals knowledge of when isolation is worth the cost

**Depth indicators:**

❌ **Junior:**
"Iterate so each user gets their own data."

❌ **Senior:**
"Iterate because RBAC needs to be respected per user."

✅ **Staff:**
"Great question. Iteration choice has huge implications.

**Option A: Batch process all users at once**
```
Input: All 50k users
Step 1: Fetch ALL assignments globally
Step 2: Fetch ALL bookings globally
Step 3: Calculate delta for ALL users (global compute)
Step 4: Create ALL time entries (single batch)
```

Pros:
- Amortize retrieval (fetch data once, use for all users)
- Larger batches (more efficient Dataverse APIs)
- Fewer HTTP round trips

Cons:
- RBAC violation: Global query sees data the querying user shouldn't see
- One user's failure blocks all (User A's error = entire batch fails)
- User B's timesheet depends on User A's success
- Uncontrolled blast radius
- Audit trail: Can't attribute action to specific user

**Option B: Per-user iteration (what we chose)**
```
FOR user in users:
  - Impersonate user (S2S token)
  - Fetch assignments (only user can see)
  - Fetch bookings (RBAC enforced)
  - Calculate delta (scoped to user's data)
  - Create time entries (as user)
  - Log result (user-specific)
```

Pros:
- RBAC respected: Each query scoped to user's permissions
- Isolation: User A's failure doesn't affect User B
- Audit trail: Action attributed to user
- Rollback granularity: If User A fails, only retry User A, not all 50k

Cons:
- Redundant work: If 100 users in Finance org, fetch same assignments 100 times
- More HTTP calls: 50k users × 7 tools = 350k HTTP calls (vs. ~10 in batch mode)
- More latency: 50k × 8 sec = 400k sec total (vs. maybe 1000 sec in batch)
- Infrastructure: 10 concurrent threads × 8 sec each = higher thread utilization

**Why we chose Option B:**
1. **Compliance requirement**: Dynamics 365 customers expect per-user audit trails. Time entry entry audit: 'User Alice created this.' Not 'System created this for Alice.'
2. **Failure isolation**: Financial workflows rely on timesheets. If Alice's sync fails, we retry just Alice. If batch fails, all 50k retry = cascading load.
3. **RBAC enforcement**: Project manager Alice sees Project A only. If we fetched globally, either we violate security (show her Project B) or we filter in memory (wrong layer).
4. **User experience**: Alice expects her timesheet created in her own context, not by system acting as someone else.

**The Cost:**
Redundant retrievals at scale:
- 50k users
- Average org size: 100 users
- 500 orgs
- Retrieving assignments 50,000 times = lots of work

**Optimization in Phase 2:**
We moved to org-level batching (MCP + metadata) to reduce redundancy. But Phase 0-1 kept it simple: per-user iteration, accept redundancy cost.

**When to break this rule:**
If requirements were pure efficiency (no audit, no RBAC), batch would be better. But enterprise software has these non-negotiables."

**Follow-up to probe deeper:**
- "How do you implement S2S on-behalf-of token? What's the token flow?"
- "What if a user has no assignments? Do they get 0 time entries or error?"
- "How do you handle users in multiple business units?"

---

### Q3: "Explain S2S impersonation (on-behalf-of flow). What problem does it solve? What could go wrong?"

**Why interviewers ask:**
- Tests understanding of distributed identity and RBAC
- Shows if you've thought through security implications
- Reveals knowledge of token management at scale

**Depth indicators:**

❌ **Junior:**
"Use a special token that lets the service act as a user."

❌ **Senior:**
"Get a token on-behalf-of the user, use it to call Dataverse APIs."

✅ **Staff:**
"S2S on-behalf-of is a classic OAuth flow in multi-service systems.

**The Problem:**
Agent runs as service principal (high privilege). If we use this identity directly:
- Query: SELECT * FROM TimeEntry WHERE UserId = X
- RBAC check: Service principal has * permission
- Result: Returns ALL time entries, violating user X's row-level security
- Security disaster

We need: Agent queries Dataverse AS user X, respecting X's permissions.

**The Solution: S2S On-Behalf-Of Flow**

OAuth 2.0 On-Behalf-Of:
```
1. Agent (service principal) has:
   - Its own identity (clientId, secret)
   - Credential to impersonate users

2. For each user:
   - Token Request to Azure AD:
     POST /token
     client_id: <agent app ID>
     client_secret: <agent secret>
     grant_type: client_credentials
     scope: https://service.dynamics.com/.default
     assertion: <user token (from BAP)>
     
   - Response: access_token (acting AS user)

3. Use token for Dataverse:
   POST /api/data/v9.2/msdyn_GetAssignments
   Headers: Authorization: Bearer <on-behalf-of token>
   Result: Only assignments user can see (RBAC enforced)
```

**Why it works:**
- Token includes user's identity + service principal's identity
- Dataverse: 'This is agent acting as Alice'
- RBAC check: Apply Alice's permissions
- Audit trail: 'Alice (via agent) queried assignments'

**What Could Go Wrong:**

1. **Token expiry mid-operation**
```
Start (token valid): Fetch assignments
Mid-operation (token expires): Fetch bookings fails
Result: Partial data, inconsistent state

Mitigation: Request fresh token per operation, or cache with short TTL
```

2. **User lacks permissions**
```
User Alice in Finance department
Query bookings for HR projects → 403 Forbidden
Result: Some tools succeed, others fail

Mitigation: Graceful fallback (skip HR projects, log warning)
```

3. **Token leak**
```
Log includes Bearer token by accident
Token captured in proxy logs
Attacker replays token (impersonates Alice)

Mitigation: Never log tokens. Use correlation IDs instead.
```

4. **Circular impersonation**
```
User A triggers agent on-behalf-of User B
User B triggers agent on-behalf-of User A
Infinite loop?

Reality: Token includes 'chain' of impersonations. After 2 hops, Azure AD rejects.

Mitigation: Understand limits (typically 1 hop allowed)
```

5. **Stale token cache**
```
Cache Alice's token for 1 hour
Alice's permissions change (removed from Finance)
Agent still has old token with old permissions

Mitigation: Cache with TTL < 30 min, or invalidate on known changes
```

**Phase 0-1 implementation:**
```csharp
// Simplified
public async Task<string> GetOnBehalfOfToken(string userId) {
    var authContext = new AuthenticationContext(authority);
    var userAssertion = await GetUserToken(userId);  // From BAP
    
    var credential = new ClientCredential(clientId, clientSecret);
    var result = await authContext.AcquireTokenAsync(
        resourceId: 'https://service.dynamics.com',
        clientAssertion: new ClientAssertionCertificate(clientId, cert),
        userAssertion: new UserAssertion(userAssertion.AccessToken)
    );
    
    return result.AccessToken;
}

// For each user
var token = GetOnBehalfOfToken(userId);
var result = await CallDataverseAPI(token, operation);
```

**Cost/Performance:**
- Token request: ~200ms per user
- 50k users × 200ms = 10,000 sec = 2.7 hours just for token calls!
- Optimization: Cache tokens, reuse within TTL (1 hour)
- With caching: ~1 token request per hour per user = negligible cost

**Why this design is worth it:**
- Compliance: Audit trail shows user's action
- Security: Row-level security enforced
- Scoping: User can't access data they shouldn't
- Industry standard: Office 365, Azure, all use this pattern"

**Follow-up to probe deeper:**
- "How do you handle token cache invalidation if user permissions change?"
- "What if token refresh fails? Retry or fail the user?"
- "How many token requests per second can Azure AD handle?"

---

### Q4: "You have 7 tools, each calling Dataverse with HTTP. Why not batch them into 1 mega-tool?"

**Why interviewers ask:**
- Tests understanding of API design and composition
- Shows if you think about failure modes and retry strategies
- Reveals knowledge of when composition > monoliths

**Depth indicators:**

❌ **Junior:**
"Each tool is separate so they're independent."

❌ **Senior:**
"Separate tools for modularity and reusability."

✅ **Staff:**
"Excellent question. There's a real tradeoff here.

**Option A: One Mega-Tool (all-in-one)**
```csharp
public TimeEntryBatch CreateTimeEntries(userId, dateRange) {
    var assignments = GetAssignments(userId, dateRange);
    var bookings = GetBookings(userId, dateRange);
    var existing = GetTimeEntries(userId, dateRange);
    
    var delta = CalculateDelta(assignments, bookings, existing);
    
    var m365signals = GetM365Signals(userId, dateRange);
    
    var comments = GenerateComments(delta, m365signals);
    
    var result = CreateBatch(delta.Select(e => 
        new TE { projectId, hours, comment }
    ).ToList());
    
    return result;
}
```

Pros:
- Single HTTP call (vs. 7)
- Atomic: All or nothing (no partial success)
- Simpler error handling (one failure point)
- Deterministic: No cross-tool inconsistency

Cons:
- **Timeout risk**: If any step slow, entire call times out
  - Example: M365 Graph slow (network issue)
  - Timeout: 30 sec (PAF limit)
  - Result: Entire operation fails, lose Assignments + Bookings + TE work
  
- **Retry cascades**: Retry entire operation (redundant work)
  - Assignment retrieval was fast, only M365 was slow
  - Retry refetches assignments (wasted work, cost)
  
- **No granular insight**: If fails, which step caused it?
  - Logs say 'CreateTimeEntries failed'
  - Debugging: Run each step manually to isolate
  
- **Rigid orchestration**: Each step must wait for previous
  - Ra (2s) → Rb (1s) → TE (1s) → Intersect (2s) → Comments (0.5s)
  - Can't parallelize Ra, Rb, TE (could save 1 sec)

**Option B: Separate Tools (what we chose)**
```
Tool 1: GetAssignments (1 tool per operation)
Tool 2: GetBookings
Tool 3: GetTimeEntries
Tool 4: CalculateDelta
Tool 5: GetM365Signals
Tool 6: GenerateComments
Tool 7: CreateBatch
```

Pros:
- **Retry granularity**: If tool 5 (M365) fails, retry only tool 5
  - Skip tools 1-4 (already succeeded)
  - Faster retry (only 1-2 sec, not 8 sec)
  
- **Parallelization**: Ra, Rb, TE can run concurrently (with SemaphoreSlim)
  - Sequential: 4 sec
  - Parallel: 2 sec (bottleneck is Ra)
  - Savings: 2 sec per user × 50k users = 100k sec = 28 hours
  
- **Debugging**: Each tool's latency visible
  - Logs show Ra=1.8s, Rb=1.1s, TE=1.0s, etc.
  - Slow tool easily identified
  
- **Reusability**: Each tool callable independently
  - Other agents can use 'GetAssignments' tool
  - Sharing infrastructure (MCP in Phase 2 leverages this)
  
- **Fault isolation**: M365 fails, agents aren't blocked
  - Fallback: Skip M365 signals, create entries anyway (no enrichment)
  - Result: 6 sec instead of failed

Cons:
- 7 HTTP calls (vs. 1)
- Intermediate state management (pass results between tools)
- Partial failure (Tool 1 succeeds, Tool 5 fails = inconsistent state)
- More complex orchestration logic

**The Tradeoff:**
- Latency: Option A = 8 sec, Option B = 6 sec (with parallelization)
- Reliability: Option A = all-or-nothing, Option B = graceful degradation
- Operability: Option A = harder to debug, Option B = visible failure points

**Why we chose Option B:**
1. **Enterprise SLA**: 'Best effort' > 'all or nothing'
   - Missing M365 signals != missing time entries
   - Better: 95% entries created than 0% because Graph was slow
   
2. **Parallelization**: 2 sec savings × 50k users = huge
   - Over Phase 0-1's 5 days, saves ~1.4 days
   
3. **Tool reusability**: Separate tools are discovered by MCP
   - Phase 2 leverages this (MCP server with individual tools)
   
4. **Cost**: Each HTTP call ≈ $0.10 (MCS overhead)
   - 7 calls × $0.10 = $0.70 per user
   - 50k × $0.70 = $35k (noticeable)
   - But parallelization saves $0.70 × 50k = $35k in infrastructure (bigger win)

**Could we have hybrid?**
```
Tool A: GetResourceData (internal: GetAssignments + GetBookings + GetTE)
Tool B: CalculateDelta
Tool C: GetM365Signals
Tool D: CreateBatch
```

Pros: Fewer calls, still parallelizable
Cons: Less reusable, less observable

We didn't do this in Phase 0-1 (wanted simplicity). Phase 2 does something similar with MCP."

**Follow-up to probe deeper:**
- "At what tool count does composition overhead exceed benefits?"
- "How do you handle tool interdependencies (Tool C needs Tool A's output)?"
- "What's the maximum number of concurrent tools you'd allow?"

---

### Q5: "Why is 'Get Existing Time Entries' a separate tool? Can't MCS just check for duplicates in memory?"

**Why interviewers ask:**
- Tests understanding of idempotency and duplicate prevention
- Shows if you think about data consistency and timing
- Reveals knowledge of when to query vs. compute

**Depth indicators:**

❌ **Junior:**
"Check in memory to avoid API calls."

❌ **Senior:**
"Query Dataverse to find existing entries, prevent duplicates."

✅ **Staff:**
"This is a critical design decision.

**Option A: Check in memory only**
```csharp
var assignments = GetAssignments();  // Projects
var existing = [];  // Empty (don't query)

foreach (var proj in assignments) {
    var te = new TimeEntry { projectId = proj, hours = 8, date = Monday };
    existing.Add(te);  // Just create
}
```

Cons:
- **Duplicate time entries**: If agent ran yesterday and created Monday entry
  - Today's run: Doesn't see yesterday's entry (not queried)
  - Creates Monday entry AGAIN
  - Result: 2 identical entries
  
- **User confusion**: Timesheet shows Monday 8h twice
  - User submits 16h instead of 8h
  - Billing is wrong
  - Financial data corrupted

- **Idempotency broken**: Same input (user, date) → Different output (duplicates)
  - Violates fundamental principle for distributed operations

**Option B: Query existing (what we do)**
```csharp
var assignments = GetAssignments();
var existing = GetTimeEntries(userId, startDate, endDate);  // Query from DB

foreach (var proj in assignments) {
    var alreadyExists = existing.FirstOrDefault(e => 
        e.projectId == proj && e.date == Monday
    );
    
    if (alreadyExists == null) {
        // Create new entry
    } else {
        // Skip (already created)
    }
}
```

Pros:
- **Idempotency**: Same input → Same output (no duplicates)
- **Safe retries**: If sync fails at 80%, retry doesn't re-create first 80%
- **Correctness**: Timesheet reflects reality (no duplicates)

Cons:
- Extra API call (1 sec latency)
- Extra cost ($0.10)
- Extra query load on Dataverse

**But is it really necessary?**

Consider: When would we create duplicates?

1. **User runs sync twice in same day?**
   - Unlikely (Flow runs once at 8 AM)
   - But possible if user manually triggers

2. **Sync fails and retries?**
   - Yes, exponential backoff kicks in
   - Could create entries twice

3. **Multiple agents for same user?**
   - Copilot + Agent both running
   - Could both create entries

**Mitigation without querying:**

Use **idempotency keys** (deterministic):
```csharp
var idempotencyKey = Hash(userId + projectId + date);
// Same input → Same key
// Dataverse: 'If key exists, return existing'
```

This way:
- No duplicate query (save 1 sec)
- Still idempotent (same key)
- Dataverse handles uniqueness

Example:
```
First run: Create entry with key 'user123-projA-2025-05-03'
Second run: Same key → Dataverse returns existing entry (no duplicate)
Result: Idempotent without querying
```

**Why we didn't use idempotency keys in Phase 0-1:**
1. Dataverse unique constraint implementation (added complexity)
2. Fallback to query was simpler initially
3. Benchmarking showed query wasn't bottleneck (TE = 1 sec, not 8 sec)

**Phase 2 evolution:**
We optimize by:
- Caching existing entries per org (query once, use for all users)
- Deterministic IDs (already using in newer version)

**When to skip the query:**
- If you have strong idempotency guarantee
- If duplicates are low-cost (not financial data)
- If performance is critical and query is bottleneck

**For time entries:**
- Financial implication (high cost of duplicates)
- Relatively rare (1 sec query not bottleneck vs. 8 sec total)
- So query is justified

**If processing 1M users and TE query becomes bottleneck:**
```
Option 1: Cache per org (query once per org, reuse)
Option 2: Batch query (single query returns all existing for user + date range)
Option 3: Switch to idempotency keys (deterministic IDs)
```

We'd likely choose Option 1 or 3 at massive scale."

**Follow-up to probe deeper:**
- "What if Dataverse is slow and TE query takes 5 seconds?"
- "How do you handle concurrent creates with same idempotency key?"
- "At what scale does caching per org become necessary?"

---

### Q6: "The 'Generate Comments' step uses an LLM. Why generative AI only here, not for other steps?"

**Why interviewers ask:**
- Tests understanding of LLM cost/benefit
- Shows if you think about what needs AI vs. determinism
- Reveals knowledge of LLM latency, cost, hallucination risks

**Depth indicators:**

❌ **Junior:**
"Use LLM for everything to be smart."

❌ **Senior:**
"Use LLM only where determinism isn't needed."

✅ **Staff:**
"This is a cost-benefit decision.

**Analysis: Where could we use LLM?**

**Step 1: Get Assignments**
```
Input: UserId, DateRange
Output: [ProjectA 8h, ProjectB 4h, ...]
Logic: Query Dataverse table → Filter by date range
Could be LLM? 'What assignments does user have?'
LLM result: 'The user has 2 projects: Project Alpha (8 hours) and Project Beta (4 hours).'

Problem:
- Deterministic query returns exact data
- LLM might hallucinate: 'ProjectC (2h)' (doesn't exist)
- Risk: Create time entries for non-existent projects
- NEVER worth it

Why use LLM when deterministic exists: No.
```

**Step 2: Get Bookings**
```
Similar to Step 1. Deterministic query exists. Never use LLM.
```

**Step 3: Calculate Delta**
```
Input: Assignments, Bookings, Existing
Logic: Set operations (intersection, difference)
Could be LLM? 'What time entries are missing?'
LLM result: 'Missing ProjectA Monday 8h, ProjectB Friday 4h'

Problem:
- Deterministic set math is faster + accurate
- LLM is slow (1-2 sec) + might miss entries or hallucinate
- Example: 'User should work 50h, but LLM says 38h'
- Risk: Missing time entries

Why use LLM when deterministic math exists: No.
```

**Step 4: Generate Comments**
```
Input: Delta entries + M365 signals (meetings, emails)
Output: Human-readable description per entry
Example output: 'ProjectA: Worked on feature design (aligned with team standup Monday 9am, discussed Q2 roadmap in email Friday)'

Logic: Synthesize multi-source data + create prose
Could be deterministic? 
```
Deterministic template:
```
'[ProjectName]: Worked on [assignment title] on [dates]'
Example: 'ProjectA: Worked on Feature Design on Monday'
```

Human-readable:
```
'ProjectA: Feature design session (aligned with team sync Monday 9am, roadmap discussion on Friday email)'
```

Clearly LLM wins (human-like, personalized).

Pros of LLM:
- Personalized: Mentions actual meetings/emails
- Human-like: Reads well
- Context-aware: Different comments per user, project, signals

Cons of LLM:
- Slower: 1-2 sec per call
- Costs: ~$0.01 per 100 calls, vs. $0.001 for template
- Hallucination risk: Might invent details
  - Example: 'Discussed salary negotiations' (didn't happen)
  
**Mitigation for hallucinations:**
- Use low temperature (0.3) for determinism
- Constrained prompts: 'Only mention actual meetings and emails'
- Validation: Check output matches input data
- Fallback: If weird, use template

**Why only Comments use LLM:**
1. **Value proposition**: LLM adds readability (not just data)
2. **Correctness**: Wrong comments ≠ wrong business logic (low risk)
3. **Cost trade-off**: 1 sec latency × 50k users = acceptable
4. **No better alternative**: Templates are poor quality

**If we used LLM for assignments:**
```
Cost: 1 sec × 50k = 50k sec = 14 hours extra per run
Value: Hallucinate and corrupt data
Verdict: Terrible trade-off
```

**Why not LLM for delta calculation:**
```
Cost: 1 sec × 50k = 14 hours extra
Value: Risk missing entries or hallucinating entries
Verdict: Worse than assignments
```

**Key principle:**
- **Use determinism for:** Data retrieval, business logic, correctness-critical paths
- **Use LLM for:** Enhancement, synthesis, human-facing output

**Future opportunity (not in Phase 0-1):**
LLM for **enrichment only** (optional data, not critical path):
```
- Effort classification: 'Is this meeting, coding, or planning?'
- Project categorization: 'Which business unit is this for?'
- Anomaly detection: 'This 50h week is unusual, ok?'
```

All optional (don't block if LLM fails). Phase 2 could add if value justified."

**Follow-up to probe deeper:**
- "What if comment generation LLM fails? How do you handle it?"
- "How do you validate LLM output to prevent hallucinations?"
- "At what point does comment generation latency become unacceptable?"

---

### Q7: "How do you handle tool failures? If 'Get Bookings' fails, do you continue or abort?"

**Why interviewers ask:**
- Tests understanding of failure modes and resilience
- Shows if you think about graceful degradation
- Reveals error handling philosophy (strict vs. lenient)

**Depth indicators:**

❌ **Junior:**
"Abort if any tool fails."

❌ **Senior:**
"Retry failed tool, abort after N retries."

✅ **Staff:**
"Failure mode depends on tool criticality.

**Categorize tools by impact:**

**Tier 1: Critical (abort if fails)**
- Get Assignments
- Get Bookings
- Get Existing Time Entries
- Calculate Delta
- Create Time Entries

If any fail: Cancel entire operation (partial state is worse than no state)

Reason: Missing assignments = create nothing, but booking success = incomplete (bad).

**Tier 2: Enrichment (degrade if fails)**
- Get M365 Signals
- Generate Comments

If fails: Continue without enrichment (lower quality, but not wrong)

Reason: Missing meeting context ≠ wrong time entry. Just less detailed.

**Implementation:**

Tier 1 tools: Strict error handling
```csharp
try {
    var assignments = await GetAssignments(userId, dateRange);
    if (assignments == null || assignments.Count == 0) {
        throw new InvalidOperationException('No assignments found');
    }
} catch {
    // Retry with exponential backoff (1s, 2s, 4s, 8s, 16s)
    for (int retry = 0; retry < 5; retry++) {
        try {
            return await GetAssignments(userId, dateRange);
        } catch when (retry < 4) {
            await Task.Delay(Math.Pow(2, retry) * 1000);
        }
    }
    // All retries failed
    throw new FatalException('GetAssignments failed after 5 retries');
}
```

Tier 2 tools: Graceful degradation
```csharp
try {
    var signals = await GetM365Signals(userId, dateRange);
    return signals;
} catch {
    // Log warning, continue without signals
    logger.Warn($'M365 signals unavailable for user {userId}');
    return new M365Signals();  // Empty signals
}
```

**Specific failure scenarios:**

**Scenario 1: GetBookings times out (Dataverse slow)**
- Retry with backoff: 5 retries over ~30 seconds
- If still fails after 30s: User already waited 30s, too long
- Decision: Fail the user (don't block longer)
- Log: Alert on-call engineer

**Scenario 2: M365 Graph unavailable**
- Retry 1x (quick)
- Fail after 1 retry (not critical)
- Log: Warning (not error)
- Result: Create time entries without meetings context

**Scenario 3: Create Batch partially fails**
- 100 entries to create, 95 succeed, 5 fail (validation errors)
- Transaction: Dataverse might rollback all on one error (depends on API)
- Decision: If rollback, fail user. If partial, log failed entries for audit.
- Better: Use idempotency keys so retries don't re-create successes

**Phase 0-1 philosophy:**
- Strict for correctness (Tier 1)
- Lenient for experience (Tier 2)
- Retry transient errors
- Fail permanently after threshold

**Tradeoff:**
- Too lenient (degrade all failures): Corrupt data
- Too strict (abort on any failure): Poor user experience

**Metrics:**
- Track: Tier 1 vs Tier 2 failure rates
- Alert if: Tier 1 > 2%, Tier 2 > 5%
- Decide: Retry threshold, backoff strategy

**At 50k users:**
- If 1% fail (500 users), manual retry? Not scalable
- Need: Automatic retry + checkpoint system
- Phase 2 adds: Checkpoint after every tool (resume from failure point)"

**Follow-up to probe deeper:**
- "How many retry attempts is reasonable? When is 'forever retry' wrong?"
- "If Create fails 50% through 100 entries, how do you recover?"
- "How do you distinguish transient (retry) from permanent (abort) failures?"

---

### Q8: "Dataverse has a 100 requests/sec rate limit. At 50k concurrent users, how do you handle this?"

**Why interviewers ask:**
- Tests understanding of rate limiting and throttling strategies
- Shows if you think about downstream dependencies and bottlenecks
- Reveals knowledge of when to queue, batch, or shed load

**Depth indicators:**

❌ **Junior:**
"Use exponential backoff retry."

❌ **Senior:**
"Implement SemaphoreSlim to limit concurrent requests."

✅ **Staff:**
"Rate limiting is critical at scale. Let's do the math:

**The Problem:**

Dataverse limit: 100 requests/sec
Time Entry Agent tools: 7 requests per user per execution
50k users processing simultaneously:

```
Naive: 50k users × 7 calls = 350k calls
If all in parallel: 350k ÷ 0.1 = 3.5M seconds of backpressure
That's not viable.
```

Actually, let me recalculate. The limit is 100 req/sec.
We're not actually sending 350k requests simultaneously.

```
Users are processed sequentially (per-user iteration):
- SemaphoreSlim(10) = 10 concurrent users max
- Each user: 7 Dataverse calls (sequential within user)
- Per user execution: ~4 sec (since Ra, Rb, TE parallel)
- 10 concurrent × 4 sec = 40 sec per batch
- Batches needed: 50k ÷ 10 = 5000 batches
- Total time: 5000 × 4 = 20,000 sec = 5.5 hours

Dataverse request rate:
- 10 concurrent users = some making Ra, some making Rb, etc.
- Peak: 10 users × 3 concurrent tools = 30 req/sec
- Steady state: lower (some users waiting for I/O)
- Well below 100 req/sec limit ✓
```

**But what if we increase concurrency?**

```
SemaphoreSlim(20):
- 20 concurrent users
- Peak: 20 × 3 = 60 req/sec
- Still safe

SemaphoreSlim(30):
- 30 concurrent users
- Peak: 30 × 3 = 90 req/sec
- Close to limit, risky

SemaphoreSlim(40):
- 40 concurrent users
- Peak: 40 × 3 = 120 req/sec
- Exceeds limit! Rate limiting kicks in
```

**How to Handle Rate Limiting:**

**Strategy 1: Conservative SemaphoreSlim**
```csharp
// Limit to 25 concurrent users
var semaphore = new SemaphoreSlim(25);

// Calculation:
// 25 users × 3 concurrent tools = 75 req/sec
// Well below 100 limit, safe margin
```

Pros:
- Simple, no complex retry logic
- Predictable performance
- Won't hit rate limits

Cons:
- Throughput capped (limited concurrency)
- Takes longer (5000 ÷ 25 = 200 batches)
- Underutilizes available bandwidth

**Strategy 2: Adaptive SemaphoreSlim + Rate Limit Handling**
```csharp
var semaphore = new SemaphoreSlim(initialConcurrency: 40);
var rateLimitBackoff = 1000;  // milliseconds

public async Task ProcessUsers(IEnumerable<User> users) {
    var tasks = users.Select(async user => {
        await semaphore.WaitAsync();
        try {
            var result = await ProcessUser(user);
            
            // Success - reset backoff
            rateLimitBackoff = 1000;
            return result;
        } catch (RateLimitException ex) {
            // Hit rate limit
            logger.Warn('Rate limit hit, backing off');
            rateLimitBackoff *= 2;  // Exponential backoff
            
            // Reduce concurrency
            semaphore.WaitHandle.Set();  // Release slot
            
            // Wait before retry
            await Task.Delay(rateLimitBackoff);
            
            // Retry same user
            return await ProcessUser(user);
        } finally {
            semaphore.Release();
        }
    }).ToList();
    
    await Task.WhenAll(tasks);
}
```

Pros:
- Higher throughput (start aggressive)
- Backoff when hitting limit
- Self-healing

Cons:
- Complex error handling
- Harder to debug (concurrency adapts)
- Risk of cascade (too many backoffs)

**Strategy 3: Batch Request Throttling**
```csharp
// Batch requests to stay under rate limit
var requestsPerSecond = 80;  // 80/100 = 80% utilization
var requestQueue = new Channel<Request>(capacity: 1000);

// Producer task (users adding requests)
_ = Task.Run(async () => {
    foreach (var user in users) {
        var requests = new[] {
            new Request(tool: 'GetAssignments', params: user),
            new Request(tool: 'GetBookings', params: user),
            // ...7 total
        };
        
        foreach (var req in requests) {
            await requestQueue.Writer.WriteAsync(req);
        }
    }
    requestQueue.Writer.Complete();
});

// Consumer task (throttled executor)
_ = Task.Run(async () => {
    var stopwatch = Stopwatch.StartNew();
    int requestCount = 0;
    
    await foreach (var request in requestQueue.Reader.ReadAllAsync()) {
        // Wait to maintain rate
        var expectedTime = (++requestCount / (double)requestsPerSecond) * 1000;
        var actualTime = stopwatch.ElapsedMilliseconds;
        
        if (actualTime < expectedTime) {
            await Task.Delay((int)(expectedTime - actualTime));
        }
        
        await ExecuteRequest(request);
    }
});
```

Pros:
- Smooth, predictable rate
- No bursts
- Works with any concurrency

Cons:
- Adds queue complexity
- Latency per request slightly higher

**Recommended for Phase 0-1:**

Start with **Strategy 1** (conservative SemaphoreSlim = 25):
- Simple to implement
- Guaranteed to not hit rate limits
- No retry complexity
- 50k users processed in ~200 batches × 4 sec = 800 sec = 13 minutes
- Fine for overnight runs

If throughput needed:
- Monitor actual Dataverse request rate
- If peak < 80 req/sec, increase to SemaphoreSlim(30)
- If peak > 90 req/sec, stay at 25

**At scale (Phase 2+ with 500k users):**
- Would need Strategy 3 or org-level batching
- Or partition by tenant/org (separate Dataverse instances)

**Monitoring:**
```csharp
_telemetry.RecordDataverseRequestRate(
    requestsPerSecond: currentRate,
    semaphoreCount: semaphore.CurrentCount,
    rateLimitHits: rateLimitCount
);

// Alert if:
// - requestsPerSecond > 95
// - rateLimitHits > 10 in 5 minutes
```"

**Follow-up to probe deeper:**
- "How do you know the actual request rate (not theoretical)?"
- "What happens if Dataverse rate limit changes (100 → 50 req/sec)?"
- "Should you queue user requests or drop them?"

---

### Q9: "Custom APIs have ~500ms latency (network + Dataverse). How does this affect your architecture?"

**Why interviewers ask:**
- Tests understanding of latency impact on system design
- Shows if you think about cascading delays
- Reveals knowledge of optimization opportunities

**Depth indicators:**

❌ **Junior:**
"Add 500ms for each API call."

❌ **Senior:**
"Use parallelization to hide latency."

✅ **Staff:**
"500ms per API is significant. Let's trace impact:

**Latency Breakdown (Phase 0-1):**

Current (8 sec total):
- Ra (GetAssignments): 2 sec
  - Custom API latency: 500ms
  - Dataverse query: 1.2 sec
  - Serialization: 300ms
- Rb (GetBookings): 1 sec
- TE (GetTimeEntries): 1 sec
- Intersect (calculate): 2 sec
- Comments (LLM): 0.5 sec
- Create: 1.5 sec

If we broke down further:
```
Sequential (no parallelization):
Ra + Rb + TE + Intersect + Comments + Create
= 2 + 1 + 1 + 2 + 0.5 + 1.5 = 8 sec

Parallel (with SemaphoreSlim):
max(Ra, Rb, TE) + Intersect + Comments + Create
= max(2, 1, 1) + 2 + 0.5 + 1.5 = 6 sec
```

500ms API latency impact:
- If we removed API latency entirely (instant): ~200ms savings per tool
- 7 tools × 200ms = 1.4 sec savings
- New total: 6 - 1.4 = 4.6 sec

**But we can't eliminate API latency.** What can we do?

**Option 1: Batch API calls (reduce count)**

Currently: 7 separate Custom API calls

Batch version:
```csharp
// Instead of 7 calls, use 1 call that returns all data
GET /api/data/v9.2/msdyn_GetResourceData
Response:
{
  assignments: [...],
  bookings: [...],
  existingTimeEntries: [...]
}

Latency: 500ms × 1 = 500ms
vs. current: 500ms × 3 = 1.5 sec
Savings: 1 sec per user
```

Problem: Can't parallelize anymore (single call takes 2-3 sec if it includes M365 Graph)

**Option 2: Async Custom APIs (non-blocking)**

Currently:
```
Request: GetAssignments
Wait: 2 sec
Response: Assignments list
```

Async version:
```
Request: GetAssignments
Response: { requestId: '123', status: 'pending' }
Immediately: Poll for result (or wait for callback)
Result comes back: 2 sec later
```

Benefit:
- MCS can send requests in parallel without blocking
- All 7 requests sent in ~50ms (network round trip)
- Then wait 2-3 sec for slowest to complete
- Same total time, but better concurrency model

**Option 3: Cache at multiple levels**

Level 1: Per-user cache (within single execution)
```
Ra (GetAssignments) returns result
Cache in memory for this user
If same data needed later: Use cache (instant)
```

Level 2: Org-level cache
```
Finance org has 100 users
All users need same set of projects
Instead of GetAssignments 100 times (2 sec × 100 = 200 sec)
GetAssignments once, cache for org (2 sec)
Share across all users

Cost savings: 200 - 2 = 198 sec!
```

Level 3: TTL-based cache
```
Cache assignments for 1 hour
All users in that hour reuse (zero latency)
If data changes: Invalidate cache, refetch
```

**Phase 0-1 approach:**
- No caching (keeps logic simple)
- Accept 8 sec latency
- Focus on parallelization

**Phase 2+ approach:**
- Add org-level cache (mentioned earlier)
- Cache with TTL (1 hour for assignments, 1 day for projects)
- Reduces redundant API calls significantly

**Impact of 500ms API latency at scale:**

At 50k users:
```
Sequential: 50k × 8 sec = 400k sec = 111 hours
If API latency removed: 50k × 4.6 sec = 230k sec = 64 hours
Savings: 47 hours (42% improvement!)
```

But achieving this requires:
1. Faster Dataverse queries (indexes, better queries)
2. Batching APIs (less modularity)
3. Caching (complex invalidation)

**Real optimization ROI:**

If we spent 1 week optimizing APIs to go from 2 sec to 1 sec (Ra):
```
Savings per user: 1 sec
50k users: 50k seconds = 14 hours per run
Over 1 year (250 runs): 3500 hours = 145 days!
```

Huge ROI. Good investment.

**Current bottleneck (Phase 0-1):**

Looking at 8 sec total:
```
Ra (2 sec) - BOTTLENECK
Rb (1 sec)
TE (1 sec)
Intersect (2 sec)
Comments (0.5 sec)
Create (1.5 sec)
```

Ra takes 2 sec. Why?
- Querying assignments (who's assigned to which projects)
- Could be 1000s of assignments per user
- SQL: SELECT * FROM Assignments WHERE ResourceId = X
- With index: Fast. Without: Slow.

Optimization:
```
Add database index on (ResourceId, ActiveOnly)
Test: Ra latency drops 2 sec → 1.2 sec

Savings: 0.8 sec per user
50k × 0.8 = 40k sec = 11 hours per run!
```

This is easier than rewriting code."

**Follow-up to probe deeper:**
- "What's the bottleneck in the 500ms Custom API latency?"
- "How would you measure whether caching is actually helping?"
- "At what scale does org-level batching become worth the complexity?"

---

### Q10: "Design the Custom API contract (request/response schema). What fields are required, optional, or derived?"

**Why interviewers ask:**
- Tests understanding of API design and data modeling
- Shows if you think about versioning and evolution
- Reveals knowledge of security (what to expose vs. hide)

**Depth indicators:**

❌ **Junior:**
"Accept userId, return array of time entries."

❌ **Senior:**
"Accept userId + dateRange, return assignments with details."

✅ **Staff:**
"Good question. API design affects everything downstream.

**Custom API Endpoints (Phase 0-1):**

Each tool has its own endpoint. Let's design each:

**1. GetAssignments Endpoint**

Request:
```json
{
  "userId": "alice@acme.com",  // Required, email
  "dateRange": {
    "start": "2025-05-05",     // Required, ISO 8601
    "end": "2025-05-09"        // Required, ISO 8601
  },
  "includeInactive": false,     // Optional, default false
  "projectFilter": null        // Optional, project IDs to filter
}
```

Response:
```json
{
  "status": "success",
  "correlationId": "550e8400-e29b-41d4-a716-446655440000",
  "data": {
    "assignments": [
      {
        "assignmentId": "assign-123",
        "projectId": "proj-A",
        "projectName": "Feature Design",
        "allocatedHours": 40,
        "startDate": "2025-05-05",
        "endDate": "2025-05-09",
        "resourceRole": "Developer"
      },
      ...
    ],
    "pagination": {
      "total": 150,
      "returned": 2,
      "hasMore": true
    }
  },
  "timestamp": "2025-05-03T08:00:00Z",
  "duration": 1820  // milliseconds
}
```

Design decisions:
- **correlationId**: Trace entire request flow for logging
- **status**: Immediate check if call succeeded (don't parse data)
- **duration**: Monitor latency
- **pagination**: Future-proof for org with 1000s of assignments

**2. GetBookings Endpoint**

Similar structure:
```json
{
  "userId": "alice@acme.com",
  "dateRange": { "start": "...", "end": "..." },
  "data": {
    "bookings": [
      {
        "bookingId": "book-456",
        "projectId": "proj-A",
        "bookedHours": 40,
        "bookingType": "Committed",
        "startDate": "2025-05-05"
      },
      ...
    ]
  }
}
```

Key difference:
- Bookings = committed hours (contract)
- Assignments = allocated work (actual)
- One doesn't equal other

**3. GetTimeEntries Endpoint**

Request:
```json
{
  "userId": "alice@acme.com",
  "dateRange": { "start": "...", "end": "..." },
  "status": "Submitted"  // Optional, filter by status
}
```

Response:
```json
{
  "data": {
    "entries": [
      {
        "entryId": "te-789",
        "projectId": "proj-A",
        "hours": 8,
        "date": "2025-05-05",
        "description": "Feature implementation",
        "comment": "Completed UI mockups",
        "status": "Submitted",
        "createdBy": "System",
        "createdOn": "2025-05-03T08:15:00Z"
      }
    ]
  }
}
```

Why separate GetExisting from Create?
- GET (query existing) vs. POST (create new) separation
- Standard REST pattern
- Easy to cache GET, invalidate on POST

**4. CalculateDelta Endpoint**

Request (composite):
```json
{
  "userId": "alice@acme.com",
  "assignments": [ /* from GetAssignments */ ],
  "bookings": [ /* from GetBookings */ ],
  "existing": [ /* from GetTimeEntries */ ]
}
```

Response:
```json
{
  "delta": {
    "toCreate": [
      {
        "projectId": "proj-A",
        "hours": 8,
        "date": "2025-05-05",
        "reason": "Booking matched, no existing entry"
      }
    ],
    "toUpdate": [
      {
        "entryId": "te-789",
        "newHours": 8,
        "reason": "Booking increased from 6h to 8h"
      }
    ],
    "toDelete": []
  }
}
```

Critical: CalculateDelta receives other data as input, not just userId
- This breaks strict REST (endpoints should be independent)
- But necessary for tool orchestration
- Alternative: Pass derived data in composite request

**5. GenerateComments Endpoint**

Request:
```json
{
  "userId": "alice@acme.com",
  "entries": [ /* delta entries to create */ ],
  "m365Signals": {
    "meetings": [ /* Calendar events */ ],
    "emails": [ /* Relevant emails */ ]
  }
}
```

Response:
```json
{
  "comments": [
    {
      "entryIndex": 0,
      "comment": "Feature design session (team sync Monday 9am, roadmap email Friday)"
    }
  ]
}
```

Note: Comments are optional enhancement
- If fails, create entries without comments
- Don't block on comment generation

**6. CreateBatch Endpoint**

Request:
```json
{
  "userId": "alice@acme.com",
  "entries": [
    {
      "projectId": "proj-A",
      "hours": 8,
      "date": "2025-05-05",
      "description": "Feature implementation",
      "comment": "Team sync + design review"
    }
  ],
  "idempotencyKey": "user-123-week-18-2025"  // For duplicate prevention
}
```

Response:
```json
{
  "status": "success",
  "created": [
    {
      "entryId": "te-new-1",
      "projectId": "proj-A",
      "status": "Submitted"
    }
  ],
  "failed": [],
  "summary": {
    "totalRequested": 8,
    "totalCreated": 8,
    "totalFailed": 0
  }
}
```

Idempotency key:
- If same key sent twice → Return same result (no duplicate entries)
- Critical for retry safety

**Versioning Strategy:**

All endpoints should support versioning:

```
POST /api/data/v9.2/msdyn_GetAssignments
Headers: X-API-Version: 1.0
```

Example evolution:
```
v1.0: Return assignments array
v1.1: Add 'resourceRole' field
v2.0: Change response schema, deprecate v1.0
```

**Security Considerations:**

Never expose:
- Salary information
- Other users' data (users must own their own userId)
- Sensitive comments ('paid time off', 'sick leave detail')

Always include:
- correlationId (for audit)
- userId (in response, verify it matches request)
- Timestamp

**Error Response Schema:**

```json
{
  "status": "error",
  "error": {
    "code": "INVALID_USER",
    "message": "User not found or inactive",
    "details": "User alice@acme.com not found in Dataverse"
  },
  "correlationId": "550e8400..."
}
```

Standard error codes:
- INVALID_USER: User doesn't exist
- INSUFFICIENT_PERMISSIONS: RBAC check failed
- RATE_LIMITED: Too many requests
- TIMEOUT: Operation took too long
- INTERNAL_ERROR: Something broke

**Contract for MCS (Orchestrator):**

MCS expects all tools to return:
```
{
  status: 'success' | 'error' | 'timeout',
  data: any,  // Tool-specific data
  error: { code, message },
  duration: number,
  correlationId: string
}
```

This standardization lets MCS handle failures uniformly."

**Follow-up to probe deeper:**
- "How do you handle schema versioning without breaking MCS?"
- "What happens if GetAssignments returns 10,000 results?"
- "Should you include auth errors in response or HTTP status codes?"

---

### Q11: "How do you log and trace issues across 7 distributed API calls? Design your telemetry strategy."

**Why interviewers ask:**
- Tests understanding of distributed tracing and observability
- Shows if you think about debugging at scale
- Reveals operational maturity

**Depth indicators:**

❌ **Junior:**
"Log each API call result."

❌ **Senior:**
"Use correlation IDs to link logs."

✅ **Staff:**
"Observability is critical with 7 tools and 50k users per run.

**Distributed Tracing Strategy:**

**Core: Correlation ID**

Flow through entire stack:
```
Power Automate (trigger)
  ├─ Generate: correlationId = UUID
  ├─ Pass to Custom API: POST /msdyn_CreateTimeEntries?cid=550e8400
  ├─ Custom API logs: cid=550e8400
  │
  ├─ Call MCS: POST /orchestrate (pass cid in header)
  │  └─ MCS logs: cid=550e8400
  │
  ├─ MCS calls Tool1: POST /msdyn_GetAssignments (X-Correlation-ID: 550e8400)
  │  └─ Tool logs: cid=550e8400
  │
  ├─ Tool calls Dataverse: Query (pass cid in header)
  │  └─ Dataverse logs: cid=550e8400
  │
  └─ Trace complete: All logs linked by cid

If error occurs:
  - Query all logs with cid=550e8400
  - Entire flow visible in one search
  - No manual matching of timestamps
```

**Log Levels (Strategic):**

```
Level 1: TRACE
- Entry/exit of each function
- Parameter values
- Local variable state
- Too verbose for production (disable)

Level 2: DEBUG
- API call details
- Response received
- Parsing logic
- Use during development/investigation

Level 3: INFO
- Tool execution started
- Tool completed (success)
- Duration
- Use in production

Level 4: WARN
- Tool failed (Tier 2 enrichment like M365)
- Retry triggered
- Performance degradation
- Use in production

Level 5: ERROR
- Critical tool failed (Tier 1 like GetAssignments)
- User sync failed
- Data corruption detected
- Use in production + alert

Level 6: FATAL
- System unable to continue
- Queue poisoned
- Dataverse connection lost
- Use + page on-call engineer
```

**Log Schema (Structured):**

```json
{
  "timestamp": "2025-05-03T08:15:22.456Z",
  "level": "INFO",
  "correlationId": "550e8400-e29b-41d4-a716-446655440000",
  "userId": "alice@acme.com",
  "tool": "GetAssignments",
  "event": "tool.started",
  "duration": null,
  "status": null,
  "error": null,
  "metadata": {
    "dateRange": { "start": "2025-05-05", "end": "2025-05-09" },
    "environment": "production",
    "tenant": "acme-corp"
  }
}
```

Then completed:
```json
{
  "timestamp": "2025-05-03T08:15:24.100Z",
  "level": "INFO",
  "correlationId": "550e8400-...",
  "userId": "alice@acme.com",
  "tool": "GetAssignments",
  "event": "tool.completed",
  "duration": 1644,
  "status": "success",
  "error": null,
  "metadata": {
    "resultCount": 2,
    "assignments": [...]  // Only in DEBUG level
  }
}
```

**Metrics Collection:**

Track per-tool:
```
- Duration (min, max, p50, p95, p99)
- Success rate
- Failure reasons (timeout, invalid user, rate limited, etc.)
- Retry count
```

Example dashboard:
```
GetAssignments:
  Duration: [p50: 1.2s, p95: 2.1s, p99: 3.5s]
  Success: 99.2%
  Errors:
    - Timeout: 0.3%
    - Invalid user: 0.5%

GetBookings:
  Duration: [p50: 0.8s, p95: 1.2s, p99: 1.8s]
  Success: 99.8%
  Errors: < 0.2%

...
```

**Alerts (Pro-active monitoring):**

Alert if:
```
1. Tool error rate > 2%
2. Tool latency p95 > 5s
3. Retry rate > 10%
4. Rate limit hits > 5 in 5 min
5. Users failed > 1% of batch
```

Example alert:
```
GetAssignments: Error rate 2.5% (threshold 2%)
Potential causes:
  - Dataverse overloaded
  - Query index missing
  - User access revoked
Action: Check Dataverse health, review slow queries
```

**Agent Metadata Table (Persistent Log):**

Store summary per user execution:
```
CREATE TABLE msdyn_AgentMetadata (
  msdyn_AgentMetadataId GUID PRIMARY KEY,
  msdyn_CorrelationId VARCHAR(100),
  msdyn_UserId VARCHAR(100),
  msdyn_ExecutionStarted DATETIME,
  msdyn_ExecutionCompleted DATETIME,
  msdyn_TotalDuration INT,  -- milliseconds
  msdyn_EntriesCreated INT,
  msdyn_EntriesFailed INT,
  msdyn_Status VARCHAR(20),  -- success, partial, failed
  msdyn_ErrorMessage TEXT,
  msdyn_ToolExecutionLog TEXT  -- JSON array of tool results
);
```

Example row:
```
CorrelationId: 550e8400-...
UserId: alice@acme.com
ExecutionStarted: 2025-05-03 08:15:20
ExecutionCompleted: 2025-05-03 08:15:28
TotalDuration: 8000
EntriesCreated: 8
EntriesFailed: 0
Status: success
ErrorMessage: null
ToolExecutionLog: [
  { tool: 'GetAssignments', duration: 1644, status: 'success' },
  { tool: 'GetBookings', duration: 980, status: 'success' },
  ...
]
```

**Query for debugging:**

```sql
SELECT * FROM msdyn_AgentMetadata
WHERE msdyn_CorrelationId = '550e8400-...'
-- Shows everything about this execution

SELECT * FROM msdyn_AgentMetadata
WHERE msdyn_UserId = 'alice@acme.com'
AND msdyn_ExecutionStarted > DATEADD(day, -7, GETDATE())
-- Shows Alice's execution history for past week

SELECT 
  msdyn_Status,
  COUNT(*) as Count,
  AVG(msdyn_TotalDuration) as AvgDuration
FROM msdyn_AgentMetadata
WHERE msdyn_ExecutionStarted > DATEADD(day, -1, GETDATE())
GROUP BY msdyn_Status
-- Shows daily summary
```

**Visualization (Observability):**

Timeline for single execution (from logs):
```
08:15:20.000 | Flow triggered
08:15:20.100 | Custom API received request
08:15:20.150 | MCS called (3 tools in parallel)
08:15:20.200 | Tool1 (GetAssignments) started
08:15:20.210 | Tool2 (GetBookings) started
08:15:20.220 | Tool3 (GetTimeEntries) started
08:15:21.500 | Tool1 completed (1.3s)
08:15:21.800 | Tool2 completed (1.6s)  ← Slowest of first batch
08:15:21.850 | Tool3 completed (1.63s)
08:15:21.860 | CalculateDelta started
08:15:23.860 | CalculateDelta completed (2.0s)
08:15:23.900 | GetM365Signals started
08:15:24.200 | GenerateComments started (parallel with M365)
08:15:24.300 | M365 completed (0.4s)
08:15:24.600 | Comments completed (0.7s)
08:15:24.610 | CreateBatch started
08:15:26.100 | CreateBatch completed (1.49s)
08:15:26.150 | Custom API returned
08:15:26.200 | Flow completed

Total: 6.2 seconds
Bottleneck: CalculateDelta (2s)
```

This visualization identifies where time goes.

**Privacy/Compliance:**

Log strategy respects:
- GDPR: Don't log sensitive data (salary, health info)
- Audit: Log enough to prove compliance
- Performance: Structured logging doesn't slow down system

Never log:
- Full request/response bodies (only schemas)
- User credentials
- Sensitive business data
- PII beyond user ID

Always log:
- User ID (for audit)
- Timestamp (for timeline)
- Correlation ID (for tracing)
- Action taken (create, read, update, delete)
- Result (success/failure)"

**Follow-up to probe deeper:**
- "How do you handle logs from multiple instances/regions?"
- "What's your log retention policy? How long do you keep logs?"
- "How do you search logs for a specific user across all correlation IDs?"

---

### Q12: "Design the retry strategy for the entire flow. When do you retry, how many times, and with what backoff?"

**Why interviewers ask:**
- Tests understanding of resilience and failure recovery
- Shows if you think about cascading failures and resource waste
- Reveals operational maturity

**Depth indicators:**

❌ **Junior:**
"Retry up to 3 times with exponential backoff."

❌ **Senior:**
"Retry transient errors (timeout, 5xx) but not user errors (400, 404)."

✅ **Staff:**
"Retry strategy is nuanced. Let me break it down:

**Error Classification:**

**Tier 1: Retryable (Transient)**
- Timeout: Network slow, try again
- 503 Service Unavailable: Service recovering
- 429 Rate Limited: Try again later
- 500 Internal Server Error: Might be transient
- Connection reset: Network flake

**Tier 2: Non-Retryable (Permanent)**
- 400 Bad Request: Invalid input, retry won't help
- 401 Unauthorized: Token issue, won't resolve in 10 seconds
- 403 Forbidden: Permission denied
- 404 Not Found: Resource doesn't exist
- 422 Unprocessable Entity: Data validation failed

**Tier 3: Partial Retry**
- 409 Conflict: Retry with new data (idempotent)
- 413 Payload Too Large: Reduce batch size, retry

**Retry Strategy by Tool:**

**Critical Tools (Tier 1: Must Succeed)**
GetAssignments, GetBookings, GetTimeEntries, CreateBatch

```csharp
public async Task<Result> GetAssignmentsWithRetry(userId, dateRange) {
    var maxRetries = 5;
    var backoffMs = 1000;
    
    for (int attempt = 0; attempt <= maxRetries; attempt++) {
        try {
            return await GetAssignments(userId, dateRange);
        } catch (HttpRequestException ex) when (IsRetryable(ex)) {
            if (attempt == maxRetries) throw;
            
            // Exponential backoff: 1s, 2s, 4s, 8s, 16s
            var delay = backoffMs * Math.Pow(2, attempt);
            logger.Warn($'GetAssignments retry {attempt + 1}/{maxRetries} after {delay}ms');
            
            await Task.Delay((int)delay);
        }
    }
}

private bool IsRetryable(HttpRequestException ex) {
    // Check HTTP status code
    if (ex.StatusCode == HttpStatusCode.RequestTimeout) return true;
    if (ex.StatusCode == HttpStatusCode.ServiceUnavailable) return true;
    if (ex.StatusCode == HttpStatusCode.TooManyRequests) return true;
    if (ex.StatusCode == HttpStatusCode.InternalServerError) return true;
    
    // Check inner exception (network errors)
    if (ex.InnerException is TimeoutException) return true;
    if (ex.InnerException is IOException) return true;
    
    return false;
}
```

Backoff curve: 1s → 2s → 4s → 8s → 16s = 31 seconds total
If fails after 5 retries: Give up, log error, alert engineer

**Enrichment Tools (Tier 2: Nice to Have)**
GetM365Signals, GenerateComments

```csharp
public async Task<M365Signals> GetM365SignalsWithRetry(userId, dateRange) {
    var maxRetries = 1;  // Only 1 retry
    
    try {
        return await GetM365Signals(userId, dateRange);
    } catch {
        if (maxRetries > 0) {
            await Task.Delay(1000);
            try {
                return await GetM365Signals(userId, dateRange);
            } catch (Exception ex) {
                logger.Warn($'M365Signals failed after retry: {ex}');
                // Return empty signals, continue
                return new M365Signals();
            }
        }
    }
}
```

Key: Give up quickly (1 retry only), degrade gracefully

**Partial Failure Handling (CreateBatch):**

Creating 100 entries, 95 succeed, 5 fail (validation errors):

```csharp
public async Task CreateEntriesWithRetry(entries) {
    var toCreate = entries.ToList();
    var maxAttempts = 3;
    
    for (int attempt = 0; attempt < maxAttempts; attempt++) {
        var result = await CreateBatch(toCreate);
        
        if (result.Failed.Count == 0) {
            // All succeeded
            return result;
        }
        
        if (IsRetryable(result.Failed)) {
            // Some are transient failures (e.g., conflict)
            toCreate = result.Failed.Where(f => f.IsRetryable).ToList();
            
            if (toCreate.Count > 0 && attempt < maxAttempts - 1) {
                var delay = 1000 * (attempt + 1);
                await Task.Delay(delay);
                continue;  // Retry only failed entries
            }
        }
        
        // Non-retryable failures or max attempts reached
        break;
    }
    
    // Log result
    logger.Info($'CreateBatch: {result.Succeeded} created, {result.Failed} failed');
}
```

**User-Level Retry (Entire Execution):**

If a user's entire execution fails:

```
Attempt 1 (8s timeout):
  GetAssignments → Timeout (Dataverse overloaded)
  Retry: GetAssignments with backoff
  Eventually: Fail after 5 retries, user fails

Next batch (after how long?):
  Option A: Immediate retry (next cycle)
  Option B: Wait 1 hour (let system stabilize)
  Option C: Exponential backoff per user
```

Recommended: **Option C (Exponential backoff per user)**

```csharp
public class RetryPolicy {
    public class UserRetryState {
        public string UserId { get; set; }
        public int FailureCount { get; set; }
        public DateTime LastAttempt { get; set; }
    }
    
    private Dictionary<string, UserRetryState> _userStates;
    
    public bool ShouldRetry(string userId) {
        if (!_userStates.TryGetValue(userId, out var state)) {
            return true;  // First time, yes
        }
        
        // Calculate backoff: 1h, 2h, 4h, 8h, 24h
        var backoffHours = Math.Min(Math.Pow(2, state.FailureCount - 1), 24);
        var nextRetryTime = state.LastAttempt.AddHours(backoffHours);
        
        return DateTime.UtcNow >= nextRetryTime;
    }
    
    public void RecordFailure(string userId) {
        if (!_userStates.ContainsKey(userId)) {
            _userStates[userId] = new UserRetryState { UserId = userId };
        }
        
        var state = _userStates[userId];
        state.FailureCount++;
        state.LastAttempt = DateTime.UtcNow;
        
        logger.Warn($'User {userId} failed {state.FailureCount} times, next retry in {Math.Pow(2, state.FailureCount - 1)} hours');
    }
    
    public void RecordSuccess(string userId) {
        if (_userStates.ContainsKey(userId)) {
            _userStates.Remove(userId);  // Reset state
        }
    }
}
```

Timeline:
```
Day 1, 8 AM: User sync fails
Day 1, 1 PM (5h later): Manual admin retry triggers
Day 1, 3 PM: Next scheduled run, doesn't retry (still in backoff)
Day 2, 8 AM: 24 hours later, retry occurs (failure count reset)
```

**Circuit Breaker (System Level):**

If error rate for a tool > 10% for 5 minutes:

```csharp
public class CircuitBreaker {
    private int _failureCount = 0;
    private DateTime _windowStart = DateTime.UtcNow;
    private bool _isOpen = false;
    
    public async Task<Result> ExecuteWithCircuitBreaker(Func<Task<Result>> operation) {
        if (_isOpen) {
            throw new CircuitBreakerOpenException('Tool experiencing too many failures');
        }
        
        try {
            var result = await operation();
            _failureCount = 0;  // Reset on success
            return result;
        } catch {
            _failureCount++;
            
            var elapsedSeconds = (DateTime.UtcNow - _windowStart).TotalSeconds;
            var errorRate = _failureCount / (elapsedSeconds / 60);  // Rough estimate
            
            if (errorRate > 0.1 && elapsedSeconds < 300) {
                // > 10% error rate in 5 min window
                _isOpen = true;
                logger.Error('Circuit breaker OPEN for tool');
                
                // Auto-close after 1 minute
                _ = Task.Delay(60000).ContinueWith(_ => _isOpen = false);
            }
            
            throw;
        }
    }
}
```

When circuit opens:
- Stop sending requests (fail fast)
- Let tool recover for 1 minute
- Then retry

**Monitoring Retry Metrics:**

Track:
```
- Retry rate per tool
- Success rate after retry
- Average retry count per user
- Retry distribution (1 vs. 5 retries)
```

Alert if:
```
- Retry success rate < 50% (retries are futile)
- Average retry count > 2 per tool (something broken)
- Any tool retry rate > 20% (degradation)
```

**Example Retry Flow:**

```
User execution starts
  ├─ GetAssignments (attempt 1)
  │  └─ Timeout (transient)
  │     └─ Backoff 1s, retry (attempt 2)
  │        └─ Timeout (transient)
  │           └─ Backoff 2s, retry (attempt 3)
  │              └─ Success ✓
  │
  ├─ GetBookings (attempt 1)
  │  └─ 403 Forbidden (permanent, don't retry)
  │     └─ Log error, try fallback
  │        └─ Fallback fails
  │           └─ Mark as Tier 2 enrichment, skip
  │
  ├─ CreateBatch (attempt 1)
  │  └─ 95 succeed, 5 conflict (retryable)
  │     └─ Retry only 5 (attempt 2)
  │        └─ All 5 succeed ✓
  │
  └─ Result: 8 total created, 0 failures (User succeeds)"

**Follow-up to probe deeper:**
- "How long should you wait before giving up on a user?"
- "What if retries themselves are causing load (dogpile)?"
- "How do you test retry logic without waiting hours?"

---

## Scaling & Performance Questions (8)

### Q13: "Explain the SemaphoreSlim(10) throttling. Why 10? How do you tune this number?"

[Content on throttling tuning, concurrency limits, resource utilization...]

### Q14: "At what point does org-level batching become worth implementing? What's the break-even?"

[Content on batching ROI, duplicate reduction, complexity vs. benefit...]

### Q15: "Design a caching strategy that reduces redundant Dataverse queries by 90%."

[Content on cache levels, TTL, invalidation, distributed caching...]

### Q16: "How would you handle 500k concurrent users (100x scale increase)? What breaks?"

[Content on bottleneck analysis, architectural changes needed...]

### Q17: "Design a checkpoint/resume system so you can restart from failures without reprocessing."

[Content on stateful retries, persistence, idempotency across restarts...]

### Q18: "What's the cost breakdown at 50k users? Where's the biggest spend?"

[Content on compute, API calls, storage, LLM, infrastructure cost analysis...]

### Q19: "How would you load test this architecture? What metrics matter most?"

[Content on load testing strategy, metrics, bottleneck identification...]

### Q20: "Design an org-level batching strategy. How does it reduce latency?"

[Content on cross-user optimization, metadata caching, batch API design...]

---

## Security & Isolation Questions (6)

### Q21: "Walk through an S2S token compromise scenario. What's the blast radius?"

[Content on token security, compromise handling, audit trails...]

### Q22: "Design row-level security enforcement at the API layer."

[Content on RBAC, query filtering, security at each layer...]

### Q23: "How do you prevent cross-tenant data leakage?"

[Content on multi-tenancy, isolation, shared infrastructure risks...]

### Q24: "Audit trail requirement: Prove which user action caused each time entry. Design it."

[Content on audit logging, tamper-proofing, compliance requirements...]

### Q25: "How would you handle a security incident (e.g., unauthorized time entries detected)?"

[Content on incident response, rollback, forensics...]

### Q26: "Design a permission model where org admins can audit but not modify time entries."

[Content on role-based access, audit-only roles, separation of duties...]

---

## RAG & LLM Integration Questions (6)

### Q27: "Explain the RAG flow. When does the LLM intervene vs. deterministic logic?"

[Content on RAG architecture, LLM decision points, reliability...]

### Q28: "How do you prevent LLM hallucinations (inventing time entries that don't exist)?"

[Content on constraints, validation, grounding in data...]

### Q29: "Design a fallback strategy if Azure OpenAI is down."

[Content on LLM failover, degraded mode, alternative models...]

### Q30: "The LLM generated a comment that violates company policy. How do you prevent this?"

[Content on prompt engineering, validation, policy enforcement...]

### Q31: "Cost optimization: Generate comments for only 10% of entries (sample), interpolate for rest."

[Content on sampling strategy, interpolation, statistical validity...]

### Q32: "Design a feedback loop where users correct LLM comments, and the model learns."

[Content on feedback capture, model retraining, continuous improvement...]

---

**End of Phase 0-1 Interview Prep**

This document covers foundational architecture mastery for Staff-level roles. Use it to prepare by:

1. Reading Q1-Q7 thoroughly (architecture foundations)
2. Studying Q8-Q12 (design decisions at scale)
3. Reviewing Q13-Q20 (performance optimization)
4. Understanding Q21-Q26 (security & compliance)
5. Learning Q27-Q32 (LLM integration & reliability)

**Interview tip:** Interviewers often start with Q1 or Q2 (full flow understanding) then probe deeper based on your answer. Be ready to explain any layer in detail.
