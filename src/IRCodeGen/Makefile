# Compiler and flags
CXX = g++ -std=c++17 # Added Latest Version [Some error due to old compiler]
CXXFLAGS = -w -lm

# Input and output files
INPUT = input.c
OUTPUT = output.txt
CERR = stderr.log

## for debug we have a console log

# Bison and Flex tools
BISON = bison -Wnone
FLEX = flex

# Source files
LEXER = lexer.l
PARSER = parser.y
UTILITY_H = utility.h
UTILITY_CPP = utility.cpp

# Generated files
LEXER_C = lex.yy.c
PARSER_C = parser.tab.c
PARSER_H = parser.tab.h
EXECUTABLE = parser

# Result dot (graphviz) tool
DOT = dot
DOTFile = ast_graph.dot
# DOTImage = ast_graph.png [Not used]
DOTPDF = ast_graph.pdf

#More Result FIle
S_EXPR = s_expr.txt
Recursive = recursive_output.txt

# #Result PARSER TABLE
# LaTeXFile = parser_table.tex
# LaTeX_OUTPUT = parser_table

#Txt File for the output
# TABLE = parser_table.txt


# Default target
all: $(EXECUTABLE)


# Step 1: Generate parser files from Bison
$(PARSER_C) $(PARSER_H): $(PARSER)
	$(BISON) -d $(PARSER)

# Step 2: Generate lexer file from Flex
$(LEXER_C): $(LEXER)
	$(FLEX) $(LEXER)

# Step 3: Compile everything together into an executable
$(EXECUTABLE): $(LEXER_C) $(PARSER_C) $(UTILITY_CPP) 
	$(CXX) $(LEXER_C) $(PARSER_C) $(UTILITY_CPP)  -o $(EXECUTABLE) $(CXXFLAGS)

$(CERR):
	touch $(CERR)

$(OUTPUT):
	touch $(OUTPUT)

run: $(EXECUTABLE) $(INPUT) $(OUTPUT) $(CERR)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) 2> $(CERR) 

# This will only run the parser and generate the output file [NO RESULT]


$(DOTFile): $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT) 

# PDF is better
# image: $(DOTFile)
# 	$(DOT) -Tpng $(DOTFile) -o $(DOTImage)

## For Visualizing the AST
ast: $(INPUT) $(OUTPUT) $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) -ast $(DOTFile) 2> $(CERR)
	$(DOT) -Tpdf $(DOTFile) -o $(DOTPDF)
	open $(DOTPDF)


r: $(EXECUTABLE) $(INPUT) $(OUTPUT)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) -r 2> $(CERR)

s: $(EXECUTABLE) $(INPUT)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) -s 2> $(CERR)

$(LaTeXFile): $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) 2> $(CERR)

# For PDF printing the Parser Table [Feature Not Needed in IR Code Gen]
# table: $(EXECUTABLE) $(INPUT) $(LaTeXFile)
# 	./$(EXECUTABLE) $(INPUT) $(OUTPUT) 2> $(CERR)
# 	pdflatex -jobname=$(LaTeX_OUTPUT) $(LaTeXFile) > /dev/null 2>&1
# 	open $(LaTeX_OUTPUT).pdf
	
# rm $(LaTeX_OUTPUT).aux $(LaTeX_OUTPUT).log 

# Clean generated files
clean:
	@rm -f $(LEXER_C) $(PARSER_C) $(PARSER_H) $(EXECUTABLE) $(OUTPUT) \
	$(CERR) $(DOTFile) $(DOTPDF) *.dot *.out \
	$(S_EXPR) $(Recursive)
	@# latexmk -CA > /dev/null 2>&1


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
	@gcc $(INPUT) -o runner && ./runner

sem_ast: $(EXECUTABLE) $(INPUT) $(OUTPUT)
	@echo "-------------------------------------------Our Syntax Analysis-------------------------------------------"
	@./$(EXECUTABLE) $(INPUT) $(OUTPUT) -ast $(DOTFile) 2> $(CERR)
	@echo "---------------------------------------GCC Compilation---------------------------------------"
	@-gcc -fsyntax-only $(INPUT) && echo "✅ Successfully Compiled by GCC"
	@$(DOT) -Tpdf $(DOTFile) -o $(DOTPDF)
	@open $(DOTPDF)

ASSEMBLY = input.s

assembly: $(INPUT)
	@clang -S -target riscv32-unknown-elf -march=rv32i $(INPUT) -o $(ASSEMBLY)


astdump: $(INPUT)
	@clang -Xclang -ast-dump -fsyntax-only $(INPUT)

SYM_H = sym.h
SYM_CPP = sym.cpp
SYM_TEST = test_sym.cpp

sym: $(SYM_H) $(SYM_CPP) $(SYM_TEST)
	$(CXX) $(UTILITY_CPP) $(SYM_CPP) $(SYM_TEST) -o sym -lm
	./sym