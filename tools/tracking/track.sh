#!/bin/bash

# ============================================================
# track.sh - Track LeetCode problem progress in question_tracker.csv
# ============================================================
# Usage:
#   ./tools/tracking/track.sh <file.cpp> <lc_number> [solved|redo] [tag] [notes]
#
# Examples:
#   ./tools/tracking/track.sh "company wise/google/alien_dictionay.cpp" 269 solved
#   ./tools/tracking/track.sh blind75/1_3sum.cpp 15 solved "Two Pointer" "sorted first"
#   ./tools/tracking/track.sh dp/egg_drop.cpp 887 redo "DP" "revisit dp transition"
#
# What it does:
#   1. Adds/updates "// LC: <number>" tag in the cpp file header
#   2. Finds the entry in question_tracker.csv by LC#
#      - If found: updates Status and Date
#      - If not found: creates a new row
#   3. Sets Status to Solved or Redo
# ============================================================

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
CSV_FILE="$ROOT_DIR/Progress/coding/google/question_tracker.csv"
TODAY=$(date +"%d%b%Y" | awk '{print tolower($0)}')

# --- Arg validation ---
if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Usage: ./tools/tracking/track.sh <file.cpp> <lc_number> [solved|redo] [tag] [notes]"
    echo ""
    echo "Examples:"
    echo "  ./tools/tracking/track.sh \"company wise/google/alien_dictionay.cpp\" 269 solved"
    echo "  ./tools/tracking/track.sh blind75/1_3sum.cpp 15 solved \"Two Pointer\""
    exit 1
fi

FILE="$1"
LC_NUM="$2"
STATUS="${3:-Solved}"
TAG="${4:-}"
NOTES="${5:-}"

# Normalize status
STATUS_LOWER=$(echo "$STATUS" | tr '[:upper:]' '[:lower:]')
if [[ "$STATUS_LOWER" == "solved" || "$STATUS_LOWER" == "s" ]]; then
    STATUS="Solved"
elif [[ "$STATUS_LOWER" == "redo" || "$STATUS_LOWER" == "r" ]]; then
    STATUS="Redo"
else
    STATUS="Solved"
fi

# Resolve file path relative to ROOT_DIR
if [[ "$FILE" != /* ]]; then
    FILE="$ROOT_DIR/$FILE"
fi

if [ ! -f "$FILE" ]; then
    echo "❌ File not found: $FILE"
    exit 1
fi

if [ ! -f "$CSV_FILE" ]; then
    echo "❌ CSV not found: $CSV_FILE"
    echo "   Expected at: Progress/coding/google/question_tracker.csv"
    exit 1
fi

# ============================================================
# Step 1: Tag the LC number in the cpp file
# ============================================================
TMPFILE=$(mktemp)
if grep -q "// LC:" "$FILE"; then
    # Update existing LC tag
    sed "s|// LC:.*|// LC: $LC_NUM|" "$FILE" > "$TMPFILE" && mv "$TMPFILE" "$FILE"
    echo "✅ Updated LC tag in file: // LC: $LC_NUM"
else
    # Add LC tag after first line (or at top if file is small)
    FIRST_LINE=$(head -1 "$FILE")
    if [[ "$FIRST_LINE" == //* ]]; then
        # File starts with comments, insert LC tag after first comment line
        { head -1 "$FILE"; echo "// LC: $LC_NUM"; tail -n +2 "$FILE"; } > "$TMPFILE" && mv "$TMPFILE" "$FILE"
    else
        # File doesn't start with comment, prepend
        { echo "// LC: $LC_NUM"; cat "$FILE"; } > "$TMPFILE" && mv "$TMPFILE" "$FILE"
    fi
    echo "✅ Added LC tag to file: // LC: $LC_NUM"
fi

# ============================================================
# Step 2: Extract problem name from file
# ============================================================
BASENAME=$(basename "$FILE" .cpp)
# Clean up filename to problem name: replace _ with space, title case
PROBLEM_NAME=$(echo "$BASENAME" | sed 's/_/ /g' | awk '{for(i=1;i<=NF;i++) $i=toupper(substr($i,1,1)) tolower(substr($i,2))}1')

# Try to extract from // Problem: header in the file
FILE_PROBLEM=$(grep -m1 "// Problem:" "$FILE" | sed 's|// Problem: *||')
if [ -n "$FILE_PROBLEM" ]; then
    PROBLEM_NAME="$FILE_PROBLEM"
fi

# ============================================================
# Step 3: Find or create entry in CSV
# ============================================================
# Search by LC# (column 2)
FOUND_LINE=$(awk -F',' -v lc="$LC_NUM" 'NR>1 && $2==lc {print NR; exit}' "$CSV_FILE")

if [ -n "$FOUND_LINE" ]; then
    # --- Entry exists: update Status and Date ---
    # Read existing values to preserve what we can
    EXISTING=$(awk -F',' -v lc="$LC_NUM" 'NR>1 && $2==lc {print $0; exit}' "$CSV_FILE")
    OLD_PROBLEM=$(echo "$EXISTING" | awk -F',' '{print $1}')
    OLD_TAG=$(echo "$EXISTING" | awk -F',' '{print $5}')
    OLD_NOTES=$(echo "$EXISTING" | awk -F',' '{print $6}')

    # Use existing values if new ones not provided
    [ -z "$TAG" ] && TAG="$OLD_TAG"
    [ -z "$NOTES" ] && NOTES="$OLD_NOTES"
    [ -n "$OLD_PROBLEM" ] && PROBLEM_NAME="$OLD_PROBLEM"

    # Replace the line
    NEW_LINE="$PROBLEM_NAME,$LC_NUM,$STATUS,$TODAY,$TAG,$NOTES"
    TMPCSV=$(mktemp)
    awk -F',' -v lc="$LC_NUM" -v newline="$NEW_LINE" 'BEGIN{OFS=","} NR==1{print; next} $2==lc{print newline; next} {print}' "$CSV_FILE" > "$TMPCSV" && mv "$TMPCSV" "$CSV_FILE"
    echo "✅ Updated existing entry: LC#$LC_NUM → $STATUS"
else
    # --- New entry: append to CSV ---
    NEW_LINE="$PROBLEM_NAME,$LC_NUM,$STATUS,$TODAY,$TAG,$NOTES"
    # Ensure CSV ends with a newline before appending
    [ -s "$CSV_FILE" ] && [ -n "$(tail -c 1 "$CSV_FILE")" ] && echo >> "$CSV_FILE"
    echo "$NEW_LINE" >> "$CSV_FILE"
    echo "✅ Created new entry: $PROBLEM_NAME (LC#$LC_NUM) → $STATUS"
fi

# ============================================================
# Summary
# ============================================================
echo ""
echo "📋 Tracker Summary:"
echo "   Problem : $PROBLEM_NAME"
echo "   LC#     : $LC_NUM"
echo "   Status  : $STATUS"
echo "   Date    : $TODAY"
echo "   Tag     : $TAG"
echo "   File    : $(basename "$FILE")"
echo ""

# Show current stats
TOTAL=$(awk -F',' 'NR>1 && $1!="" {count++} END {print count}' "$CSV_FILE")
SOLVED=$(awk -F',' 'NR>1 && $3=="Solved" {count++} END {print count+0}' "$CSV_FILE")
REDO=$(awk -F',' 'NR>1 && $3=="Redo" {count++} END {print count+0}' "$CSV_FILE")
NOT_STARTED=$(awk -F',' 'NR>1 && $3=="Not Started" {count++} END {print count+0}' "$CSV_FILE")
echo "📊 Overall: $TOTAL tracked | $SOLVED solved | $REDO redo | $NOT_STARTED not started"
