# C2RISC-Engine

This GitHub Repo is about our semester long project under the course CSN-352 *Compiler Design* 


## Compiler Specification
Source Language - `C` <br>
Target Machine/Arch - "RISC-V" <br>
Intermediate Representation - "Three Address Code" <br>
Implementation Language - `C++` <br>


## Features of C++ Supported
 TO WRITE


### Running Lexer

Steps 
- Make sure you have 'Flex' and 'g++' installed on your system
- RUN `$ flex lexer.l` ➾ Generates a `lex.yy.c` file
- RUN `$ g++ lex.yy.c -o lexer -w` ➾ Generates a `lexer` executable
- RUN `$ ./lexer <input_file>` ➾ This does a tokenization on <input_file> and stores output to `<input_base_name>_output.txt` and error stored to `<input_base_name>_error.txt`

#### Some Debugging Instructions
Global Variable
- DEBUGMODE ➾ Turn on to show comments as well
- SHOWERRORS ➾ Turn on to get error log to error file
- TESTMODE ➾ Set value > 0 to get some specific tokens only to output file | Helpful in Testing certain Token's validity

### Running Parser
TO BE MADE



