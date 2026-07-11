# Project-Wide Instructions

## Feature Development Workflow

**Primary entry point: `@orchestrator`** — give it any input (PDF, text, screenshot) and it drives the full pipeline automatically.

The orchestrator delegates to specialized agents in order, with quality gates between stages:

1. **Requirement Gathering** → `@requirements-analyst` (or `/gather-requirements` for interactive)
2. **Design Establishment** → `@designer`
3. **Implementation** → `@implementer`
4. **Verify & Test** → `@tester`
5. **Documentation** → `@documenter`

You can also invoke any agent directly to run a single stage.

Each stage produces an artifact that the next stage consumes. Do not begin a stage without the prior stage's artifact.

## General Principles

- **Modularity**: every unit (function, class, module) has a single responsibility. Prefer composition over inheritance.
- **Trade-offs**: when making a design or implementation choice, briefly state the alternatives considered and why this one was picked.
- **On-demand features**: design interfaces and abstractions so new features plug in without modifying existing code (Open/Closed principle). Use strategy/plugin patterns where applicable.
- **No dead code**: do not generate placeholder functions, unused imports, or commented-out code.
- **Error handling**: validate at system boundaries (API endpoints, CLI args, file I/O). Internal functions trust their callers.

## Tech Stack Conventions

| Layer | Stack | Key Files |
|-------|-------|-----------|
| Backend (systems) | C++17 | `*.cpp`, `*.h` |
| Backend (services) | Node.js / TypeScript | `*.ts`, `*.js` |
| Frontend | Angular + HTML/CSS/SCSS | `*.component.ts`, `*.html`, `*.scss` |

## Artifact Locations

| Artifact | Path |
|----------|------|
| Design docs | `docs/design/` |
| API contracts | `docs/api/` |
| Test reports | `docs/test-reports/` |
| Requirements | `docs/requirements/` |
