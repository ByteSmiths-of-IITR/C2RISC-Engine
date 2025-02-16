# Compiler and flags
CXX = g++
CXXFLAGS = -w -lm

# Bison and Flex tools
BISON = bison
FLEX = flex

# Source files
LEXER = lexer.l
PARSER = parser.y
MAIN = main.cc

# Generated files
LEXER_C = lex.yy.c
PARSER_C = parser.tab.c
PARSER_H = parser.tab.h
EXECUTABLE = parser

# Default target
all: $(EXECUTABLE)

# Step 1: Generate parser files from Bison
$(PARSER_C) $(PARSER_H): $(PARSER)
	$(BISON) -d $(PARSER)

# Step 2: Generate lexer file from Flex
$(LEXER_C): $(LEXER)
	$(FLEX) $(LEXER)

# Step 3: Compile everything into an executable
$(EXECUTABLE): $(LEXER_C) $(PARSER_C) $(MAIN)
	$(CXX) $(LEXER_C) $(PARSER_C) $(MAIN) -o $(EXECUTABLE) $(CXXFLAGS)

# Clean generated files
clean:
	rm -f $(LEXER_C) $(PARSER_C) $(PARSER_H) $(EXECUTABLE)
