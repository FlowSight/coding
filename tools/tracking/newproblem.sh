#!/bin/bash

# Usage: ./tools/tracking/newproblem.sh <filename> [directory]
# Example: ./tools/tracking/newproblem.sh two_sum.cpp blind75/
# Example: ./tools/tracking/newproblem.sh cracking_safe.cpp "company wise/google/"

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"

if [ -z "$1" ]; then
    echo "Usage: ./tools/tracking/newproblem.sh <filename.cpp> [directory]"
    echo "Example: ./tools/tracking/newproblem.sh two_sum.cpp blind75/"
    exit 1
fi

FILENAME="$1"
DIR="${2:-.}"  # Default to current directory if not specified

# Get current date in format: 13Feb26
DATE=$(date +"%d%b%y" | sed 's/\([A-Z]\)/\L\1/g')

# Resolve directory relative to ROOT_DIR
if [[ "$DIR" != /* ]]; then
    DIR="$ROOT_DIR/$DIR"
fi

# Create the directory if it doesn't exist
mkdir -p "$DIR"

# Full path
FILEPATH="$DIR/$FILENAME"

# Check if file already exists
if [ -f "$FILEPATH" ]; then
    echo "Error: File '$FILEPATH' already exists!"
    exit 1
fi

# Create file with tracking header
cat > "$FILEPATH" << EOF
// Severity: Sev_
// Date: $DATE
// Where I failed: 
// Pattern: 
// Notes: 

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    
};

int main() {
    Solution sol;
    
    return 0;
}
EOF

echo "Created: $FILEPATH"
echo "Opening in VS Code..."
code "$FILEPATH"
