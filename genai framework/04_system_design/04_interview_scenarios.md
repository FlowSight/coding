# Interview Scenarios - D.E. Shaw Style Design Problems

## Scenario 1: "Design a Research Copilot for Investment Analysts"

### Prompt:
"Our analysts spend 4-6 hours per company researching SEC filings, earnings calls, and news. Design a GenAI system that reduces this to 30 minutes."

### Framework for Answering:

**1. Clarify Requirements:**
- Users: 50-200 analysts
- Data: SEC filings (10-K, 10-Q, 8-K), earnings call transcripts, news, analyst reports
- Output: Research summary, key metrics, risk factors, sentiment
- Latency: Can be minutes (not real-time trading)
- Accuracy: Very high — analysts will verify but don't want noise
- Security: Sensitive internal views must not leak between teams

**2. High-Level Architecture:**
```
┌──────────────────────────────────────────────────────────┐
│                  Research Copilot                          │
├──────────────────────────────────────────────────────────┤
│                                                           │
│  Ingestion Pipeline:                                      │
│  SEC EDGAR API → Parse (tables + text) → Chunk → Embed  │
│  News APIs → Filter relevant → Chunk → Embed            │
│  Earnings transcripts → Speaker diarize → Chunk → Embed │
│                                                           │
│  Query Pipeline:                                          │
│  Analyst question → Query decomposition →                │
│    → Parallel retrieval (filings, news, calls)           │
│    → Reranking per source type                           │
│    → Multi-document synthesis                            │
│    → Structured output (summary + citations + metrics)   │
│                                                           │
│  Agent Mode:                                             │
│  "Deep dive on NVDA" → Plan (5-8 research questions) →  │
│    → Execute each → Synthesize into full report          │
│                                                           │
└──────────────────────────────────────────────────────────┘
```

**3. Key Design Decisions:**
- **Chunking**: Structured (tables stay together, sections by header)
- **Embedding model**: Financial-specific or Voyage (long context)
- **Vector DB**: pgvector (already using Postgres) or Pinecone (managed)
- **LLM**: GPT-4o for synthesis, Claude for long-document analysis
- **Hybrid search**: Critical — ticker symbols, dates need keyword match
- **Metadata**: Filing type, company, date, section → essential filters

**4. Handling Financial Tables:**
- Parse tables as structured data (not plain text)
- Store in relational DB alongside vector store
- For numerical queries, use SQL tools (not RAG)
- Example: "What was revenue in Q3?" → SQL query, not vector search

**5. Evaluation:**
- 200+ test questions per company (factual + analytical)
- Human analyst ratings on generated reports
- Key metric: "Would you trust this enough to not re-read the filing?"
- Track time saved per analyst (business metric)

---

## Scenario 2: "Build a Real-Time Market Event Interpreter"

### Prompt:
"When a material event occurs (earnings miss, FDA approval, geopolitical event), our traders need immediate analysis of impact on relevant positions. Design this."

### Answer Framework:

**1. Requirements:**
- Latency: <30 seconds from event to analysis
- Input: News feed, market data, position data
- Output: Impact assessment, affected positions, suggested actions
- Scale: Hundreds of events/day, each analyzed against thousands of positions

**2. Architecture:**
```
Event Stream (Kafka/Kinesis)
    ↓
Event Classifier (fast model / rules)
    ↓ (material events only)
Parallel Fan-out:
    ├── Position Matcher (which positions affected?)
    ├── Historical Analogy Search (similar past events)
    └── Impact Estimator (direction + magnitude)
    ↓
Synthesis Agent (combine into brief)
    ↓
Alert System → Trader Dashboard
```

**3. Key Challenges:**
- **Speed**: Can't use full RAG pipeline (too slow)
  - Pre-compute company → position mappings
  - Pre-embed common event patterns
  - Use fastest model (GPT-4o-mini) for classification
  - GPT-4o only for final synthesis

- **Accuracy under pressure**: Wrong analysis → wrong trades
  - Confidence scoring on every output
  - Clear "LOW CONFIDENCE" flags
  - Human-in-the-loop for any suggested action

- **Context**: Event meaning depends on current market state
  - Maintain "market context" that's continuously updated
  - Include recent related events in analysis

**4. NOT using heavy RAG here — why:**
- Events are novel (not in historical docs)
- Need reasoning about implications, not retrieval
- Speed constraint incompatible with full retrieval pipeline
- Hybrid: light retrieval (cached analogies) + strong reasoning

---

## Scenario 3: "Design an Automated Report Generator"

### Prompt:
"Generate weekly portfolio performance reports that currently take analysts 8 hours each. 50 portfolios, each needs custom narrative."

### Answer:

**1. Pipeline:**
```
For each portfolio:
  1. Pull performance data (structured, from DB)
  2. Pull attribution data (what drove returns)
  3. Pull market context (relevant news/events)
  4. Generate narrative sections:
     a. Executive summary (2-3 sentences)
     b. Performance vs benchmark
     c. Top contributors/detractors
     d. Risk metrics update
     e. Outlook/action items
  5. Quality check (automated + human review)
```

**2. Why this is a CHAIN, not an AGENT:**
- Fixed structure (same sections every time)
- Predictable data inputs
- No dynamic decision-making needed
- Reliability > flexibility

**3. Technical Details:**
```python
class ReportGenerator:
    def generate(self, portfolio_id):
        # Structured data (NOT RAG - direct DB queries)
        perf_data = self.db.get_performance(portfolio_id)
        attribution = self.db.get_attribution(portfolio_id)
        
        # RAG for market context only
        context = self.rag.retrieve_market_context(
            portfolio=portfolio_id,
            holdings=perf_data.holdings,
            period="last_week"
        )
        
        # Template-guided generation
        report = self.llm.generate(
            template=REPORT_TEMPLATE,
            data={"performance": perf_data, "attribution": attribution},
            context=context,
            output_format="markdown"
        )
        
        # Automated quality checks
        checks = self.validate(report, perf_data)
        if not checks.passed:
            report = self.regenerate_with_corrections(report, checks.issues)
        
        return report
```

**4. Critical: Number Verification**
- LLMs make arithmetic errors
- All numbers in report MUST come from structured data
- Post-processing: verify every number in narrative against source data
- If mismatch detected → flag for human review

---

## Scenario 4: "Compliance Document Q&A"

### Prompt:
"Our compliance team answers 200+ questions/day about trading rules, regulations, and internal policies. Build a Q&A system."

### Key Points:

**1. This is classic RAG, but with extreme accuracy requirements:**
- Wrong compliance answer → regulatory violations → millions in fines
- Must include citations (which rule, which section)
- Must indicate confidence level
- Must escalate uncertain cases to human

**2. Design:**
```python
class ComplianceQA:
    def answer(self, question):
        # Strict retrieval from approved sources only
        docs = self.retrieve(question, sources=["regulations", "internal_policies"])
        
        # Generate with strict grounding
        answer = self.generate(
            question=question,
            context=docs,
            system="Answer ONLY from the provided context. "
                   "Cite specific sections. "
                   "If uncertain, say 'Please consult compliance team directly.'"
        )
        
        # Confidence check
        confidence = self.evaluate_confidence(answer, docs)
        
        if confidence < 0.8:
            return self.escalate_to_human(question, answer, docs)
        
        # Audit log
        self.log(question, answer, docs, confidence)
        
        return answer
```

**3. Unique Requirements:**
- Document version control (regulations change!)
- Jurisdiction-aware (rules differ by country)
- Audit trail for every answer
- Regular re-evaluation (run eval suite when rules change)

---

## Scenario 5: "System Design Quick-Fire Questions"

### "How would you reduce hallucination in a financial Q&A system?"
```
1. Strict grounding: "Answer only from context, else say I don't know"
2. Citation requirement: Every claim must reference a source
3. Confidence scoring: Only show high-confidence answers
4. Numerical verification: Cross-check LLM output against source data
5. Human-in-the-loop for low-confidence responses
6. Adversarial testing: Intentionally ask questions without answers in context
```

### "You have $10K/month budget. Design a RAG system for 10K queries/day."
```
Model: GPT-4o-mini for 80% of queries ($150/month)
       GPT-4o for complex 20% ($750/month)
Embedding: text-embedding-3-small ($30/month for 1M embeddings)
Vector DB: pgvector on existing Postgres ($0 extra)
Cache: Redis ($50/month) → 30% cache hit → saves 30% model cost
Total: ~$1000/month (well under budget)
Remaining: evaluation infra, monitoring, buffer
```

### "How do you handle a model provider outage?"
```
1. Multi-provider setup (OpenAI primary, Anthropic secondary, Azure backup)
2. Circuit breaker: After 3 failures in 1 minute, switch provider
3. Degraded mode: If all LLMs down, return cached similar answers
4. Alert on-call team
5. Queue failed requests for retry
```

### "A trader says your system gave wrong information. What do you do?"
```
1. Find the trace (LangSmith/logs) for that specific query
2. Identify: Was it retrieval failure or generation failure?
3. Check: Was the correct document in the index?
4. Check: Was the correct chunk retrieved?
5. Check: Did the LLM follow instructions correctly?
6. Add this case to eval dataset (prevent recurrence)
7. Fix root cause, verify with eval suite, deploy
8. Report back to trader with what went wrong and what's fixed
```

---

## Meta-Strategy for Any Design Question

```
1. LISTEN - What are they really asking? What's the business context?
2. CLARIFY - Users? Scale? Latency? Accuracy requirements?
3. SCOPE - What's MVP? What's v2?
4. ARCHITECTURE - Draw high-level components
5. DEEP DIVE - Pick 2-3 components to detail
6. TRADE-OFFS - Why this choice over alternatives?
7. EVALUATION - How do you know it works?
8. OPERATIONS - How do you run it in production?
9. EVOLUTION - How does it improve over time?
```

### D.E. Shaw Specific Angles to Hit:
- **Quantitative rigor**: Don't hand-wave. Give numbers (latency, cost, accuracy).
- **Risk awareness**: What can go wrong? How do you prevent/detect/recover?
- **Cost consciousness**: They're a hedge fund. Every dollar matters. Show cost optimization.
- **Data sensitivity**: Financial data requires security-first design.
- **Practical pragmatism**: Don't over-engineer. What's the simplest thing that works?
