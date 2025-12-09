#!/bin/bash

# Build and Run Script for C++ files
# Usage: ./build_and_run.sh <cpp_file_path> [output_name]

if [ $# -eq 0 ]; then
    echo "Usage: $0 <cpp_file_path> [output_name]"
    echo "Example: $0 multithreading/basic.cpp basic"
    exit 1
fi

CPP_FILE="$1"
OUTPUT_NAME="${2:-$(basename "$1" .cpp)}"
BUILD_DIR="./build"
EXECUTABLES_DIR="./executables"

# Create directories if they don't exist
mkdir -p "$BUILD_DIR"
mkdir -p "$EXECUTABLES_DIR"

# Check if file exists
if [ ! -f "$CPP_FILE" ]; then
    echo "Error: File '$CPP_FILE' not found!"
    exit 1
fi

echo "Compiling $CPP_FILE..."

# Compile with common flags
g++ -std=c++17 -Wall -Wextra -O2 -pthread \
    -I. \
    "$CPP_FILE" \
    -o "$EXECUTABLES_DIR/$OUTPUT_NAME"

if [ $? -eq 0 ]; then
    echo "✅ Compilation successful!"
    echo "🚀 Running $OUTPUT_NAME..."
    echo "----------------------------------------"
    "./$EXECUTABLES_DIR/$OUTPUT_NAME"
    echo "----------------------------------------"
    echo "✅ Execution completed!"
else
    echo "❌ Compilation failed!"
    exit 1
fi