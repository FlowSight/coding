# Prompt 1: Architecture, Flows, Tests, and Class/Method Comments

> <strong class="action-chip action-prompt">PROMPT TO AI</strong>
> Send one fenced prompt. AI performs every instruction inside it; do not perform its
> numbered lines manually.

> [!IMPORTANT]
> <strong class="action-chip action-verify">VERIFY AFTER AI STOPS</strong>
> Open the saved artifact and use the live-card gate.

## PROMPT TO AI - Full

Send unchanged.

```text
Research pass 1/3 across the current first-party repository, not the checkpoint.
Infer root and stack; exclude dependencies, generated/vendor code, and build output.
Write `.interview/research/00-architecture-tests-and-comments.md`.
Agent-mode write boundary: edit only this research Markdown file. Do not edit source
comments, executable code, signatures, tests, config, or build files.

Never assume. Label material claims OBSERVED, INFERRED, or UNKNOWN. Give every code,
test, and repository-defined validation claim a relative Markdown link to a verified
existing file; use line anchors when reliable. Label platform buttons/controls
PLATFORM and manual/sample flows MANUAL; do not invent commands or file links for
them. Plain/backticked paths, directory links,
`path :: symbol`, `file://`, and `vscode://` are not evidence.

Make the artifact fast to scan:
- maximum 180 lines; open with `60-second read` of at most 10 bullets;
- use compact tables/bullets; no generic tutorials, repetition, or filler;
- keep cells/bullets under 25 words; group similar modules, flows, and tests;
- cover every top-level module and primary flow, but omit trivial helpers.

Include:
1. Purpose/stack and component table: responsibility, entry points, dependencies.
2. HLD: processes, storage, queues, external systems, protocols, communication.
3. Important LLD: classes/interfaces/functions/data structures, state, contracts.
4. One-row summary of every primary flow: trigger, ordered components, data changes,
   errors, persistence/events, result/side effect.
5. Grounded validation methods: commands when defined, platform controls, and manual/
   sample flows; suites mapped to components/flows; assertions actually proved;
   focused/broad checks; top five missing or weak coverage areas.
6. UNKNOWN/conflicting evidence.

Audit the existing comments on every critical or large first-party class and method.
Critical means it drives a primary flow, business rule, state transition, persistence,
concurrency, or complex errors. Large means its branching or multi-step logic is not
obvious. Classify each as ADEQUATE, NEEDS_ENHANCEMENT, or MISSING. For the latter two,
write a proposed concise language-idiomatic comment in the artifact; do not apply it.
Class proposals explain responsibility, lifecycle, collaborators, and invariants.
Method proposals explain purpose, inputs/outputs, key steps, state/side effects/errors,
and non-obvious invariants. Avoid trivial or line-by-line narration. Record:
`Symbol link | Why the class/method is critical or large | Comment status | Proposed comment or why adequate`.

Use at most three grounded Mermaid diagrams: one HLD, one important LLD, and sequence
diagrams for at most two distinct primary flows. Summarize remaining flows in the
table. Below each diagram, link every code component; label non-code actors EXTERNAL.

Before finishing, verify module/flow/test/comment coverage, links, diagrams, and
`git diff`; only `.interview/research/00-architecture-tests-and-comments.md` may
change. Final chat response (completion check, not artifact content):
- PATH: artifact path.
- UNCOVERED: top-level modules, primary flows, or test suites; write NONE when complete.
- UNRESOLVED: UNKNOWN items; write NONE when resolved.
- WRITE SCOPE: confirm no project file changed.
Then stop.
```

## PROMPT TO AI - Quick

Type this when external copy/paste is prohibited:

```text
P1 Agent research; do only:
1. Output only: 00-architecture-tests-and-comments.md; no project edits.
2. Ground HLD/LLD, components, flows, tests, coverage.
3. Within 180 lines/three Mermaid diagrams, audit existing comments on critical or
   large classes/methods. Classify each comment ADEQUATE, NEEDS_ENHANCEMENT, or MISSING;
   propose fixes in the artifact only.
4. Report artifact path, uncovered modules/flows/suites or NONE, unresolved UNKNOWNs,
   and no-project-edit confirmation; stop; no drift.
```
