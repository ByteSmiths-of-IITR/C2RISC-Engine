# !/bin/bash

# Set paths
Ptest_dir="./test/positive"
Ntest_dir="./test/negative"
executable="./parser"
results_dir="./test_results"
AST_results_dir="./test_results/AST"
LaTexFile="parser_table.tex"
Table="parser_table"

# Ensure the executable exists
if [ ! -f "$executable" ]; then
    echo "Executable not found. Running 'make' in the parser directory first."
    make
fi

# Create results directory if it doesn't exist
mkdir -p "$results_dir"

# Iterate over test cases
echo "👍 Running positive tests..."
for test_file in $(find "$Ptest_dir" -type f -name "*.c"); do
    test_name=$(basename "$test_file" .c)
    output_file="$results_dir/P_${test_name}.out"
    
    echo "-----Running test: $test_file------"
    "$executable" "$test_file" "$output_file"

    # This will generate a LaTex File for the parser table
    echo "-----Generating PDF of Parser Table from LaTeX------"
    pdflatex -jobname="$Table" "$LaTexFile" > /dev/null 2>&1
    # Now cp the file to the test_results directory with the name of the test
    cp "$Table.pdf" "$results_dir/${test_name}_Table.pdf"
    echo ""
done

echo " ## All Output stored in: $results_dir as <P_test_name>.out and <test_name>_Table.pdf------"

echo "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
echo "🚨 Running negative tests..."

for test_file in $(find "$Ntest_dir" -type f -name "*.c"); do
    test_name=$(basename "$test_file" .c)
    output_file="$results_dir/N_${test_name}.out"
    
    echo "-----Running test: $test_file------"
    "$executable" "$test_file" "$output_file"

    echo " "
done
echo "## All Output stored in: $results_dir as <N_test_name>.out------"

echo "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
echo "" 
dotFile="ast_graph.dot"

echo "---------AST Option---------"
# Ask user if they was AST as well
echo "❓ Would you like to generate the AST for the positive tests? (y/n)"
read -r response

#new folder for ASTs
mkdir -p "$AST_results_dir"

if [ "$response" = "y" ]; then
    echo "🌳 Generating ASTs..."
    for test_file in $(find "$Ptest_dir" -type f -name "*.c"); do
        test_name=$(basename "$test_file" .c)
        output_file="$results_dir/P_${test_name}.out"
        
        "$executable" "$test_file" "$output_file" -ast "$dotFile"
        dot -Tpdf "$dotFile" -o "$AST_results_dir/${test_name}_AST.pdf"
        echo -n "."
    done
    echo ""
    echo " All The ASTs stored in: $AST_results_dir------"
fi
echo "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
# Define color codes
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
CYAN='\033[1;36m'
RESET='\033[0m'
echo ""
# Print the banner with decorations
echo -e "${BLUE}+------------------------------------------------------------+"
echo -e "${YELLOW}| ${GREEN}🎉  Thank you for using the ${CYAN}C2RISC-Engine Parser!  ${GREEN}🎉  ${YELLOW}|"
echo -e "${YELLOW}| ${RED}Developed with ❤️ by ${CYAN}Vineet, Raman, Vraj & Indranil 🚀 ${YELLOW}|"
echo -e "${BLUE}+------------------------------------------------------------+${RESET}"
echo ""

# Clean up
echo "Cleaning up..."
make clean