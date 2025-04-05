#!/bin/bash

# -------- Configuration --------
EXECUTABLE="bin/C2RISC_Engine"  # Change this or override via CLI
TEST_DIR="test"

# -------- Override executable via CLI arg --------
if [ $# -ge 1 ]; then
    EXECUTABLE="$1"
fi

# -------- Check if executable exists --------
if [ ! -x "$EXECUTABLE" ]; then
    echo "❌ Compiler's Executable '$EXECUTABLE' not found or not executable."
    echo "Running 'make' to build the compiler."
    make compiler
fi

# -------- Loop through all files recursively --------
echo "🚀 Running tests with: $EXECUTABLE"
find "$TEST_DIR" -type f | while IFS= read -r test_file; do
    echo "🔹 Running on: $test_file"
    "$EXECUTABLE" "$test_file" -t 2> 
    echo "---------------------------"
done