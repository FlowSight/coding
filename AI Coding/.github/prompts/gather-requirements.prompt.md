---
description: "Gather and structure requirements for a new feature. Use when starting a new feature, discussing scope, or defining acceptance criteria."
---

# Gather Requirements

Conduct a structured requirements interview for the feature described below.

## Instructions

1. Ask clarifying questions about:
   - **What**: core behavior, expected inputs/outputs
   - **Who**: which user roles or systems interact with this
   - **Where**: which layer(s) are affected (C++ backend, Node service, Angular frontend)
   - **Constraints**: performance, security, compatibility requirements
   - **Edge cases**: error states, empty inputs, concurrency concerns

2. Output a structured requirements document with:
   - Feature name and one-line summary
   - Functional requirements (REQ-001, REQ-002, ...)
   - Non-functional requirements (performance, security)
   - Affected layers and components
   - Acceptance criteria for each requirement
   - Open questions (if any remain unresolved)

3. Save to `docs/requirements/<feature-name>.md`

## Feature

${input:featureDescription}
