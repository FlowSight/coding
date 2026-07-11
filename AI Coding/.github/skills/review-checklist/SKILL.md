---
name: review-checklist
description: "Run a structured code review checklist before merging. Use when: review code, pre-merge check, code review, PR review, check quality, review checklist."
---

# Review Checklist

Run a multi-point quality review on changed files before merge.

## Steps

### 1. Identify changed files
Read git diff (staged or unstaged) to find modified/added files.

### 2. Run checklist per file

**All stacks:**
- [ ] No hardcoded secrets, URLs, or credentials
- [ ] No `TODO` or `FIXME` without a linked issue
- [ ] Follows naming conventions from stack instructions
- [ ] REQ-XXX traceability comment present for new logic

**C++:**
- [ ] No raw `new`/`delete`
- [ ] `#pragma once` in headers
- [ ] Compiles with `-Wall -Wextra -Werror`

**Node.js/TypeScript:**
- [ ] No `any` types
- [ ] Async functions have error handling
- [ ] No unused imports (run `npx depcheck` if applicable)

**Angular:**
- [ ] `OnPush` change detection
- [ ] Semantic HTML, ARIA attributes on interactive elements
- [ ] No `!important` in styles

**Tests:**
- [ ] New public functions have tests
- [ ] Tests are independent (no shared mutable state)
- [ ] Test names describe behavior

### 3. Output
Produce a review summary table:

| File | Pass | Issues |
|------|------|--------|
| ... | ✅/❌ | ... |

List blocking issues that must be fixed, and advisory suggestions separately.
