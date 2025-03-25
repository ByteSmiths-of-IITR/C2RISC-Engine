# Compiler and flags
CXX = g++ -std=c++17 # Added Latest Version [Some error due to old compiler]
CXXFLAGS = -w -lm

#Folders
SRC_DIR = src
INCLUDE_DIR = include
INPUT_DIR = input
OUTPUT_DIR = output
BUILD_DIR = build
BIN_DIR = bin
TEST_DIR = test

# Input and output files
INPUT = $(INPUT_DIR)/input.c
OUTPUT = $(OUTPUT_DIR)/output.txt
CERR = $(OUTPUT_DIR)/stdcerr.log

## for debug we have a console log

# Bison and Flex tools
BISON = bison -Wnone
FLEX = flex

# Source files
LEXER = $(SRC_DIR)/lexer.l
PARSER = $(SRC_DIR)/parser.y
UTILITY_H = utility.h
UTILITY_CPP = $(SRC_DIR)/utility.cpp

# Generated files
LEXER_C = $(BUILD_DIR)/lex.yy.c
PARSER_C = $(BUILD_DIR)/parser.tab.c
PARSER_H = $(INCLUDE_DIR)/parser.tab.h
EXECUTABLE = $(BIN_DIR)/parser

# Result dot (graphviz) tool
DOT = dot
DOTFile = $(BUILD_DIR)/ast_graph.dot
# DOTImage = ast_graph.png [Not used]
DOTPDF = $(OUTPUT_DIR)/PTree.pdf

#More Result FIle
S_EXPR = $(OUTPUT_DIR)/s_expr.txt
Recursive = $(OUTPUT_DIR)/recursive_output.txt



# Default target
all: $(EXECUTABLE)


# Step 1: Generate parser files from Bison
$(PARSER_C) $(PARSER_H): $(PARSER)
	$(BISON) -d $(PARSER) --output=$(PARSER_C) --header=$(PARSER_H)

# Step 2: Generate lexer file from Flex
$(LEXER_C): $(LEXER)
	$(FLEX) -o $(LEXER_C) $(LEXER)

# Step 3: Compile everything together into an executable
$(EXECUTABLE): $(LEXER_C) $(PARSER_C) $(UTILITY_CPP) 
	$(CXX) $(LEXER_C) $(PARSER_C) $(UTILITY_CPP)  -o $(EXECUTABLE) $(CXXFLAGS) -I $(INCLUDE_DIR)

$(CERR):
	touch $(CERR)

$(OUTPUT):
	touch $(OUTPUT)

run: $(EXECUTABLE) $(INPUT) $(OUTPUT) $(CERR)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) 2> $(CERR) 

# This will only run the parser and generate the output file [NO RESULT]


$(DOTFile): $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT) 

# Create required directories
dirs:
	mkdir -p $(BUILD_DIR) $(BIN_DIR) $(OUTPUT_DIR)
	

## For Visualizing the AST
ast: $(INPUT) $(OUTPUT) $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) -ast $(DOTFile) 2> $(CERR)
	$(DOT) -Tpdf $(DOTFile) -o $(DOTPDF)
	open $(DOTPDF)

ptree: $(INPUT) $(OUTPUT) $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) -ptree $(DOTFile) 2> $(CERR)
	$(DOT) -Tpdf $(DOTFile) -o $(DOTPDF)
	open $(DOTPDF) 

r: $(EXECUTABLE) $(INPUT) $(OUTPUT)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) -r 2> $(CERR)

s: $(EXECUTABLE) $(INPUT)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) -s 2> $(CERR)


# Clean generated files
clean:
	@rm -f $(LEXER_C) $(PARSER_C) $(PARSER_H) $(EXECUTABLE) $(OUTPUT) \
	$(CERR) $(DOTFile) $(DOTPDF) $(S_EXPR) $(Recursive) $(ASSEMBLY)


again:
	rm -f $(EXECUTABLE) \
		$(PARSER_C) \
		$(PARSER_H)
	make all


semantic: $(EXECUTABLE) $(INPUT) $(OUTPUT)
	@echo "-------------------------------------------Our Syntax Analysis-------------------------------------------"
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) 2> $(CERR)
	@echo "---------------------------------------------GCC Compilation---------------------------------------------"
	@gcc -fsyntax-only $(INPUT) && echo "✅ Successfully Compiled by GCC"

execute: $(EXECUTABLE) $(INPUT) $(OUTPUT)
	@gcc $(INPUT) -o $(BIN_DIR)/input_exec
	@./$(BIN_DIR)/input_exec

sem_ast: $(EXECUTABLE) $(INPUT) $(OUTPUT)
	@echo "-------------------------------------------Our Syntax Analysis-------------------------------------------"
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) -ast $(DOTFile) 2> $(CERR)
	@echo "---------------------------------------GCC Compilation---------------------------------------"
	@-gcc -fsyntax-only $(INPUT) && echo "✅ Successfully Compiled by GCC"
	@$(DOT) -Tpdf $(DOTFile) -o $(DOTPDF)
	@open $(DOTPDF)

ASSEMBLY = $(OUTPUT_DIR)/assembly.s

assembly: $(INPUT)
	@clang -S -target riscv32-unknown-elf -march=rv32i $(INPUT) -o $(ASSEMBLY)


astdump: $(INPUT)
	@clang -Xclang -ast-dump -fsyntax-only $(INPUT)

SYM_H = $(INCLUDE_DIR)/sym.h
SYM_CPP = $(SRC_DIR)/sym.cpp
SYM_TEST = $(SRC_DIR)/test_sym.cpp

SYM_TABLEFile = $(OUTPUT_DIR)/sym_table.txt

sym: $(SYM_H) $(SYM_CPP) $(SYM_TEST)
	$(CXX) $(UTILITY_CPP) $(SYM_CPP) $(SYM_TEST) -o $(BIN_DIR)/symTest $(CXXFLAGS) -I $(INCLUDE_DIR)
	./$(BIN_DIR)/symTest $(SYM_TABLEFile)

