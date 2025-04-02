#Folders
SRC_DIR = src
INCLUDE_DIR = include
INPUT_DIR = input
OUTPUT_DIR = output
BUILD_DIR = build
OBJ_DIR = object
BIN_DIR = bin
TEST_DIR = test
GRAMMAR_DIR = grammar

# Compiler and flags
CXX = g++ -std=c++17 # Added Latest Version [Some error due to old compiler]
CC = gcc
CXXFLAGS = -w -lm -I $(INCLUDE_DIR)


# Input and output files
INPUT = $(INPUT_DIR)/input.c
OUTPUT = $(OUTPUT_DIR)/output.txt
CERR = $(OUTPUT_DIR)/stdcerr.log

## for debug we have a console log

# Bison and Flex tools
BISON = bison -Wnone
FLEX = flex

# Lexer File
LEXER = $(GRAMMAR_DIR)/lexer.l
LEXER_C = $(BUILD_DIR)/lex.yy.c


# Header Files
UTILITY_H = utility.h
HEADER_H = header.h

# Source Files
HEADER_CPP = $(SRC_DIR)/header.cpp
SEMANTIC_CPP = $(SRC_DIR)/semantic.cpp
SYM_CPP = $(SRC_DIR)/sym.cpp
TAC_CPP = $(SRC_DIR)/tac.cpp
TYPE_CPP = $(SRC_DIR)/type.cpp
UTILITY_CPP = $(SRC_DIR)/utility.cpp


# Parser\Bison Files
PARSER_C = $(BUILD_DIR)/parser.tab.c

PARSER = $(GRAMMAR_DIR)/parser.y # just change Grammar File Here will change all 

PARSER_H = $(INCLUDE_DIR)/parser.tab.h
EXECUTABLE = $(BIN_DIR)/parser

# Making Object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DIR) 
	@$(CXX) $(CXXFLAGS) -c $< -o $@ 


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
$(PARSER_C) $(PARSER_H): $(PARSER) $(BUILD_DIR)
	@$(BISON) -d $(PARSER) --output=$(PARSER_C) --header=$(PARSER_H)

# Step 2: Generate lexer file from Flex
$(LEXER_C): $(LEXER) $(BUILD_DIR) 
	@$(FLEX) -o $(LEXER_C) $(LEXER)

# Step 3: Compile everything together into an executable
$(EXECUTABLE): $(LEXER_C) $(PARSER_C) $(PARSER_H) $(OBJ_FILES) $(BIN_DIR) $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LEXER_C) $(PARSER_C) $(OBJ_FILES) -o $(EXECUTABLE)

$(CERR): $(OUTPUT_DIR)
	@touch $(CERR)

$(OUTPUT): $(OUTPUT_DIR)
	@touch $(OUTPUT)

run: $(EXECUTABLE) $(INPUT) $(OUTPUT) $(CERR) $(OUTPUT_DIR) $(BUILD_DIR) $(OBJ_DIR) 
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) 2> $(CERR) 

# This will only run the parser and generate the output file [NO RESULT]


$(DOTFile): $(EXECUTABLE)
	@./$(EXECUTABLE) $(INPUT) 

# Auto Create Required Directories
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)




## For Visualizing the AST
ast: $(INPUT) $(OUTPUT) $(EXECUTABLE) $(OUTPUT_DIR) $(BUILD_DIR) 
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) -ast $(DOTFile) 2> $(CERR)
	@$(DOT) -Tpdf $(DOTFile) -o $(DOTPDF)

ptree: $(INPUT) $(OUTPUT) $(EXECUTABLE) $(OUTPUT_DIR) $(BUILD_DIR) 
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) -ptree $(DOTFile) 2> $(CERR)
	@$(DOT) -Tpdf $(DOTFile) -o $(DOTPDF)

DOTFile2 = $(BUILD_DIR)/annotated_ast_graph.dot
DOTPDF2 = $(OUTPUT_DIR)/A_PTree.svg

$(DOTFile2):
	@touch $(DOTFile2)

$(DOTPDF2):
	@touch $(DOTPDF2)

Aptree: $(INPUT) $(OUTPUT) $(EXECUTABLE) $(OUTPUT_DIR) $(BUILD_DIR) $(DOTFile2) $(DOTPDF2) $(OBJ_DIR)
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) -APTree $(DOTFile2) 2> $(CERR)
	$(DOT) -Tsvg $(DOTFile2) -o $(DOTPDF2)

r: $(EXECUTABLE) $(INPUT) $(OUTPUT)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) -r 2> $(CERR)

s: $(EXECUTABLE) $(INPUT)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) -s 2> $(CERR)


# Clean generated files
clean:
	@rm -f $(LEXER_C) $(PARSER_C) $(PARSER_H) $(EXECUTABLE) $(OUTPUT) \
	$(CERR) $(DOTFile) $(DOTPDF) $(S_EXPR) $(Recursive) $(ASSEMBLY) \
	$(OBJ_FILES)

again:
	rm -f $(EXECUTABLE) \
		$(PARSER_C) \
		$(PARSER_H)
	make all


semantic: $(EXECUTABLE) $(INPUT) $(OUTPUT)
	@echo "---------------------------------------------GCC Compilation---------------------------------------------"
	@$(CC) -fsyntax-only $(INPUT) && echo "✅ Successfully Compiled by GCC"
	@echo "-------------------------------------------Our Syntax Analysis-------------------------------------------"
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) 2> $(CERR)
	

execute: $(INPUT)
	@$(CC) $(INPUT) -o $(BIN_DIR)/input_exec
	@./$(BIN_DIR)/input_exec

sem_ast: $(EXECUTABLE) $(INPUT) $(OUTPUT)
	@echo "---------------------------------------GCC Compilation---------------------------------------"
	@-$(CC) -fsyntax-only $(INPUT) && echo "✅ Successfully Compiled by GCC"
	@echo "-------------------------------------------Our Syntax Analysis-------------------------------------------"
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) -ast $(DOTFile) 2> $(CERR)
	@$(DOT) -Tpdf $(DOTFile) -o $(DOTPDF)
	@open $(DOTPDF)

sem_ptree: $(EXECUTABLE) $(INPUT) $(OUTPUT)
	@echo "---------------------------------------GCC Compilation---------------------------------------"
	@-$(CC) -fsyntax-only $(INPUT) && echo "✅ Successfully Compiled by GCC"
	@echo "-------------------------------------------Our Syntax Analysis-------------------------------------------"
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) -ptree $(DOTFile) 2> $(CERR)
	@$(DOT) -Tpdf $(DOTFile) -o $(DOTPDF)

ASSEMBLY = $(OUTPUT_DIR)/assembly.s
LLVMIR = $(OUTPUT_DIR)/llvm_ir.ll

assembly: $(INPUT)
	@clang -S -target riscv32-unknown-elf -march=rv32i $(INPUT) -o $(ASSEMBLY)

llvm: $(INPUT)
	@clang -S -emit-llvm $(INPUT) -o $(LLVMIR)

astdump: $(INPUT)
	@clang -Xclang -ast-dump -fsyntax-only $(INPUT)

SYM_H = $(INCLUDE_DIR)/sym.h
SYM_CPP = $(SRC_DIR)/sym.cpp
SYM_TEST = $(SRC_DIR)/test_sym.cpp

SYM_TABLEFile = $(OUTPUT_DIR)/sym_table.txt

sym: $(SYM_H) $(SYM_CPP) $(SYM_TEST)
	@$(CXX) $(UTILITY_CPP) $(SYM_CPP) $(SYM_TEST) -o $(BIN_DIR)/symTest $(CXXFLAGS) -I $(INCLUDE_DIR)
	@./$(BIN_DIR)/symTest $(SYM_TABLEFile)


# IRSemantic = $(SRC_DIR)/IRCodeGen.y
# IRSemantic_H = $(INCLUDE_DIR)/IRCodeGen.tab.h
# IRSemantic_CPP = $(SRC_DIR)/IRCodeGen.tab.c
# IRSemantic_EXECUTABLE = $(BIN_DIR)/IRCodeGen

# $(IRSemantic_H): $(IRSemantic)
# 	@$(BISON) -d $(IRSemantic) --output=$(IRSemantic_CPP) --header=$(IRSemantic_H)


# IRCode: $(IRSemantic)  $(IRSemantic_H) $(IRSemantic_CPP) $(SYM_CPP) $(SEMANTIC_CPP) $(TAC_CPP) $(UTILITY_CPP)
# 	$(CXX) $(LEXER_C) $(IRSemantic_CPP) $(SYM_CPP) $(SEMANTIC_CPP) $(TAC_CPP) $(UTILITY_CPP) -o $(IRSemantic_EXECUTABLE) $(CXXFLAGS) -I $(INCLUDE_DIR)
# 	./$(IRSemantic_EXECUTABLE)

UNIT_TEST = unit_testing.cpp

UNIT_TEST_EXECUTABLE = $(BIN_DIR)/unit_test

unitTest: $(UNIT_TEST) $(OBJ_FILES) 
	$(CXX) $(CXXFLAGS) $(UNIT_TEST) $(OBJ_FILES) -o $(UNIT_TEST_EXECUTABLE)
	./$(UNIT_TEST_EXECUTABLE)


IRCodeFile = $(OUTPUT_DIR)/IRCode.txt

$(IRCodeFile):
	@touch $(IRCodeFile)

irCode: $(EXECUTABLE) $(INPUT) $(OUTPUT) $(CERR) $(OUTPUT_DIR) $(BUILD_DIR) $(OBJ_DIR) $(IRCodeFile)
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) -tac $(IRCodeFile) -APTree $(DOTFile2) 2> $(CERR)
	@$(DOT) -Tsvg $(DOTFile2) -o $(DOTPDF2)
