# Bloomberg — System Design Round

**Date**: July 8, 2026  
**Role**: Senior Software Engineer  
**Duration**: ~45 min  
**Format**: System design — redesign an existing trade data system  
**Status**: TBD  
**Confidence**: TBD  

---

## Problem: Trade Information System Redesign

Unconventional format — presented an existing system diagram and asked to identify problems and propose a redesign.

### Existing System
- Stock exchanges on one end
- A few relay servers receiving data from each stock exchange
- Relay servers forwarding information to different downstream Bloomberg processors

### Problems Identified (Discussed ~15 min)
1. **Network bandwidth waste**: Relay servers send the same data to all Bloomberg processors — duplicated traffic across the network
2. **IO exhaustion**: UDP is an IO-bound process — memory and IO on relay servers can be exhausted under load
3. **Server crashes**: Relay servers are prone to crashing under high throughput
4. **Out-of-order updates**: No ordering guarantee with UDP — out-of-order updates affect Bloomberg processors and end-user experience
5. **Lost updates**: If Bloomberg processors crash, there is no way to re-read from a particular offset (unlike Kafka) — updates are permanently lost
6. **Storage not suited for time-series data**: The DBs used by Bloomberg processors are not TimescaleDB or time-series optimized — not scalable for time-series pattern data
7. **Processor crashes from traffic spikes**: Bloomberg processors can crash when there's a spike from a particular trade or symbol (no backpressure/buffering)

---

## My Approach

### 0. Clarifying Questions (Blocked)
- Asked: "What are the requirements, expectations, and goals the original system was designed for?"
- Interviewer response: "That's really out of discussion scope. Maybe you can talk with the architect over a coffee, but that's not the importance here. We want to design it from scratch and make it better in every way."
- **Impact**: Could not establish clear functional/non-functional requirements (latency, throughput, consistency guarantees) — had to infer from context
- This made it difficult to set expectations on what the redesign should optimize for

### 1. Ingestion Layer
- Stock updates arrive via **SSE (Server-Sent Events)** or **WebSocket** from exchanges
- A consumer service receives these streams and immediately dumps into a message queue
- Decouples ingestion from processing

### 2. Message Queue — Kafka (Initial Proposal)
- **Topic**: one per exchange
- **Partition**: by stock symbol
- Reasoning: natural ordering guarantee per symbol, parallelism across symbols
- **Consumer servers**: horizontally scaled, each server reads from specific partitions across multiple topics
  - Example: one consumer server handles Apple stock → reads partition 1 from topic 1 (exchange 1), partition 5 from topic 2 (exchange 2), partition 3 from topic 3 (exchange 3)
  - Each server is **responsible for a set of stock symbols/partitions** across all exchanges
  - Scales by adding more consumer servers to own more partition sets

### 3. Interviewer Pushback — Kafka Consumer Constraint
- Interviewer pushed back: "Why can only one consumer read from a partition?"
- Explained that Kafka's design assigns each partition to exactly one consumer within a consumer group
- Interviewer pushed further: "Why did you make that assumption?"
- **Pivoted to SQS**: multiple queues representing multiple stock exchanges, allowing multiple consumers per queue without the single-consumer-per-partition constraint

**Note on ordering**: Ordering is NOT handled at the queue layer — it's handled at the storage/CDC layer:
- Updates can arrive out of order from either Kafka or SQS
- When CDC writes to TimescaleDB, out-of-order updates are inserted into the correct time position within a chunk
- If a late update arrives after a chunk has already been written, the entire chunk is rewritten to include it
- This means the queue choice (Kafka vs SQS) is not about ordering — ordering is a DB-layer concern

### 4. Storage Architecture
- Proposed an **audit table** as the single source of truth — every raw update goes in
- Audit table stored in **Cassandra**
  - Write-optimized (LSM tree, SSTables)
  - Binary search within SSTables for reads
  - High write throughput for streaming trade data
  - Distributed, no single point of failure

### 5. CDC (Change Data Capture) from Audit Table
- From the Cassandra audit table, use CDC to populate two downstream stores:
  1. **Ticker/Price Updates** → TimescaleDB
  2. **Trade Updates** → TimescaleDB

### 6. TimescaleDB Reasoning
- Columnar representation — efficient for time-series queries on specific fields
- Delta encoding — compresses sequential price data efficiently
- Hypertable partitioning by time — fast range queries on trade history
- Optimized for the read patterns of financial data (time-range queries, aggregations)

### 7. Cassandra Deep Dive (Discussed)
- Write path: commit log → memtable → SSTable flush
- Read path: bloom filter → partition index → SSTable binary search
- Compaction strategies for managing SSTable proliferation
- Distributed hash ring for partition placement

### 8. User Query Path — Initial Proposal
- Interviewer: "How will the user get the update?"
- Proposed: users query from TimescaleDB directly — supports ~100K queries
- Interviewer pushback: "No, but how is real-time query served?"
- This requirement was **not stated in the original problem** — acknowledged and adapted

### 9. Real-Time Push — SSE + Redis Pub/Sub
- Added a **Query Service** that establishes SSE connections with users
- Flow on first connect:
  1. User connects via SSE to Query Service
  2. Query Service creates an in-memory map: `connectionId → user`
  3. User expresses interest in specific stocks (subscription)
- Flow on stock update:
  1. Relay server puts update into the queue
  2. Worker consumes the update and publishes to **Redis Pub/Sub**
  3. Redis Pub/Sub topic = stock symbol
  4. SSE servers (Query Service instances) are subscribers on Redis Pub/Sub
  5. On receiving a pub/sub message, SSE server checks which connected users are subscribed to that stock
  6. Pushes the update to those users via their SSE connection

### 10. Interviewer Pushback — Why Redis Pub/Sub over Kafka?
- Question: "Why not use Kafka instead of Redis Pub/Sub?"
- My answer:
  - Kafka requires sequential offset processing — if an update arrives, it must wait for all preceding offsets to be processed → introduces delay, not truly real-time/instantaneous
  - Redis Pub/Sub is fire-and-forget, no offset tracking → near-zero latency for hot path
  - We already have persistence in Cassandra/TimescaleDB — so even if Redis crashes, historical/cold data is recoverable from the tables
  - Redis Pub/Sub serves the **hot path** (real-time); TimescaleDB serves the **cold path** (historical queries)

---

## Key Design Decisions

| Decision | Choice | Reasoning |
|----------|--------|-----------|
| Ingestion | SSE/WebSocket consumer → Queue | Decouple exchange streams from processing |
| Queue (initial) | Kafka, topic=exchange, partition=symbol | Ordering per symbol, parallelism |
| Queue (revised) | SQS, queue per exchange | Multiple consumers, no partition lock-in |
| Raw storage | Cassandra audit table | Write-optimized, distributed, high throughput |
| Derived storage | TimescaleDB (price + trade tables) | Columnar, delta encoding, time-series optimized |
| Data flow | CDC from audit → derived tables | Decoupled, eventual consistency, replayable |
| Real-time push | SSE + Redis Pub/Sub | Fire-and-forget, no offset delay, near-zero latency |
| Hot vs Cold path | Redis Pub/Sub (hot) / TimescaleDB (cold) | Real-time vs historical separation |

---

## Interviewer Pushback & Handling

| Pushback | My Response |
|----------|-------------|
| "Why can only one consumer read from a Kafka partition?" | Explained Kafka's consumer group model — one partition → one consumer per group |
| "Why did you make that assumption?" | Pivoted to SQS which allows multiple consumers per queue without that constraint |
| "How is real-time query served?" | Added SSE-based Query Service with Redis Pub/Sub for instant push |
| "Why Redis Pub/Sub over Kafka for real-time?" | Kafka has offset ordering delay; Redis is fire-and-forget with near-zero latency; persistence already handled by Cassandra/TimescaleDB |

---

## Reflection

- **What went well**:
  - Identified problems with existing system from diagram
  - Clean separation: ingestion → audit → CDC → derived stores
  - Good technology reasoning (Cassandra write path, TimescaleDB columnar/delta encoding)
  - Handled pivot from Kafka to SQS without losing composure

- **What could have been stronger**:
  - **[PRIMARY FAILURE]** Did not narrate the reasoning for why pivoting from Kafka to SQS was valid — the CDC/DB-layer ordering logic was in my head but never communicated. Interviewer had no way to know the pivot was deliberate and well-reasoned.
  - When interviewer blocked requirements gathering, should have stated assumptions explicitly ("I'll assume X, Y, Z") rather than proceeding without a clear contract — this led to the real-time requirement surfacing late as a surprise
  - For a financial data company, should have defaulted to real-time as a core assumption even when requirements were withheld

---

## Lessons Learned

1. **[PRIMARY] Narrate your reasoning chain — always explain the "why" behind a pivot**
   - The right response when pivoting from Kafka to SQS:
   > "Actually, I don't need ordering at the queue layer. My CDC process handles out-of-order writes when inserting into TimescaleDB — it places updates in the correct time chunk, and rewrites chunks for late arrivals. So the queue only needs to be durable and parallelizable — SQS gives me that with more consumer flexibility."
   - This single sentence would have turned a perceived weakness into a strength: shows ability to re-evaluate, reason about where guarantees belong in the stack, and make deliberate trade-offs
   - **Rule**: If you change direction in an interview, explicitly bridge the old decision to the new one with reasoning. Silent pivots look like folding under pressure.

2. **Carry your problem analysis INTO your solution**
   - Identified "out-of-order updates" as problem #4 but didn't explicitly address it in the architecture
   - Every problem you identify should map to a specific design decision
   - Treat your problem list as a checklist — for each one, point to where your design solves it
   - **Rule**: After presenting your design, walk back through your problem list: "Problem 1 is solved by X, problem 2 by Y..."

3. **Domain defaults must be muscle memory, not real-time reasoning**
   - For financial/trading systems: real-time delivery, ordering, exactly-once semantics, and backpressure are table stakes — not "nice to haves"
   - These should be reflexive, pre-loaded before you walk in
   - You shouldn't need a requirements discussion to know Bloomberg cares about real-time
   - **Rule**: Before any domain-specific interview, write down the 3-4 non-negotiable constraints for that domain. Internalize them.

4. **"Blocked on requirements" ≠ "skip requirements"**
   - Preparation said to state requirements upfront. Interviewer blocked it. Moved on without them — wrong move.
   - The right response when blocked:
   > "OK, since the architect isn't available, I'll design with these assumptions: (1) real-time delivery to end users, (2) ordering guarantees per symbol, (3) zero data loss, (4) horizontal scalability. I'll call these out as I go."
   - This shows you *know* what matters even when nobody tells you
   - **Rule**: If requirements are blocked, state them yourself as assumptions. Never proceed in a vacuum.

5. **Preparation → Execution gap is a repetition problem**
   - Knew the right moves (state requirements, defend decisions) but didn't execute under pressure
   - This isn't a knowledge gap — it's a reps gap
   - Need mock interviews where someone actively pushes back and blocks you
   - The discomfort of being blocked needs to be familiar so you respond with structure rather than compliance
   - **Rule**: Practice being uncomfortable. Seek mock partners who challenge and block.

6. **When presented with an existing system**: spend time articulating the problems clearly before jumping to redesign (did this well — 15 min)

7. **Unconventional formats**: practice redesign/critique problems, not just greenfield design

---

## Pipeline Status

| Round | Type | Status |
|-------|------|--------|
| System Design | Redesign existing trade system | ❌ Rejected |
