# Time Entry Agent — Phase 2: MCP Server Extension

## What Changed

Phase 1 used Custom APIs (direct HTTP endpoints in Dataverse) as tools. In Phase 2, we extended the agent to use **MCP (Model Context Protocol) servers** as an abstraction layer between MCS and the underlying services.

Two MCP servers were introduced:
- **Dataverse MCP Server** — wraps Custom APIs + CRUD operations on Dataverse tables
- **M365 MCP Server** — wraps Teams meeting info and mail info from Graph API

```
Phase 1:  MCS ──HTTP──▶ Custom API (Dataverse)
          MCS ──HTTP──▶ Graph API (M365)

Phase 2:  MCS ──MCP──▶ DV MCP Server ──▶ Custom API / CRUD
          MCS ──MCP──▶ M365 MCP Server ──▶ Teams / Mail
```

## Why MCP

- **Standardized tool contract** — MCP provides a uniform protocol for tool discovery, invocation, and response. MCS can discover available tools dynamically instead of hardcoded HTTP endpoints.
- **Reusability** — MCP servers can be shared across multiple agents/copilots, not just Time Agent.
- **Platform direction** — Microsoft's broader strategy moving toward MCP as the standard for agent-tool communication.

## Architecture — Phase 2

```
┌──────────────────────────────────────────────────────────────────────────────┐
│  Regional Deployment                                                          │
│                                                                               │
│  ┌─────────────────────┐     S2S token     ┌──────────────────┐              │
│  │  Power Automate      │◀────────────────▶│  BAP RP          │              │
│  │  (Scheduled Flow)    │                   │  (Impersonation) │              │
│  │  FOR EACH user:      │                   └──────────────────┘              │
│  │   call MCS + corrID  │                                                     │
│  └──────────┬───────────┘                                                     │
│             │ Native MCS connector (HTTP)                                     │
│             ▼                                                                 │
│  ┌────────────────────────────────────────────────────────────────┐           │
│  │  MCS (Microsoft Copilot Studio) — Orchestrator only             │           │
│  │  No embedded LLM. All LLM inference routed via Custom API.      │           │
│  │                                                                  │           │
│  │  ┌──────────────────────────────────────┐                       │           │
│  │  │ Knowledge:                           │                       │           │
│  │  │  - MCP tool list (scoped, not global)│                       │           │
│  │  │  - pipeline steps + fallback rules   │                       │           │
│  │  └──────────────────────────────────────┘                       │           │
│  │  Instructions: "Only use tools listed in Knowledge"             │           │
│  │  Guardrails: If MCP fails → fall back to direct Custom API      │           │
│  └──────┬─────────────────┬───────────────────────┐               │           │
│         │                 │                       │ FALLBACK path │           │
│         │ Tool calls      │ ALL LLM inference     │ (direct HTTP) │           │
│         │ (MCP primary)   │ (MCS→CAPI→Azure Model)▼               │           │
│         │                 │                ┌─────────────────┐     │           │
│         │                 │                │ Direct Custom   │     │           │
│         │                 ▼                │ APIs (Phase 1   │     │           │
│         │  ┌────────────────────────┐      │ endpoints)      │     │           │
│         │  │  Azure Model Deployment│      │ Same C#/.NET    │     │           │
│         │  │  (GPT, low temp)       │      │ underneath      │     │           │
│         │  │                        │      └────────┬────────┘     │           │
│         │  │  Called for:           │               │              │           │
│         │  │  - Orchestration       │               │              │           │
│         │  │    (tool selection,    │               │              │           │
│         │  │     result interpret)  │               │              │           │
│         │  │  - Comment generation  │               │              │           │
│         │  └────────────────────────┘               │              │           │
│         │                                           │              │           │
│         │ PRIMARY path (MCP)                        │              │           │
│         ▼                                           │              │           │
│  ┌──────────────────────────────────────┐  ┌─────────────────┐    │           │
│  │  MCP Layer                            │  │ Direct Custom   │    │           │
│  │                                       │  │ APIs (Phase 1   │    │           │
│  │  Identity-based tool scoping:         │  │ endpoints)      │    │           │
│  │  Service Tree ID                      │  │ Same C#/.NET    │    │           │
│  │  (D365 → Proj Ops → Time Agent)      │  │ underneath      │    │           │
│  │  → MCP returns ONLY our tools         │  └────────┬────────┘    │           │
│  │                                       │           │             │           │
│  │  ┌────────────────┐  ┌─────────────┐ │           │             │           │
│  │  │ DV MCP Server  │  │ M365 MCP    │ │           │             │           │
│  │  │ - Custom APIs  │  │ Server      │ │           │             │           │
│  │  │ - CRUD ops     │  │ - Meetings  │ │           │             │           │
│  │  │ - Entity sets  │  │ - Mail      │ │           │             │           │
│  │  └───────┬────────┘  └──────┬──────┘ │           │             │           │
│  └──────────┼──────────────────┼────────┘           │             │           │
│             │                  │                     │             │           │
│             ▼                  ▼                     │             │           │
│  ┌───────────────────┐  ┌──────────────────┐        │             │           │
│  │  Dataverse         │  │  M365 Graph API  │◀───────┘             │           │
│  │  - Business tables │  └──────────────────┘                      │           │
│  │  - Agent Metadata  │                                            │           │
│  │  - OCC (ETags)     │                                            │           │
│  └───────────────────┘                                             │           │
│                                                                               │
└──────────────────────────────────────────────────────────────────────────────┘

Key changes from Phase 1:
- MCP layer sits between MCS and backend services (wrapper, not rewrite)
- Service Tree ID scoping prevents tool explosion hallucination
- Fallback path to direct Custom APIs if MCP fails
- Same underlying Custom APIs, Agent Metadata, OCC, impersonation — unchanged
```

## MCS Changes

| Component | What changed |
|-----------|-------------|
| **Knowledge** | Added MCP server contract details (available tools, input/output schemas). Added retry instructions. Added fallback: "if MCP fails, fall back to direct Custom API tools." |
| **Instructions** | Updated to reference MCP tools instead of direct HTTP endpoints |
| **Tools registered** | MCP server endpoints replaced individual Custom API registrations |

## Challenges

### 1. MCP Server Gaps — Co-Development Required
Certain Dataverse entity operations (entityset support) weren't supported by the MCP server out of the box. We had to **co-develop** with the MCP server team to add support for our specific Custom APIs and entity types. The existing Custom APIs remained the same underneath — MCP was a wrapper, not a rewrite.

### 2. Hallucination from Tool Explosion
**Problem**: MCP servers expose tools globally — not just Time Agent's tools, but all registered tools across the platform. When MCS saw a much larger tool catalog, it started **hallucinating tool selections** — picking irrelevant global tools instead of the Time Agent-specific ones.

**Why**: In Phase 1, MCS had exactly 8 (later 2) tools registered. In Phase 2, MCP exposed dozens of global tools. The LLM's tool selection degraded with the larger search space.

**Mitigation approaches**:
- Tightened Knowledge to explicitly list which MCP tools to use and in what order
- Added guardrails in Instructions: "Only use tools listed in Knowledge. Do not invoke any tool not explicitly mentioned."
- Fallback: If MCP tool invocation fails or returns unexpected results, fall back to direct Custom API call
- **Identity-based tool scoping (feature request to MCP team)**: We requested a feature from the MCP team to enable **identity-based tool filtering**. The Time Entry Agent's **Service Tree ID** (a child service under Dynamics 365 → Project Operations hierarchy) was registered with the MCP server. When our agent identified by this Service Tree ID called MCP, the server returned **only the subset of tools available to that identity** — not the full global catalog. This drastically reduced the tool list MCS had to reason over, cutting context size and eliminating hallucinated tool selections.

### 3. Fallback Strategy
Since MCP was newer and less battle-tested than direct Custom APIs, we built a **fallback path**:
- MCS first attempts tool call via MCP server
- If MCP call fails (timeout, unsupported operation, unexpected response), MCS retries via direct Custom API
- Retry logic documented in MCS Knowledge so the LLM knows when and how to fall back

## What Stayed the Same
- Power Automate trigger and user iteration logic — unchanged
- Custom APIs (C#/.NET) — unchanged, MCP wraps them
- S2S impersonation flow — unchanged
- Agent Metadata table — unchanged
- OCC strategy — unchanged
- Correlation ID framework — unchanged

## Key Takeaway
MCP added a clean abstraction layer but introduced tool discovery noise. The main engineering effort was **not the MCP integration itself** — it was managing the LLM's behavior when the tool catalog grew. The fix was constraining MCS's knowledge and instructions more tightly, essentially trading flexibility for reliability.