LEX = flex
# Autodetect compiler
CC := $(shell command -v clang++ 2>/dev/null || command -v g++ 2>/dev/null)

# Check if a compiler was found
ifeq ($(CC),)
$(error Neither clang++ nor g++ found on the system)
endif


LEX_FILE = lexer.l
LEX_GEN_C = lex.yy.c
EXECUTABLE = lexer

all: $(EXECUTABLE)

$(LEX_GEN_C): $(LEX_FILE)
	$(LEX) $(LEX_FILE)

$(EXECUTABLE): $(LEX_GEN_C)
	$(CXX) $(LEX_GEN_C) -w -o $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE) test.cpp


clean:
	rm -f $(LEX_GEN_C) $(EXECUTABLE)