---
name: project-config
description: "Project configuration for the orchestrator. Defines project name, tech stack, directory layout, and input sources. Created once per project, referenced by all agents."
---

# Project Configuration

Each project must have a `.github/project-config.json` at its root before the orchestrator begins work.

## Schema

```json
{
  "projectName": "my-feature",
  "techStack": {
    "backend": "cpp|node|both",
    "frontend": "angular|none",
    "testFramework": {
      "cpp": "gtest",
      "node": "jest|vitest",
      "angular": "jasmine|jest",
      "e2e": "playwright|cypress|none"
    }
  },
  "directories": {
    "requirements": "docs/requirements",
    "design": "docs/design",
    "testReports": "docs/test-reports",
    "source": {
      "cpp": "src/cpp",
      "node": "src",
      "angular": "src/app"
    }
  },
  "inputSources": {
    "type": "pdf|url|local|manual",
    "path": "inputs/requirement.pdf",
    "notes": "Optional context about the input"
  },
  "conventions": {
    "requirementPrefix": "REQ",
    "branchNaming": "feature/<projectName>-<short-desc>",
    "commitPrefix": "feat(<projectName>):"
  }
}
```

## Fields

| Field | Required | Description |
|-------|----------|-------------|
| `projectName` | Yes | Unique identifier, used for artifact paths and state tracking |
| `techStack` | Yes | Which layers are in scope |
| `directories` | Yes | Where artifacts go. User can override defaults |
| `inputSources.type` | Yes | How requirements arrive: `pdf` (attached file), `url` (web link), `local` (file on disk), `manual` (user types them) |
| `inputSources.path` | If type != manual | Path or URL to the requirement source |
| `conventions` | No | Project-specific naming rules |

## Creation

The orchestrator creates this file interactively on first invocation if it doesn't exist.
