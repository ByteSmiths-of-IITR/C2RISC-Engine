#!/bin/bash

# -------- Configuration --------
EXECUTABLE="bin/C2RISC_Engine"   # Default executable
TEST_DIR="test"                  # Default test directory
ERROR="output/testing.log"       # Error log file

# -------- Parse arguments --------
FILTER_DIR=""
if [ $# -ge 1 ]; then
    FILTER_DIR="$TEST_DIR/$1."  # Match the numbered folder pattern
fi

if [ $# -ge 2 ]; then
    EXECUTABLE="$2"  # Optional override for executable
fi

# -------- Check if executable exists --------
if [ ! -x "$EXECUTABLE" ]; then
    make compiler || { echo "❌ Make failed."; exit 1; }
fi

# -------- Ensure output directory for log exists --------
mkdir -p "$(dirname "$ERROR")"
> "$ERROR"  # Clear previous error log

# -------- Find and run tests --------
echo "🚀 Running tests with: $EXECUTABLE"

# If a specific numbered folder is given, filter by it
if [ -n "$FILTER_DIR" ]; then
    find "$FILTER_DIR"* -type f -name "*.c" 2>/dev/null | while IFS= read -r test_file; do
        echo "🔹 Running on: $test_file"
        "$EXECUTABLE" "$test_file" -t 2>>"$ERROR"
        echo "---------------------------"
    done
else
    # Run all .c tests if no folder filter is provided
    find "$TEST_DIR" -type f -name "*.c" | while IFS= read -r test_file; do
        echo "🔹 Running on: $test_file"
        "$EXECUTABLE" "$test_file" -t 2>>"$ERROR"
        echo "---------------------------"
    done
fi