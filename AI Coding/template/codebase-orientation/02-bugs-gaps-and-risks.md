# Prompt 2: Bugs, Unfinished Work, Gaps, and Risks

> <strong class="action-chip action-prompt">PROMPT TO AI</strong>
> Send one fenced prompt. AI performs every instruction inside it; do not perform its
> numbered lines manually.

> [!IMPORTANT]
> <strong class="action-chip action-verify">VERIFY AFTER AI STOPS</strong>
> Open the saved artifact and use the live-card gate.

## PROMPT TO AI - Full

After reviewing Pass 1, send unchanged.

```text
Research pass 2/3. Read `.interview/research/00-architecture-tests-and-comments.md`;
ignore the checkpoint; write only `.interview/research/01-bugs-gaps-and-risks.md`.
Do not repeat architecture or test inventories from Pass 1.
Agent-mode write boundary: edit only this research Markdown file; do not edit source,
comments, tests, config, or build files.

Never assume. Label evidence OBSERVED, INFERRED, or UNKNOWN and classify each finding
BUG, UNFINISHED, GAP, or RISK. Link every finding to verified existing files,
relative to the output. An OBSERVED BUG must link actual behavior and the violated
contract, test, schema, or caller expectation. Keep unproved failures as RISK and
missing/conflicting evidence as UNKNOWN. Plain/backticked paths, directory links,
`path :: symbol`, `file://`, and `vscode://` are not evidence.

Search first-party code for TODO/FIXME/HACK/XXX, stubs/placeholders, incomplete
branches, hardcoding, commented-out behavior, swallowed errors, ignored returns,
broad catches, unsafe casts, null/nil issues, invalid states, cleanup/leaks, contract
disagreement, races, cancellation, retries, unbounded work/storage, nondeterminism,
transaction gaps, and grounded performance risks. Use Pass 1 tests only as evidence;
do not redo test inventory or coverage analysis.

Make the artifact fast to scan:
- maximum 100 lines; begin with `30-second read` of at most six bullets;
- use one severity-ranked table; keep each finding to one row under 30 words;
- include all critical/high findings and at most five medium/low findings;
- group omitted lower findings by category, state how many were omitted, and link the
   evidence so the line cap does not hide their scope;
- no generic risk checklist, tutorials, repeated evidence, or speculative advice.

For each listed finding give ID, classification, severity, impact, evidence, related
test/contract, confidence, and the cheapest confirming check. Add short sections for
unfinished work, architecture/contract gaps, and UNKNOWN items only when nonempty.

Mermaid is optional: use at most one grounded diagram only when a cross-component
failure is clearer visually than in the table. Do not edit source/test/config/build
files. Verify links and bug proof. Final chat response (completion check):
- PATH: artifact path.
- TOP FINDINGS: highest-severity finding IDs; write NONE when no finding qualifies.
- UNCOVERED: required finding categories not searched/covered; write NONE when complete.
- UNRESOLVED: UNKNOWN items; write NONE when resolved.
- WRITE SCOPE: confirm no project file changed.
Then stop.
```

## PROMPT TO AI - Quick

Type this when external copy/paste is prohibited:

```text
P2 Agent research; do only:
1. Read 00; write 01-bugs-gaps-and-risks.md only.
2. Ground/rank BUG, UNFINISHED, GAP, RISK; prove BUG against its contract; keep
   uncertainty RISK/UNKNOWN.
3. Use <=100 lines: six-bullet summary, one table, no repeated inventory/advice.
4. Report artifact path, highest-severity IDs, unresolved UNKNOWNs, and no-project-edit
confirmation; stop; no drift.
```
