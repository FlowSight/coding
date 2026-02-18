#!/bin/bash

# Usage: ./newproblem.sh <filename> [directory]
# Example: ./newproblem.sh two_sum.cpp blind75/
# Example: ./newproblem.sh cracking_safe.cpp "company wise/google/"

if [ -z "$1" ]; then
    echo "Usage: ./newproblem.sh <filename.cpp> [directory]"
    echo "Example: ./newproblem.sh two_sum.cpp blind75/"
    exit 1
fi

FILENAME="$1"
DIR="${2:-.}"  # Default to current directory if not specified

# Get current date in format: 13Feb26
DATE=$(date +"%d%b%y" | sed 's/\([A-Z]\)/\L\1/g')

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
// Problem: ${FILENAME%.cpp}
// 
// How much solved: 
// Where I failed: 
// Pattern: 
// Notes: 
//
// Sev0 = Couldn't solve / Major conceptual gap
// Sev1 = Solved with hints / Minor issues  
// Sev2 = Solved independently

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
