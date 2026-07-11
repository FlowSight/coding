---
name: trace-requirements
description: "Trace requirements coverage across design, implementation, and tests. Use when: trace requirements, check coverage, requirement traceability, verify all requirements implemented, REQ coverage, feature completeness."
---

# Trace Requirements

Verify every requirement has design coverage, implementation, and test coverage.

## Steps

### 1. Load artifacts
- Read `docs/requirements/<feature>.md` to extract all REQ-XXX IDs.
- Read `docs/design/<feature>/design.md` for design references.
- Search source code for `// REQ-XXX` comments.
- Search test files for REQ-XXX references in test names or comments.

### 2. Build traceability matrix

| REQ | Description | Design | Implementation | Unit Test | Integration Test |
|-----|-------------|--------|----------------|-----------|------------------|
| REQ-001 | ... | ✅/❌ | file:line | ✅/❌ | ✅/❌ |

### 3. Report gaps
- **Missing design**: REQ exists but no design section references it.
- **Missing implementation**: REQ designed but no `// REQ-XXX` in source.
- **Missing tests**: REQ implemented but no test covers it.

### 4. Output
Save traceability report to `docs/test-reports/<feature>-traceability.md`.
Print summary: X/Y requirements fully covered, list gaps.
