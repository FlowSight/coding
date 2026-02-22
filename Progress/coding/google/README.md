# Google L5 Prep — Tooling Guide

Quick reference for the tracking tools set up in this workspace.

---

## 1. Adding a Tracking Header (Snippet)

When you open or create a `.cpp` file, type **`track`** and press `Tab`. It expands to:

```cpp
// Severity: Sev0          ← Tab to pick Sev0 / Sev1 / Sev2
// Date: 19Feb26           ← Auto-filled
// LC: 269                 ← Tab to type LC number
// Where I failed:         ← Tab to describe
// Pattern: Graph          ← Tab to type pattern/topic
// Notes: ...              ← Tab to add notes
```

There's also a compact version: type **`qtrack`** or **`qt`** and press `Tab`.

---

## 2. Syncing to the CSV Tracker

After filling in the snippet and saving the file:

### Option A: Keyboard Shortcut (recommended)
Press **`Cmd+Shift+T`** while in any `.cpp` file.

### Option B: Command Palette
`Cmd+Shift+P` → **Run Task** → **Sync to Tracker**

### Option C: Terminal
```bash
./tools/tracking/track_sync.sh "path/to/file.cpp"
```

### What it does:
- Reads `// LC:`, `// Pattern:`, `// Notes:` from the file header
- Finds the LC# in `question_tracker.csv`:
  - **Found** → marks as `Redo`, updates Date, Tag, Notes
  - **Not found** → creates a new row marked `Solved`
- Prints a summary with overall stats

---

## 3. Creating a New Problem File

```bash
./tools/tracking/newproblem.sh <filename.cpp> [directory]

# Examples:
./tools/tracking/newproblem.sh two_sum.cpp blind75/
./tools/tracking/newproblem.sh cracking_safe.cpp "company wise/google/"
```

Creates a `.cpp` file with a clean header template and opens it in VS Code.

---

## Files Overview

| File | Purpose |
|------|---------|
| `Progress/coding/google/google_prep_tracker.md` | Master prep plan, goals, phase tracker |
| `Progress/coding/google/question_tracker.csv` | Problem-level tracking (Problem, LC#, Status, Date, Tag, Notes) |
| `tools/tracking/track_sync.sh` | Reads file header → syncs to CSV (no prompts) |
| `tools/tracking/newproblem.sh` | Creates new `.cpp` with header template |
| `.vscode/cpp.code-snippets` | `track` and `qtrack` snippets |
| `.vscode/tasks.json` | VS Code task for "Sync to Tracker" |

---

## Typical Workflow

```
1. ./tools/tracking/newproblem.sh lfu_cache.cpp "company wise/google/"
2. Solve the problem
3. Type `track` at the top → fill in Sev, LC#, Pattern, Notes
4. Save (Cmd+S)
5. Sync (Cmd+Shift+T)
6. CSV updated ✅
```

For existing files without `// LC:` — just add the line manually (e.g. `// LC: 960`) then `Cmd+Shift+T`.
