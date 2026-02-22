#!/bin/bash

# Build and Run Script for C++ files
# Usage: ./tools/build/build_and_run.sh <cpp_file_path> [output_name]

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"

if [ $# -eq 0 ]; then
    echo "Usage: $0 <cpp_file_path> [output_name]"
    echo "Example: $0 multithreading/basic.cpp basic"
    exit 1
fi

CPP_FILE="$1"
OUTPUT_NAME="${2:-$(basename "$1" .cpp)}"
BUILD_DIR="$ROOT_DIR/build"
EXECUTABLES_DIR="$ROOT_DIR/executables"

# Create directories if they don't exist
mkdir -p "$BUILD_DIR"
mkdir -p "$EXECUTABLES_DIR"

# Resolve file relative to ROOT_DIR if not absolute
if [[ "$CPP_FILE" != /* ]]; then
    CPP_FILE="$ROOT_DIR/$CPP_FILE"
fi

# Check if file exists
if [ ! -f "$CPP_FILE" ]; then
    echo "Error: File '$CPP_FILE' not found!"
    exit 1
fi

echo "Compiling $CPP_FILE..."

# Compile with common flags
g++ -std=c++17 -Wall -Wextra -O2 -pthread \
    -I"$ROOT_DIR" \
    "$CPP_FILE" \
    -o "$EXECUTABLES_DIR/$OUTPUT_NAME"

if [ $? -eq 0 ]; then
    echo "✅ Compilation successful!"
    echo "🚀 Running $OUTPUT_NAME..."
    echo "----------------------------------------"
    "$EXECUTABLES_DIR/$OUTPUT_NAME"
    echo "----------------------------------------"
    echo "✅ Execution completed!"
else
    echo "❌ Compilation failed!"
    exit 1
fi
