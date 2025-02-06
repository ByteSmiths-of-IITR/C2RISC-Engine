#!/bin/bash

# Check if the lexer executable exists
if [ ! -f lexer ]; then
    echo "Lexer executable not found. Building using Makefile..."
    make
fi

# Run lexer on each test case
for test_file in test/*.cpp; do
    echo "Running lexer on $test_file..."
    ./lexer "$test_file"
    echo "------------------------------------"
done