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

# Directories
REQUIRED_DIRS = build bin object output

$(REQUIRED_DIRS):
	@if [ ! -d $@ ]; then mkdir -p $@; fi

.PHONY: all $(REQUIRED_DIRS) 

.INIT: $(REQUIRED_DIRS)



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
EXECUTABLE = $(BIN_DIR)/C2RISC_Engine

# Making Object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Creating Object File of" $<
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(OBJ_FILES:.o=.d)


#More Result FIle
S_EXPR = $(OUTPUT_DIR)/s_expr.txt
Recursive = $(OUTPUT_DIR)/recursive_output.txt


# Default target
all: $(REQUIRED_DIRS) $(OUTPUT) $(INPUT) $(CERR) 

compiler: all $(EXECUTABLE) $(INPUT) $(OUTPUT) $(CERR)
	@echo "----- 🏗️ C2RISC_Engine Successfully Built 🏗️ -----"

# Step 1: Generate parser files from Bison
$(PARSER_C) $(PARSER_H): $(PARSER) 
	@echo "~~~~~~~~~~~~~~~~~~~~~ Making Parser ~~~~~~~~~~~~~~~~~"
	@$(BISON) -d $(PARSER) --output=$(PARSER_C) --header=$(PARSER_H) 

# Step 2: Generate lexer file from Flex
$(LEXER_C): $(LEXER) 
	@echo "~~~~~~~~~~~~~~~~~~~~~ Making Lexer ~~~~~~~~~~~~~~~~~"
	@$(FLEX) -o $(LEXER_C) $(LEXER)

# Step 3: Compile everything together into an executable
$(EXECUTABLE): $(LEXER_C) $(PARSER_C) $(PARSER_H) $(OBJ_FILES) 
	@echo "=================== 🔨 Making C2RISC Engine 🔨 ==================="
	@$(CXX) $(CXXFLAGS) $(LEXER_C) $(PARSER_C) $(OBJ_FILES) -o $(EXECUTABLE)

$(CERR): | $(OUTPUT_DIR)
	@touch $(CERR)

$(OUTPUT): | $(OUTPUT_DIR)
	@touch $(OUTPUT)

run: all $(EXECUTABLE) $(INPUT) $(OUTPUT) $(CERR)
	@echo "🚥 Starting C2RISC Engine 🟢 on -" $(INPUT)
	@./$(EXECUTABLE) $(INPUT) 2> $(CERR)

# This will only run the parser and generate the output file [NO RESULT]


# Result dot (graphviz) tool
DOT = dot



PTreeFile = $(BUILD_DIR)/ptree_graph.dot
PTreeSVG = $(OUTPUT_DIR)/PTree.svg

ptree: all $(INPUT) $(OUTPUT) $(EXECUTABLE)  $(CERR)
	@echo "🚥 Starting C2RISC Engine 🟢 on -" $(INPUT)
	@./$(EXECUTABLE) $(INPUT) -t -d1 $(PTreeFile)  2> $(CERR)
	@echo "🌲 PTree in " $(PTreeSVG) 
	@$(DOT) -Tsvg $(PTreeFile) -o $(PTreeSVG)
	open $(PTreeSVG)

APTreeFile = $(BUILD_DIR)/annotated_ast_graph.dot
APTreeSVG = $(OUTPUT_DIR)/A_PTree.svg

$(APTreeFile):
	@touch $(APTreeFile)

$(APTreeSVG):
	@touch $(APTreeSVG)

Aptree: all $(INPUT) $(OUTPUT) $(EXECUTABLE) $(APTreeFile) $(APTreeSVG)  $(CERR)
	@echo "🚥 Starting C2RISC Engine 🟢 on -" $(INPUT)
	@-./$(EXECUTABLE) $(INPUT) -t -d2 $(APTreeFile) 2> $(CERR)
	@echo "🎄 APTree in - " $(APTreeSVG)
	@$(DOT) -Tsvg $(APTreeFile) -o $(APTreeSVG)
	@open $(APTreeSVG)

r: all $(EXECUTABLE) $(INPUT) $(OUTPUT)  $(CERR)
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) -r 2> $(CERR)

s: all $(EXECUTABLE) $(INPUT)  $(CERR)
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) -s 2> $(CERR)


# Clean generated files
clean:
	@rm -f $(LEXER_C) $(PARSER_C) $(PARSER_H) $(EXECUTABLE) \
	$(OBJ_DIR)/* $(BUILD_DIR)/* $(OUTPUT_DIR)/* $(BIN_DIR)/*

again:
	rm -f $(EXECUTABLE) \
		$(PARSER_C) \
		$(PARSER_H)
	make all


semantic: all $(EXECUTABLE) $(INPUT) $(OUTPUT)
	@echo "---------------------------------------------GCC Compilation---------------------------------------------"
	$(CC) -fsyntax-only $(INPUT) && echo "✅ Successfully Compiled by GCC"
	@echo "-------------------------------------------Our Syntax Analysis-------------------------------------------"
	@./$(EXECUTABLE) $(INPUT) -o $(OUTPUT) 2> $(CERR)
	

execute: all $(INPUT)
	$(CC) $(INPUT) -o $(BIN_DIR)/input_exec
	@./$(BIN_DIR)/input_exec

sem_ptree: all $(EXECUTABLE) $(INPUT) $(OUTPUT)  $(CERR)
	@echo "---------------------------------------GCC Compilation---------------------------------------"
	@-$(CC) -fsyntax-only $(INPUT) && echo "✅ Successfully Compiled by GCC"
	@echo "-------------------------------------------Our Syntax Analysis-------------------------------------------"
	@./$(EXECUTABLE) $(INPUT) -o $(OUTPUT) -d2 $(PTreeFile) 2> $(CERR)
	$(DOT) -Tpdf $(PTreeFile) -o $(PTreeSVG)

ASSEMBLY = $(OUTPUT_DIR)/assembly.s
LLVMIR = $(OUTPUT_DIR)/llvm_ir.ll

assembly: all $(INPUT) 
	@clang -S -target riscv32-unknown-elf -march=rv32i $(INPUT) -o $(ASSEMBLY)

llvm: all $(INPUT) 
	@clang -S -emit-llvm $(INPUT) -o $(LLVMIR)

astdump: all $(INPUT) 
	@clang -Xclang -ast-dump -fsyntax-only $(INPUT)

SYM_H = $(INCLUDE_DIR)/sym.h
SYM_CPP = $(SRC_DIR)/sym.cpp
SYM_TEST = $(SRC_DIR)/test_sym.cpp

SYM_TABLEFile = $(OUTPUT_DIR)/sym_table.txt

sym: all $(SYM_H) $(SYM_CPP) $(SYM_TEST) 
	$(CXX) $(UTILITY_CPP) $(SYM_CPP) $(SYM_TEST) -o $(BIN_DIR)/symTest $(CXXFLAGS) -I $(INCLUDE_DIR)
	@./$(BIN_DIR)/symTest $(SYM_TABLEFile)


UNIT_TEST = unit_testing.cpp

UNIT_TEST_EXECUTABLE = $(BIN_DIR)/unit_test

$(UNIT_TEST_EXECUTABLE): $(UNIT_TEST) $(EXECUTABLE)
	@echo "------- Making Unit Test -------"
	$(CXX) $(CXXFLAGS)  $(UNIT_TEST) $(OBJ_FILES) -o $(UNIT_TEST_EXECUTABLE)

unitTest: all $(UNIT_TEST_EXECUTABLE)
	@echo "------- Running Unit Test -------"
	./$(UNIT_TEST_EXECUTABLE)


IRCodeFile = $(OUTPUT_DIR)/IRCode.txt

$(IRCodeFile):
	@touch $(IRCodeFile)

irCode: all $(EXECUTABLE) $(INPUT) $(OUTPUT) $(CERR) $(IRCodeFile)
	@echo "🚥 Starting C2RISC Engine 🟢 "
	@-./$(EXECUTABLE) $(INPUT) -o $(IRCodeFile) -d2 $(APTreeFile) 2> $(CERR)
	@echo "🎄 APTree in - " $(APTreeSVG)
	@-$(DOT) -Tsvg $(APTreeFile) -o $(APTreeSVG)
	@open -a "Visual Studio Code" $(IRCodeFile)


testing: all $(EXECUTABLE) $(INPUT) $(OUTPUT) $(CERR)
	@echo "🚥 Starting C2RISC Engine 🟢 "
	@-./$(EXECUTABLE) $(INPUT) -t  2> $(CERR)
	@echo "Testing Over"

debugging: all $(EXECUTABLE) $(INPUT) $(OUTPUT) $(CERR)
	@echo "🚥 Starting C2RISC Engine 🟢 "
	@-./$(EXECUTABLE) $(INPUT) -t -d2 $(APTreeFile) 2> $(CERR)
	@echo "🎄 APTree in - " $(APTreeSVG)
	@-$(DOT) -Tsvg $(APTreeFile) -o $(APTreeSVG)