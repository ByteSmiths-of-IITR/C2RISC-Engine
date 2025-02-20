# Compiler and flags
CXX = clang++
CXXFLAGS = -w -lm

# Input files
INPUT = input.c
OUTPUT = output.txt
CERR = cerr.txt

## for debug we have a console log

# Bison and Flex tools
BISON = bison
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
DOTFile = ast.dot
DOTImage = ast.png
DOTPDF = ast.pdf

# Result recursive print
VISUAL = visual.txt
S_EXPR = s_expr.txt

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

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) 2> $(CERR)

$(DOTFile): $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) -p $(DOTFile)

image: $(DOTFile)
	$(DOT) -Tpng $(DOTFile) -o $(DOTImage)

pdf: $(DOTFile)
	$(DOT) -Tpdf $(DOTFile) -o $(DOTPDF)

r: $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) -r $(VISUAL)

s: $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT) $(OUTPUT) -s $(S_EXPR)

# Clean generated files
clean:
	rm -f $(LEXER_C) \
		$(PARSER_C) \
		$(PARSER_H) \
		$(EXECUTABLE) \
		$(DOTFile) \
		$(DOTImage) \
		$(DOTPDF) \
		$(VISUAL) \
		$(S_EXPR) \
		$(OUTPUT)
