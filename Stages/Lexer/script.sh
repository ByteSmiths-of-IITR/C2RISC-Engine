#!/bin/bash

# Check if the lexer executable exists
if [ ! -f lexer ]; then
    echo "Lexer executable not found. Building using Makefile..."
    make
fi

# Detect OS
if [[ "$OSTYPE" == "linux-gnu"* ]] || [[ "$OSTYPE" == "darwin"* ]]; then
    # UNIX-based system (Linux/macOS)
    echo "Running on UNIX-based system"
    system=1
elif [[ "$OSTYPE" == "msys"* ]] || [[ "$OSTYPE" == "cygwin"* ]] || [[ "$OS" == "Windows_NT" ]]; then
    # Windows system (Git Bash, Cygwin, or native Windows)
    echo "Running on Windows"
    system=2
else
    echo "Unsupported OS: $OSTYPE"
    exit 1
fi

# Run lexer on each test case
for test_file in test/*.cpp; do
    echo "Running lexer on $test_file..."
    # Run lexer on the test file
    if [ $system -eq 1 ]; then
        ./lexer "$test_file"
    elif [ $system -eq 2 ]; then
        ./lexer.exe "$test_file"
    fi

    echo "------------------------------------"
done