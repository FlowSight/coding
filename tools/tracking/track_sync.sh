#!/bin/bash

# ============================================================
# track_sync.sh - Reads LC#, severity, pattern from file header
#                 and syncs to question_tracker.csv
# ============================================================
# Usage: ./tools/tracking/track_sync.sh <file.cpp>
#   Called automatically via Cmd+Shift+T in VS Code
#
# Reads from the file's comment header:
#   // LC: 269
#   // Severity: Sev0  →  maps to status: Sev0=Redo, Sev1=Redo, Sev2=Solved
#   // Pattern: DP      →  maps to Tag
#   // Notes: ...       →  maps to Notes
# ============================================================

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
CSV_FILE="$ROOT_DIR/Progress/coding/google/question_tracker.csv"
TODAY=$(date +"%d%b%Y" | awk '{print tolower($0)}')

if [ -z "$1" ]; then
    echo "Usage: ./tools/tracking/track_sync.sh <file.cpp>"
    exit 1
fi

FILE="$1"
if [[ "$FILE" != /* ]]; then
    FILE="$ROOT_DIR/$FILE"
fi

if [ ! -f "$FILE" ]; then
    echo "❌ File not found: $FILE"
    exit 1
fi

if [ ! -f "$CSV_FILE" ]; then
    echo "❌ CSV not found: $CSV_FILE"
    exit 1
fi

# ============================================================
# Extract info from file header (first 15 lines)
# ============================================================
HEADER=$(head -15 "$FILE")

# LC number — match "// LC: 123" or "// LC number: 123"
LC_NUM=$(echo "$HEADER" | grep -m1 -oE '// LC[^:]*:\s*[0-9]+' | grep -oE '[0-9]+')

if [ -z "$LC_NUM" ]; then
    echo "❌ No LC number found in file header."
    echo "   Add '// LC: <number>' to your file first."
    echo "   Tip: use the 'track' snippet to add the header."
    exit 1
fi

# Status is determined by whether entry exists in CSV (set after lookup below)

# Pattern → Tag
TAG=$(echo "$HEADER" | grep -m1 -iE '// [Pp]attern:' | sed 's|.*[Pp]attern:\s*||' | sed 's/\s*$//')
[ "$TAG" = "pattern_name" ] && TAG=""

# Notes
NOTES=$(echo "$HEADER" | grep -m1 -iE '// [Nn]otes:' | sed 's|.*[Nn]otes:\s*||' | sed 's/\s*$//')
[ "$NOTES" = "additional_notes" ] && NOTES=""

# Problem name from filename
BASENAME=$(basename "$FILE" .cpp)
PROBLEM_NAME=$(echo "$BASENAME" | sed 's/_/ /g; s/-/ /g' | awk '{for(i=1;i<=NF;i++) $i=toupper(substr($i,1,1)) tolower(substr($i,2))}1')

# Try to extract from // Problem: header
FILE_PROBLEM=$(grep -m1 "// Problem:" "$FILE" | sed 's|// Problem: *||')
if [ -n "$FILE_PROBLEM" ] && [ "$FILE_PROBLEM" != "problem_name" ]; then
    PROBLEM_NAME="$FILE_PROBLEM"
fi

# ============================================================
# Find or create entry in CSV
# ============================================================
FOUND_LINE=$(awk -F',' -v lc="$LC_NUM" 'NR>1 && $2==lc {print NR; exit}' "$CSV_FILE")

if [ -n "$FOUND_LINE" ]; then
    # Entry exists → Redo
    STATUS="Redo"
    EXISTING=$(awk -F',' -v lc="$LC_NUM" 'NR>1 && $2==lc {print $0; exit}' "$CSV_FILE")
    OLD_PROBLEM=$(echo "$EXISTING" | awk -F',' '{print $1}')
    OLD_TAG=$(echo "$EXISTING" | awk -F',' '{print $5}')
    OLD_NOTES=$(echo "$EXISTING" | awk -F',' '{print $6}')

    [ -z "$TAG" ] && TAG="$OLD_TAG"
    [ -z "$NOTES" ] && NOTES="$OLD_NOTES"
    [ -n "$OLD_PROBLEM" ] && PROBLEM_NAME="$OLD_PROBLEM"

    NEW_LINE="$PROBLEM_NAME,$LC_NUM,$STATUS,$TODAY,$TAG,$NOTES"
    TMPCSV=$(mktemp)
    awk -F',' -v lc="$LC_NUM" -v newline="$NEW_LINE" 'BEGIN{OFS=","} NR==1{print; next} $2==lc{print newline; next} {print}' "$CSV_FILE" > "$TMPCSV" && mv "$TMPCSV" "$CSV_FILE"
    echo "✅ Updated: LC#$LC_NUM → $STATUS"
else
    # New entry → Solved
    STATUS="Solved"
    NEW_LINE="$PROBLEM_NAME,$LC_NUM,$STATUS,$TODAY,$TAG,$NOTES"
    # Ensure CSV ends with a newline before appending
    [ -s "$CSV_FILE" ] && [ -n "$(tail -c 1 "$CSV_FILE")" ] && echo >> "$CSV_FILE"
    echo "$NEW_LINE" >> "$CSV_FILE"
    echo "✅ New entry: $PROBLEM_NAME (LC#$LC_NUM) → $STATUS"
fi

# ============================================================
# Summary
# ============================================================
echo ""
echo "📋 Synced to CSV:"
echo "   Problem : $PROBLEM_NAME"
echo "   LC#     : $LC_NUM"
echo "   Status  : $STATUS"
echo "   Date    : $TODAY"
echo "   Tag     : $TAG"
echo "   Notes   : $NOTES"
echo ""

# Stats
TOTAL=$(awk -F',' 'NR>1 && $1!="" {count++} END {print count}' "$CSV_FILE")
SOLVED=$(awk -F',' 'NR>1 && $3=="Solved" {count++} END {print count+0}' "$CSV_FILE")
REDO=$(awk -F',' 'NR>1 && $3=="Redo" {count++} END {print count+0}' "$CSV_FILE")
echo "📊 Stats: $TOTAL tracked | $SOLVED solved | $REDO redo"
