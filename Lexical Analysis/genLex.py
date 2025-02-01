import os
import sys

# Check if the correct number of arguments are provided
if len(sys.argv) != 2:
    print("Usage: python3 genLex.py <lexer_file>")
    sys.exit(1)


# Define filenames
lexer_file = sys.argv[1]
output_executable = "lexer"
input_file = "input.cpp"
output_file = "output.txt"

# Step 1: Run FLEX to generate lex.yy.c
print("Running FLEX...\n")
os.system(f"flex {lexer_file}")

# Step 2: Compile lex.yy.c with Clang
print("Compiling lexer...")
compile_cmd = f"$CXX lex.yy.c -o {output_executable}"
if os.system(compile_cmd) != 0:
    print("Compilation failed!")
    sys.exit(1)

# Step 3: Run the lexer on input file
print("Running lexer...\n")
os.system(f"./{output_executable} {input_file} {output_file}")

print(f"Lexical analysis complete. Output saved to {output_file}")
