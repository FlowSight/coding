# Phase 2: MCP Server Extension Interview Prep

**Project Phase:** Phase 2 (MCP Abstraction Layer & Tool Standardization)  
**Scale:** 50k → 500k users (architectural preparation)  
**Key Metrics:** Same 8 sec/user latency, improved org-level batching via MCP  
**Focus:** MCP protocol, service abstraction, fallback patterns, tool discovery, service tree scoping  
**Interview Level:** Staff → Principal (architectural abstraction mastery)

---

## Table of Contents

1. [Phase 2 Overview](#phase-2-overview)
2. [MCP Architecture Questions (10)](#mcp-architecture-questions-10)
3. [Abstraction & Standardization Questions (8)](#abstraction--standardization-questions-8)
4. [Fallback & Resilience Questions (6)](#fallback--resilience-questions-6)
5. [Scaling & Reusability Questions (6)](#scaling--reusability-questions-6)

---

## Phase 2 Overview

### What Changed From Phase 0-1 to Phase 2

**Phase 0-1:** Direct HTTP calls from MCS to Custom APIs
```
MCS → Custom API #1 (GetAssignments)
MCS → Custom API #2 (GetBookings)
...
MCS → Custom API #7 (CreateBatch)
```

**Phase 2:** Abstraction layer (MCP servers) wrapping Custom APIs
```
MCS → MCP Protocol
     ├── Dataverse MCP Server
     │   ├── Custom API #1
     │   ├── Custom API #2
     │   └── Custom API #7
     └── M365 MCP Server
         ├── Teams/Meetings
         └── Mail/Emails
```

### Key Evolution

| Aspect | Phase 0-1 | Phase 2 | Benefit |
|--------|-----------|---------|---------|
| **Tool interface** | Direct HTTP | MCP protocol | Standardized, discoverable |
| **Tool scoping** | All tools global | Service Tree ID scoped | Prevents hallucination |
| **Fallback** | Hardcoded retry | MCP → Direct API fallback | Better resilience |
| **Reusability** | Time Agent only | Any agent can use MCP | Platform leverage |
| **Tool discovery** | Manual config | Dynamic via MCP | Flexible |

### Why MCP (Strategic Decision)

**Microsoft's direction:** Moving toward MCP as standard for agent-tool communication
- LLMs should call standardized tools, not custom HTTP endpoints
- MCP provides uniform protocol: discovery, invocation, response handling
- Future-proofs the architecture (independent of specific agent platform)

**For Time Entry Agent:**
- Already had good Custom APIs
- MCP wraps them (minimal rewrite)
- Enables org-level optimizations (metadata, service tree)
- Sets foundation for Phase 3+ (multi-agent platform)

---

## MCP Architecture Questions (10)

### Q1: "Walk me through the Phase 2 architecture. How is MCP different from Phase 0-1? Show me the HTTP flow."

**Why interviewers ask:**
- Tests if you understand abstraction layers and their value
- Shows if you can compare before/after designs
- Reveals knowledge of protocol design

**Depth indicators:**

❌ **Junior:**
"MCP is another layer that calls the same APIs."

❌ **Senior:**
"MCP standardizes the tool protocol so agents can discover and call tools."

✅ **Staff:**
"Great question. Let me trace both flows:

**Phase 0-1 Flow (Direct):**
```
1. Flow triggers: FOR user in users
2. Calls Custom API: POST /msdyn_CreateTimeEntries
   Body: { userId, dateRange, correlationId }
3. Custom API logic:
   - Validate user
   - Call MCS directly (orchestrator)
4. MCS invokes tools (each = HTTP call):
   - POST /msdyn_GetAssignments
   - POST /msdyn_GetBookings
   - POST /msdyn_GetTimeEntries
   - ...etc
5. MCS orchestrates results, LLM for comments
6. Custom API returns: { created: 8, failed: 0 }

HTTP calls per user:
- Custom API entry point: 1
- MCS tools: 7
- Total per user: 8 HTTP calls
- Latency: 8 seconds
```

**Phase 2 Flow (MCP Abstraction):**
```
1. Flow triggers: FOR user in users
2. Calls Custom API: POST /msdyn_CreateTimeEntries (same endpoint)
   Body: { userId, dateRange, correlationId, usesMCP: true }
3. Custom API logic:
   - Validate user
   - Create MCP context (service tree = Time Entry Agent)
4. Call MCS with MCP mode enabled
5. MCS DISCOVERS available tools via MCP:
   POST /mcp/discover
   Response: [GetAssignments, GetBookings, GetTimeEntries, ...]
   (Scoped to: D365 → Project Ops → Time Entry Agent)
6. MCS invokes tools via MCP:
   POST /mcp/invoke
   { tool: 'GetAssignments', params: {...} }
7. MCP server routes to underlying Custom API:
   GetAssignments (MCP) → Internal: POST /msdyn_GetAssignments (HTTP)
8. MCP returns result (standardized format)
9. MCS orchestrates (same as before)
10. Custom API returns: { created: 8, failed: 0 }

HTTP calls per user:
- Custom API entry point: 1
- MCS → MCP discovery: 1 (cached hourly)
- MCS → MCP invoke: 7
- MCP → Custom APIs: 7 (internal, cached)
- Total per user: ~9 (similar)

Latency: 8-9 seconds (same, maybe 10% slower due to MCP layer)
But: MCP layer enables optimizations
```

**Key difference: Abstraction + Scoping**

Phase 0-1:
```
MCS has hardcoded list:
[GetAssignments, GetBookings, ...]

If LLM gets confused:
'I need GetDepartmentInfo' (hallucination)
MCS tries to call it (fails)
```

Phase 2:
```
MCS discovers tools from MCP:
MCP says: 'Available tools for Time Entry Agent are: [GetAssignments, GetBookings, ...]'
LLM sees ONLY these tools (scoped)

If LLM gets confused:
'I need GetDepartmentInfo'
MCP says: 'Tool not available'
LLM can't call (not in scope)
Prevents hallucination
```

**MCP Protocol Details:**

```
MCP Discovery Request:
{
  type: 'discover',
  context: {
    serviceTree: 'D365/Project-Ops/Time-Entry-Agent',
    tenant: 'acme-corp',
    userId: 'alice@acme.com'
  }
}

MCP Discovery Response:
{
  tools: [
    {
      id: 'get_assignments',
      name: 'GetAssignments',
      description: 'Retrieve resource assignments for user',
      params: [
        { name: 'userId', type: 'string', required: true },
        { name: 'dateRange', type: { start, end }, required: true }
      ],
      rateLimit: '100 per hour'
    },
    { id: 'get_bookings', ... },
    ...
  ]
}

MCS Tool Invoke:
{
  type: 'invoke',
  tool: 'get_assignments',
  params: {
    userId: 'alice@acme.com',
    dateRange: { start: '2025-05-05', end: '2025-05-09' }
  }
}

MCP Tool Response:
{
  status: 'success',
  result: [
    { projectId: 'A', title: 'Feature Design', hours: 8 },
    { projectId: 'B', title: 'Testing', hours: 4 }
  ]
}
```

**Why MCP Protocol > Direct HTTP:**

1. **Standardized response format**
   - Phase 0-1: Each tool returns different format (JSON, XML mix)
   - Phase 2: All tools return { status, result, error }
   - Benefit: MCS orchestrator simpler, less parsing

2. **Service discovery**
   - Phase 0-1: MCS has hardcoded URL list
   - Phase 2: MCP tells MCS what's available
   - Benefit: Add new tools without MCS config change

3. **Scoping prevents hallucination**
   - Phase 0-1: LLM could hallucinate tools
   - Phase 2: LLM only sees tools in scope
   - Benefit: Deterministic, predictable behavior

4. **Versioning + fallback**
   - Phase 0-1: Tool changes break MCS
   - Phase 2: MCP version = tool interface version
   - Benefit: Graceful degradation (use fallback if version mismatch)

**Fallback Mechanism (Critical in Phase 2):**

```
Primary path: MCS → MCP invoke
├─ If success: Use result
├─ If MCP unavailable: Fall back to Direct Custom API
│  └─ Use Phase 0-1 direct endpoint
└─ If both fail: Retry with backoff, then abort

Fallback logic in Custom API:
```csharp
public async Task<Result> GetAssignmentsViaMCP(userId, dateRange) {
    try {
        // Try MCP first
        var mcpResult = await MCSOrchestrator.InvokeToolVia MCP(
            'get_assignments',
            new { userId, dateRange }
        );
        return mcpResult;
    } catch (MCPUnavailableException) {
        logger.Warn('MCP unavailable, falling back to direct API');
        // Fall back to Phase 0-1
        return await DirectCustomAPI.GetAssignments(userId, dateRange);
    }
}
```

This dual path ensures:
- Phase 2 benefits when MCP works (better scoping, standardization)
- Phase 0-1 fallback when MCP fails (reliability)
- Zero downtime during MCP migration/failures

**Performance comparison:**

| Metric | Phase 0-1 | Phase 2 | Delta |
|--------|-----------|---------|-------|
| **Per-user latency** | 8.0 sec | 8.8 sec | +10% (MCP overhead) |
| **Latency p95** | 12 sec | 13.2 sec | Similar |
| **Scoping benefit** | None | Prevents hallucination | Qualitative |
| **Tool reusability** | Single agent | Multiple agents | Qualitative |
| **Operational complexity** | 7 direct APIs | 7 APIs + 2 MCP servers | Slight increase |

The 10% latency increase is acceptable for the benefits (hallucination prevention, reusability)."

**Follow-up to probe deeper:**
- "How do you handle MCP version mismatch? What if MCP breaks compatibility?"
- "What happens if MCP discovery returns 1000 tools (preventing scoping benefit)?"
- "How often does MCP discovery get called? Is it cached?"

---

### Q2: "Explain Service Tree ID scoping. How does it prevent hallucination?"

**Why interviewers ask:**
- Tests understanding of tool discovery and scope
- Shows if you think about LLM behaviors and constraints
- Reveals knowledge of preventing unintended tool use

**Depth indicators:**

❌ **Junior:**
"Service Tree ID groups tools so agents see only their tools."

❌ **Senior:**
"Service Tree ID scopes tools to prevent cross-agent interference."

✅ **Staff:**
"Service Tree ID is a brilliant design choice to prevent hallucination.

**The Problem (Phase 0-1):**

MCS has hardcoded tools:
```
All Time Entry Agent tools:
- GetAssignments
- GetBookings
- GetTimeEntries
- CalculateDelta
- GetM365Signals
- GenerateComments
- CreateBatch
```

LLM might hallucinate:
```
User: 'Create time entries and also get the list of all projects in the org'
LLM: 'I'll use GetProjects tool'
MCS: 'GetProjects not available' → Error
User: Confused (thought the agent could get projects)
```

Or worse:
```
LLM: 'I'll call GetDepartmentSalaries (hallucinated tool)'
MCS: Tries to call (doesn't exist)
Result: Error, confusing behavior
```

**The Solution: Service Tree ID Scoping**

Service Tree: Microsoft's internal organizational hierarchy
```
Microsoft Corporation
├── M365
├── Dynamics 365
│   ├── Project Operations
│   │   ├── Time Entry Agent
│   │   ├── Resource Scheduling
│   │   └── Capacity Planning
│   └── Sales
└── Azure
```

When Time Entry Agent calls MCS with MCP:
```
Request to MCP:
{
  serviceTree: 'D365/Project-Ops/Time-Entry-Agent'
}

MCP response:
{
  scopedTools: [
    GetAssignments,
    GetBookings,
    GetTimeEntries,
    CalculateDelta,
    GetM365Signals,
    GenerateComments,
    CreateBatch
  ]
}

All other tools (GetDepartmentSalaries, GetOrganization, etc.) hidden
```

**How it prevents hallucination:**

LLM has the knowledge:
```
GPT-4 knows about 100,000 possible tools (from training data)
```

But MCP tells MCS:
```
'Only these 7 tools exist for this agent:'
- GetAssignments
- GetBookings
- GetTimeEntries
- CalculateDelta
- GetM365Signals
- GenerateComments
- CreateBatch
```

MCS sends to LLM:
```
System prompt:
'You are a time entry agent. Available tools: [list of 7]'

LLM:
'I want to call GetProjects'
MCS: 'Tool not in your available list'
LLM: 'Oh right, my available tools are [7], GetProjects not there'
Result: LLM complies with scope
```

**Multi-tenant security benefit:**

```
Tenant A (Acme Corp):
  Service Tree: D365/Project-Ops/Time-Entry-Agent
  Tools: [Get Acme assignments, Get Acme bookings, ...]
  Custom APIs scoped to Acme org

Tenant B (Bob's Startup):
  Service Tree: D365/Project-Ops/Time-Entry-Agent
  Tools: [Get Bob assignments, Get Bob bookings, ...]
  Custom APIs scoped to Bob org

If LLM (trained on public data) tries:
  'Get Acme data from Bob's tenant'
  
MCP response: 'No Acme tools available for Bob'
LLM can't call it (tool not in scope)
```

**Implementation in Phase 2:**

```csharp
public class MCPServer {
    private readonly ServiceTreeResolver _treeResolver;
    
    public async Task<ToolListResponse> Discover(string serviceTree, string userId) {
        // Verify user has access to this service tree
        if (!await _authz.CanAccess(userId, serviceTree)) {
            throw new UnauthorizedException();
        }
        
        // Return only tools for this service tree
        var tools = _toolRegistry.GetToolsFor(serviceTree);
        
        return new ToolListResponse {
            tools = tools,  // Only 7, not 1000
            scope = serviceTree
        };
    }
}
```

**Scoping levels (nested):**

```
Level 1: Service Tree
  D365 agents see: Only D365 tools
  Azure agents see: Only Azure tools

Level 2: Product
  Project Ops agents see: Time Entry + Resource Scheduling + Capacity Planning
  Sales agents see: Opportunity Management + Account Management

Level 3: Feature
  Time Entry Agent sees: Only time entry tools
  Resource Scheduling sees: Only scheduling tools

Prevent:
- Cross-product data access (Sales can't see Project Ops)
- Cross-feature interference (Resource Scheduling can't call time entry tools)
- Hallucinated tools (LLM sees only what's configured)
```

**Metrics on hallucination reduction:**

Phase 0-1 (no scoping):
- LLM tries to call non-existent tools: ~2% of runs
- Error rate due to invalid tools: 0.5%

Phase 2 (with service tree scoping):
- LLM tries to call non-existent tools: < 0.1%
- Error rate due to invalid tools: < 0.01%

Why only 0.1% and not 0%?
- LLM might still try tools due to training data
- But MCS blocks them immediately (tool not in scope)
- Clean error: 'Tool not available'
- User understands (not a bug, a feature)

**Future benefit (Phase 3+):**

Service Tree scoping enables:
- **Cross-agent reusability**: Multiple agents can use same tools
  - HR Agent, Time Entry Agent, Resource Scheduling Agent all use GetAssignments
  - All see only Time Entry-related fields (scoped)
  
- **Tool marketplace**: Platform tools registry
  - Tool vendors register tools at specific service tree level
  - Agents discover relevant tools only
  
- **Policy enforcement**: Org-wide tool policies
  - 'No agent can call HR tools without compliance approval'
  - MCP enforces scope before LLM ever sees tool list"

**Follow-up to probe deeper:**
- "What if an agent needs a tool from a different service tree?"
- "How do you handle cross-org tool calls (tenant A needs tenant B's data)?"
- "At what scale does the tool registry become a bottleneck?"

---

### Q3: "What happens if MCP Server is down? Walk me through the fallback path."

**Why interviewers ask:**
- Tests understanding of resilience and fallback design
- Shows if you've thought through single points of failure
- Reveals operational thinking (what fails, what's acceptable)

**Depth indicators:**

❌ **Junior:**
"If MCP is down, the agent stops working."

❌ **Senior:**
"Fall back to direct Custom APIs if MCP fails."

✅ **Staff:**
"Excellent question. Fallback is critical in Phase 2.

**MCP Failure Scenarios:**

**Scenario 1: MCP Server crashes**
```
Primary path fails:
  MCS → MCP invoke → Network error (connection refused)
  Retry 1: Still down
  Timeout: 5 seconds elapsed

Fallback triggered:
  Use Direct Custom API (Phase 0-1 path)
  POST /msdyn_GetAssignments (HTTP directly)
  
Result:
  Tool succeeds (direct API works)
  User's timesheet created on time
  Alert: MCP downtime detected
  
Recovery:
  Restart MCP server
  Next call: Back to MCP path (preferred)
```

**Scenario 2: MCP Discovery is slow**
```
MCP discover call: 10 seconds timeout (too slow)
  (Normally 100ms, but under load = slow)

Result:
  Discovery timeout
  No tools returned
  Fallback: Use cached tool list from last successful discovery
  
If no cache:
  Use hardcoded fallback tool list
  Result: Same as Phase 0-1 (fewer tools, but works)
```

**Scenario 3: MCP returns invalid response**
```
MCP invoke response:
  { status: 'error', result: null }
  
MCS interprets: 'Tool failed'
Fallback: Try direct Custom API instead

Example:
  MCP GetAssignments fails → Direct API GetAssignments succeeds
  
Why both might exist:
  - MCP Server has performance regression (degraded)
  - Direct API is slower but reliable
  - Fallback ensures availability
```

**Fallback Implementation:**

```csharp
public class MCSToolInvoker {
    private readonly MCPClient _mcpClient;
    private readonly DirectAPIClient _directAPIClient;
    private readonly ILogger _logger;
    
    public async Task<ToolResult> InvokeTool(
        string toolId, 
        Dictionary<string, object> @params,
        string serviceTree,
        CancellationToken ct) {
        
        // Primary path: MCP
        try {
            _logger.Info($'Invoking tool {toolId} via MCP');
            var result = await _mcpClient.InvokeAsync(
                toolId, 
                @params,
                serviceTree,
                timeout: TimeSpan.FromSeconds(5),
                ct: ct
            );
            
            if (result.Status == ToolStatus.Success) {
                return result;
            }
            
            // MCP returned error, but tool exists
            throw new ToolExecutionException(result.Error);
        } 
        catch (TimeoutException) {
            _logger.Warn($'MCP timeout for tool {toolId}');
            // Fall through to fallback
        } 
        catch (MCPUnavailableException) {
            _logger.Warn('MCP unavailable, using fallback');
            // Fall through to fallback
        }
        
        // Fallback path: Direct API
        try {
            _logger.Info($'Falling back to direct API for tool {toolId}');
            var result = await _directAPIClient.InvokeAsync(
                toolId, 
                @params,
                timeout: TimeSpan.FromSeconds(10),  // Slightly higher timeout
                ct: ct
            );
            
            // Log fallback usage
            _telemetry.RecordFallback(
                toolId: toolId,
                reason: 'MCP unavailable',
                duration: result.Duration
            );
            
            return result;
        } 
        catch (Exception ex) {
            _logger.Error($'Both MCP and fallback failed for {toolId}: {ex}');
            throw;  // Give up, propagate error
        }
    }
}
```

**Fallback decision tree:**

```
User triggers sync
  ↓
Call MCP discovery
  ├─ Success (< 200ms): Use MCP tools ✓
  ├─ Timeout/Error: Use cached tools (if available)
  └─ No cache: Use hardcoded fallback tools ✓
  
For each tool:
  Call MCP invoke
    ├─ Success: Use result ✓
    ├─ Timeout: Try direct API ✓
    ├─ Tool error (validation): Propagate error (don't retry)
    ├─ Server error (5xx): Try direct API ✓
    └─ Network error: Try direct API ✓
    
Direct API result:
  ├─ Success: Return result ✓
  └─ Failure: Propagate error ✗
```

**Availability tradeoff:**

Phase 0-1 (no fallback):
```
Availability: 99.9% (MCS availability)
If MCS down: Agent down
```

Phase 2 (with fallback):
```
Primary path (MCP): 99.9%
Fallback path (Direct API): 99.95%
Combined: 99.9% × 99.95% + 99.9% × 99.95% ≈ 99.999%

Wait, that's not right. Let me recalculate:
If MCP fails (0.1%), can fall back: 99.95% of time works
If MCP works (99.9%), use it: works
Combined: 99.9% + (0.1% × 99.95%) ≈ 99.995%

Much better.
```

**Cost of fallback:**

Phase 0-1:
```
- 1 Custom API entry point
- 7 tool calls via MCS
- Total: 8 calls per user
```

Phase 2:
```
- 1 Custom API entry point
- 7 tool calls via MCP (primary)
- 0-7 fallback calls (if MCP fails)
  
Expected:
- 99% of time: 7 MCP calls (same as Phase 0-1)
- 1% of time: 7 fallback calls (slightly slower)
- Net: ~7-7.1 calls per user
```

**Operational insight:**

If fallback is used frequently (>5%):
```
Issue: MCP degraded or unreliable
Action: Investigate + fix MCP (don't rely on fallback)
```

Fallback is safety net, not long-term solution.

**Monitoring fallback health:**

```csharp
_telemetry.RecordFallback(
    toolId: 'GetAssignments',
    reason: 'MCP timeout',
    mcpDuration: 5000,  // timeout
    fallbackDuration: 1500,  // faster!
    success: true
);
```

Alert if:
- Fallback rate > 5%: MCP issue
- Fallback latency > direct API + 20%: Something wrong
- Pattern: Specific tools always fallback: MCP tool broken"

**Follow-up to probe deeper:**
- "How do you keep fallback code in sync with MCP code?"
- "What's the cost of maintaining two code paths?"
- "At what point do you deprecate fallback (assume MCP always works)?"

---

### Q4: "Compare MCP to traditional microservices (REST APIs). Why not just use REST?"

**Why interviewers ask:**
- Tests understanding of protocol design and LLM-specific needs
- Shows if you see beyond immediate implementation
- Reveals architectural thinking

**Depth indicators:**

❌ **Junior:**
"MCP is just a standard protocol."

❌ **Senior:**
"MCP includes service discovery, which REST doesn't."

✅ **Staff:**
"Great question. MCP is specifically designed for LLM agent patterns.

**Traditional REST (Phase 0-1 approach):**

```
GET /api/data/v9.2/msdyn_GetAssignments?userId=alice&start=2025-05-05&end=2025-05-09
POST /api/data/v9.2/msdyn_GetBookings
POST /api/data/v9.2/msdyn_CreateBatch
```

MCS knows about all 7 endpoints (hardcoded).

Pros:
- Simple (HTTP is universal)
- Cacheable (GET has standard semantics)
- Observable (status codes 200, 404, 500)

Cons:
- **No discovery**: MCS must know all endpoints ahead of time
- **No LLM scoping**: LLM could try non-existent endpoints
- **Parameter mismatch**: Each tool has different parameter schema
- **Response heterogeneity**: No standard response format
- **Tool versioning**: Hard to version individual tools

**MCP (Phase 2):**

```
Discovery:
  MCP discovery protocol → returns available tools
  
Invocation:
  MCP invoke protocol → calls tools via standardized interface
  
Tool definition:
  {
    name: 'GetAssignments',
    description: 'Get resource assignments',
    inputSchema: { /* standardized JSON schema */ },
    outputSchema: { /* standardized JSON schema */ }
  }
```

Pros:
- **Discovery**: Tools are auto-discovered
- **LLM scoping**: Only tools in discovery are available
- **Standardized**: All tools speak MCP protocol
- **Versioning**: Tool version in discovery response
- **Extensions**: Custom tools can extend the protocol

Cons:
- More complex (new protocol to learn)
- One extra layer (MCP → REST)
- Tooling less mature (REST has 25 years of maturity)

**Why MCP specifically for LLMs:**

LLMs have unique requirements:
1. **Tool exploration**: LLM needs to know what tools exist
   - REST: Hardcode list (not scalable)
   - MCP: Dynamic discovery (scalable)

2. **Parameter constraints**: LLM needs to validate inputs
   - REST: Parse documentation (error-prone)
   - MCP: Structured input schema (machine-readable)

3. **Multi-tenant isolation**: LLM must be scoped to its context
   - REST: Manual filtering (error-prone)
   - MCP: Service tree scoping (enforced)

4. **Tool composition**: LLM chains multiple tools
   - REST: Orchestrate externally (complex)
   - MCP: Standardized composition (simple)

**Comparison Table:**

| Aspect | REST | MCP |
|--------|------|-----|
| **Discovery** | Manual | Automatic |
| **Scoping** | No | Yes (service tree) |
| **Parameter validation** | Runtime | Schema-based |
| **Response format** | Tool-specific | Standardized |
| **Versioning** | URL path | Protocol native |
| **Multi-tenant** | Manual | Built-in |
| **Tool chains** | External logic | Protocol primitive |

**Real example: LLM confusion with REST**

```
LLM (trained on public docs): 'I see GetAssignments endpoint'
Query: 'What other resources can I get?'
LLM (hallucinating): 'I can call GetDepartments'
MCS: Tries to call /msdyn_GetDepartments
Response: 404 Not Found
User: Confused (LLM said it could do that)
```

With MCP:
```
LLM (given discovery response): 'Available tools are [GetAssignments, GetBookings, ...]'
Query: 'What other resources can I get?'
LLM: 'I can only call these 7 tools'
MCS: Works correctly
User: Understands LLM's capabilities
```

**Cost of MCP abstraction:**

Latency:
```
REST (Phase 0-1): 500ms per call (direct)
MCP (Phase 2): 500ms call + 50ms MCP overhead = 550ms (10% slower)
```

Worth it for:
- Hallucination prevention (reduced errors by 100x)
- Reusability (multiple agents use same tools)
- Platform alignment (Microsoft's direction)

**When REST is still better:**

If you need:
- Extreme performance (low-latency requirements)
- Simple, proven infrastructure
- No LLM integration (traditional API consumers)

Then REST is fine. MCP is overhead if you don't need it."

**Follow-up to probe deeper:**
- "Could you build MCP on top of REST, or does it require new transport?"
- "How does MCP handle authentication vs. REST API keys?"
- "What's the learning curve for teams trained on REST?"

---

### Q5: "Design how Phase 2 would scale to 500k users with MCP. What changes?"

**Why interviewers ask:**
- Tests scaling thinking with new abstraction layer
- Shows if you understand when abstractions break down
- Reveals long-term architectural thinking

**Depth indicators:**

❌ **Junior:**
"Just increase SemaphoreSlim limit."

❌ **Senior:**
"Add more MCP servers, scale horizontally."

✅ **Staff:**
"Scaling with MCP requires careful design:

**Bottlenecks at 500k users:**

Phase 0-1 (50k): 5-day runtime
Phase 2 (500k): Naive scaling = 50 days (terrible)

Bottleneck analysis:
```
Dataverse: 100 req/sec limit
500k users × 7 tools = 3.5M calls total
At 100 req/sec: 3.5M ÷ 100 = 35,000 seconds = 9.7 hours
```

If we ran overnight (10 hours), we'd just barely fit. But:
- Retries add overhead
- MCP adds ~10% latency
- Other services sharing Dataverse
- No buffer for failures

**Real bottleneck: Org-level redundancy**

Phase 0-1 problem:
```
Finance org: 100 users
All fetch same projects: 100 × 7 tools = 700 calls
Redundant: Fetch 'Project A' 100 times (same result each time)

Better: Fetch 'Project A' once, cache for org
Savings: 99 duplicate calls per project
At 1000 projects: 99,000 duplicate calls!
```

**MCP metadata approach (Phase 2 optimization):**

```
MCP server maintains: ServiceTree → Metadata
  D365/Project-Ops/Time-Entry-Agent → {
    organizations: [ acme-corp, bob-startup, ... ],
    orgs[acme-corp].projects: [ ProjectA, ProjectB, ... ],
    orgs[acme-corp].departments: [ Finance, Engineering, ... ],
    ttl: 1 hour
  }
```

When processing 100 users in Finance org:
```
User 1 (Alice):
  MCP discovery: Returns available tools (cached from MCP server)
  GetAssignments (MCP): Calls internal Custom API
    → Uses metadata cache (instant)
  ...
  
User 2 (Bob):
  MCP discovery: Cached (no call to MCP)
  GetAssignments (MCP): Uses same org metadata
    → Instant (cached from metadata, not queried)
  ...

User 100 (Carol):
  MCP discovery: Cached
  GetAssignments (MCP): Metadata still valid
    → Instant
```

Result:
```
Phase 0-1: 100 users × 7 tools × GetAssignments latency = hundreds of duplicate queries
Phase 2: 100 users × 7 tools but metadata cached = single query for org, reused 100 times
```

**Architecture scaling from 50k → 500k:**

Phase 0-1 (50k users):
```
Single Power Automate flow
  ├─ Single Custom API entry point
  ├─ Single MCS orchestrator
  └─ Single Dataverse tenant
  
Performance: 5 days
```

Phase 2 (500k users with sharding):
```
Multiple Power Automate flows (per tenant/region)
  ├─ Multiple Custom API instances (load-balanced)
  ├─ Multiple MCS orchestrators (per tenant)
  ├─ Multiple MCP servers (per service tree)
  ├─ Multiple Dataverse instances (if org is large)
  └─ Metadata cache layer (distributed Redis)

Performance: 
  - Dataverse queries: Partitioned across instances
  - Metadata cache: Reduces per-org queries by 90%
  - Time per batch: Still 4 seconds (same)
  - Concurrent batches: 5000 (500k ÷ 100 per batch)
  - Total: 5000 × 4 = 20,000 sec = 5.5 hours
```

**Key scalability improvement from Phase 2:**

Metadata caching (enabled by MCP standardization):
```
Before MCP: Each Custom API invocation is independent
  No shared metadata layer
  
With MCP: Standardized tool discovery
  MCP server caches service tree metadata
  All agents share metadata
  
Result: 10-100x reduction in redundant queries
```

**Multi-region design (Phase 2+):**

```
US East:
  MCS orchestrator (US-East)
    ├─ MCP server (US-East)
    └─ Custom APIs (US-East)

US West:
  MCS orchestrator (US-West)
    ├─ MCP server (US-West)
    └─ Custom APIs (US-West)

Metadata sync:
  MCP servers replicate metadata via service bus
  TTL handles staleness
```

**Cost optimization at 500k users:**

Phase 0-1 cost (50k):
```
- Custom API calls: 350k calls × $0.001/call = $350
- MCS orchestration: 50k runs × $0.01/run = $500
- LLM (comments): 50k × 0.0003/entry = $15
- Dataverse queries: 350k × $0.001 = $350
- Total: ~$1,215
```

Phase 2 cost (500k) without optimization:
```
- Naive scaling: 10× increase
- Cost: ~$12,150
```

Phase 2 cost (500k) with caching:
```
- Metadata cache reduces queries by 90%: -$315
- MCP layer efficiency: -$50
- Bulk operations: -$200
- Total: ~$11,585
- Savings: 5%

Still not great. Need bigger optimization.
```

Real optimization at 500k (batch at org level):
```
Instead of per-user iteration:
  - Process users in org batches (10-100 users)
  - Fetch assignments once for org
  - Filter per user (memory, instant)
  - Create entries in batch (100 at a time)

Cost breakdown:
- Queries: 500k ÷ 100 (org avg) = 5k queries
- MCS calls: 5k (not 50k)
- Total cost: ~$1,215 (SAME as 50k!)
```

This is Phase 2+ evolution (not in original Phase 2 scope)."

**Follow-up to probe deeper:**
- "How do you handle metadata staleness? What's the impact of stale cache?"
- "At what org size does per-user iteration become inefficient?"
- "How would you partition work across multiple regions?"

---

## Abstraction & Standardization Questions (8)

### Q6: "Design the MCP tool interface contract. What's required vs. optional in tool definition?"

[Tool schema design, JSON Schema for inputs/outputs, versioning, deprecation...]

### Q7: "How would you add a new tool (e.g., GetApprovals) without disrupting existing agents?"

[Tool versioning, backwards compatibility, discovery changes...]

### Q8: "Explain tool composition via MCP. Can one tool call another tool?"

[Tool chaining, recursive composition, circular dependency prevention...]

### Q9: "Design error handling in MCP. How do errors propagate from tool → MCS → LLM?"

[Error standardization, error codes, LLM-friendly error messages...]

### Q10: "Compare MCP to OpenAI's function calling protocol. Why use MCP instead?"

[Protocol comparison, LLM agility, vendor lock-in, standards...]

### Q11: "How would you expose MCP to external partners? Security & governance implications?"

[API gatekeeping, service tree isolation, compliance, monetization...]

### Q12: "Design a testing framework for MCP tools. How do you ensure contract compliance?"

[Tool contract verification, backward compatibility testing, mock implementations...]

### Q13: "At what point would you move from MCP back to direct REST? What would trigger regression?"

[Performance requirements, complexity threshold, cost-benefit analysis...]

---

## Fallback & Resilience Questions (6)

### Q14: "Design a cascade when MCP is down. Which operations degrade, which fail?"

[Graceful degradation, critical vs. optional paths, user experience...]

### Q15: "How would you test the fallback path without breaking production?"

[Canary deployments, chaos engineering, synthetic monitoring...]

### Q16: "Design a rate limiter for MCP to prevent overload. How do you tune it?"

[Rate limiting algorithms, backpressure, queue management...]

### Q17: "What's the SLA for MCP? How do you meet it (e.g., 99.9% uptime)?"

[SLA definition, monitoring, alert thresholds, incident response...]

### Q18: "Design recovery from MCP data corruption. How do you detect and fix?"

[Data validation, consistency checks, rollback strategy, audit trail...]

### Q19: "Timeout handling: MCP takes 30 seconds. Should MCS wait or fallback?"

[Timeout strategy, fallback decision logic, user experience tradeoff...]

---

## Scaling & Reusability Questions (6)

### Q20: "Design how other agents (HR, Scheduling, Capacity Planning) would reuse Time Entry Agent's tools."

[Tool discovery, scope isolation, customization, governance...]

### Q21: "At 1000s of agents, how do you prevent tool name collisions?"

[Namespacing, service tree hierarchy, tool registries, DNS-like resolution...]

### Q22: "How would you monetize MCP tools if partners want to consume them?"

[Usage metering, billing, SLA enforcement, tiered access...]

### Q23: "Design a tool marketplace (internal or external). How would discovery work at scale?"

[Centralized registry, federation, search, rating, versioning...]

### Q24: "How would you support tool customization per tenant (e.g., ACME has different fields)?"

[Extensibility, schema evolution, backwards compatibility, field masking...]

### Q25: "Design telemetry to understand which tools are most valuable. How do you measure impact?"

[Tool usage metrics, user satisfaction, cost attribution, ROI calculation...]

---

**End of Phase 2 Interview Prep**

This document covers MCP abstraction and architectural evolution for Staff+ roles. Key themes:

1. **Abstraction value** (Q1-Q5): Why MCP beats direct REST for LLM agents
2. **Tool standardization** (Q6-Q13): How to design composable, discoverable tools
3. **Resilience** (Q14-Q19): Fallback, SLA, error handling in distributed systems
4. **Scaling & reusability** (Q20-Q25): Multi-agent platforms and tool ecosystems

**Interview progression:** Start with Q1-Q2 (MCP vs. Phase 0-1) to establish foundation, then probe Q3+ based on interviewer's focus (resilience, reusability, scaling).

---

## Bonus: Principal-Level Questions (Architectural Vision)

### Q26: "Design the 5-year evolution path from Phase 0-1 → Phase 2 → Phase 3+. What's the vision?"

**Staff-level thinking:** Make Phase 2 work well.  
**Principal-level thinking:** See the long-term trajectory and position for future.

### Q27: "What would break at 10M users? Redesign the entire architecture."

**This is a redesign question, not an incremental scaling question.**

### Q28: "Should we build MCP tools or rent them from a vendor? Build vs. buy analysis."

**Strategic thinking about platform decisions.**

### Q29: "Design organizational structure to support this architecture at scale. What teams do you need?"

**Sociotechnical architecture thinking.**

### Q30: "If you could redesign Phase 0-1 from scratch with current knowledge, what would you change?"

**Retrospective design thinking, humility, evolution.**

I'll create a concise summary of remaining questions to keep the file manageable:
