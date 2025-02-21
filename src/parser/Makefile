# Compiler and flags
CXX = g++ -std=c++17 # Added Latest Version [Some error due to old compiler]
CXXFLAGS = -w -lm

# Input and output files
INPUT = input.c
# OUTPUT to console
CERR = stderr.log
LEXLog = lexer.log
PARSERLog = parser.log

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
DOTFile = ast.dot
DOTImage = ast.png
DOTPDF = ast.pdf

#Result PARSER TABLE
PARSER_TABLE = parser_table.txt

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



run: $(EXECUTABLE) $(INPUT) 
	touch $(CERR)
	./$(EXECUTABLE) $(INPUT) 2> $(CERR)

$(DOTFile): $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT) -p $(DOTFile) 2> $(CERR)

# PDF is better
# image: $(DOTFile)
# 	$(DOT) -Tpng $(DOTFile) -o $(DOTImage)

pdf: $(DOTFile) $(INPUT)
	./$(EXECUTABLE) $(INPUT) -p $(DOTFile) 2> $(CERR)
	$(DOT) -Tpdf $(DOTFile) -o $(DOTPDF)
	open $(DOTPDF)

r: $(EXECUTABLE) $(INPUT)
	./$(EXECUTABLE) $(INPUT) -r $(VISUAL)

s: $(EXECUTABLE) $(INPUT)
	./$(EXECUTABLE) $(INPUT) -s $(S_EXPR)

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
		$(CERR) \
		$(LEXLog) \
		$(PARSERLog) \
		$(PARSER_TABLE)

again:
	rm -f $(EXECUTABLE) \
		$(PARSER_C) \
		$(PARSER_H)
	make all
	
