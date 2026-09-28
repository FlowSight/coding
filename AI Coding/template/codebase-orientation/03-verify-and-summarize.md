# Prompt 3: Verify and Summarize Orientation

> <strong class="action-chip action-prompt">PROMPT TO AI</strong>
> Send one fenced prompt. AI performs every instruction inside it; do not perform its
> numbered lines manually.

> [!IMPORTANT]
> <strong class="action-chip action-verify">VERIFY AFTER AI STOPS</strong>
> Open the saved artifact and use the live-card gate.

## PROMPT TO AI - Full

After reviewing passes 1-2, send unchanged.

```text
Research pass 3/3. Read `00-architecture-tests-and-comments.md` and
`01-bugs-gaps-and-risks.md`; ignore the checkpoint. Verify them against the repository,
repair unsupported claims in those artifacts, and write
`.interview/research/02-orientation-summary.md`. Do not edit source/test/config/build
files or source comments. Agent-mode edits stay inside `.interview/research/`.

Resolve every relative Markdown link and require an existing file target. Label
material claims OBSERVED, INFERRED, or UNKNOWN and link each code claim to evidence.
Cross-check module/critical-class/method completeness; flow participants; validation
methods and test assertions; BUG behavior plus violated contract; contradictions;
comment audit; and existing diagram grounding. Downgrade unsupported findings to
RISK/UNKNOWN.

Make summary 02 an interview dashboard, not a restatement:
- maximum 100 lines; start with `60-second repository briefing` of <=10 bullets;
- use compact tables and phrases; cells/bullets <=25 words; no prose essay;
- link to detailed artifact sections instead of duplicating their evidence;
- include purpose/stack, component index, one-row primary-flow index, key LLD and
  critical symbols, validation methods, strongest coverage and top five gaps,
  critical/high findings, contracts/invariants to preserve, and UNKNOWN items;
- include one grounded final architecture/flow Mermaid, <=12 nodes; label non-code
  actors EXTERNAL. No other diagram is needed.

Gate PASS requires all first-party modules and primary flows considered; all material
claims linked to verified files; repository-defined commands linked, platform/manual
methods labeled without invented links, and required diagrams grounded; no broken
links; no non-research file changes; complete comment audit; no duplicate/slop sections;
and contradictions corrected or UNKNOWN. Final chat response:
- PATHS: all three research artifacts.
- GATE: PASS or FAIL.
- UNRESOLVED: broken links, contradictions, and UNKNOWN items; write NONE when resolved.
- SIZE: summary line count, reported only to confirm the 100-line cap.
Then stop.
```

## PROMPT TO AI - Quick

Type this when external copy/paste is prohibited:

```text
P3 Agent research; do only:
1. Verify 00-01, evidence, diagrams, and zero project-file changes.
2. Repair research artifacts only.
3. Write <=100-line 02-orientation-summary.md: 10-bullet briefing, compact system,
   tests, findings, contracts, unknowns; one grounded <=12-node diagram.
4. Report paths, gate PASS/FAIL, unresolved links/contradictions/UNKNOWNs or NONE, and
summary line count for the cap; stop; no drift.
```
