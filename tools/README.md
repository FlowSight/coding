# Tools

Utility scripts organized by function. All scripts auto-resolve the workspace root, so they work correctly regardless of your current working directory.

---

## Directory Structure

```
tools/
├── build/                  # Compilation & execution utilities
│   └── build_and_run.sh    # Compile and run a C++ file with standard flags
├── tracking/               # Problem tracking & scaffolding
│   ├── track.sh            # Manual tracker: tag file + update CSV
│   ├── track_sync.sh       # Auto-sync: reads file header → updates CSV
│   └── newproblem.sh       # Scaffold a new .cpp with header template
└── README.md               # This file
```

## Adding New Tools

Place new scripts in the appropriate subdirectory, or create a new one:

| Category | Directory | Purpose |
|----------|-----------|---------|
| Build | `tools/build/` | Compilation, linking, execution |
| Tracking | `tools/tracking/` | Progress tracking, CSV sync, scaffolding |
| Analysis | `tools/analysis/` | Stats, reports, visualizations *(future)* |
| Testing | `tools/testing/` | Test runners, validators *(future)* |

### Convention for new scripts

1. Use `SCRIPT_DIR` / `ROOT_DIR` pattern for portable path resolution:
   ```bash
   SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
   ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
   ```
2. Accept file paths relative to workspace root.
3. Include a usage banner when called with no args.
4. Make executable: `chmod +x tools/<category>/your_script.sh`

---

## Quick Reference

### Build & Run
```bash
# Preferred (quick shortcuts at repo root):
./run array/two_sum.cpp
make r FILE=array/two_sum.cpp

# Direct script:
./tools/build/build_and_run.sh array/two_sum.cpp
```

### Tracking
```bash
# Create a new problem file
./tools/tracking/newproblem.sh lfu_cache.cpp "company wise/google/"

# Manual track (with args)
./tools/tracking/track.sh blind75/1_3sum.cpp 15 solved "Two Pointer"

# Auto-sync from file header (or use Cmd+Shift+T in VS Code)
./tools/tracking/track_sync.sh "company wise/google/alien_dictionary.cpp"
```
