%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "ast.h"  // Ensure this is included
// #include "sym.h" 

extern char *yytext;
extern int DEBUGMODE;
void yyerror(const char *s);
extern int yylex();
extern FILE *yyin;

#define YYDEBUG 1

ASTNode *root;

%}

%union {
    char *str;
    struct ASTNode *node;
}

%token <str> IDENTIFIER NUMBER
%token ASSIGN SEMICOLON 
%token <str> UNKNOWN

%type <node> statement statements

%%

statements:
    statement                 { 
        ASTNode *node = new ASTNode("statements"); 
        node->addChild($1);
        $$ = node;
        root = node;
    }
    | statements statement     { 
        ASTNode *node = new ASTNode("statements");
        node->addChild($1);
        node->addChild($2);
        $$ = node;
        root = node;
    }
    ;

statement:
    IDENTIFIER ASSIGN NUMBER SEMICOLON {
        ASTNode *node = new ASTNode("statement");
        node->createChild("IDENTIFIER", $1);
        node->createChild("ASSIGN", "="); // FIX: Corrected function name
        node->createChild("NUMBER", $3);
        node->createChild("SEMICOLON", ";");
        $$ = node;
        std::cout << "Assignment" << $1 << " = " << $3 << std::endl;
    }
    ;


%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}



// main function

int main(int argc, char **argv) {


    //------------------------ cmd line arguments handling ------------------------

        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> [-d<debug_mode>] [-p [<DOTFileName>] ] [-r <recursiveOutputFile]\n";
            return 1;
        }

        std::string input_file = argv[1];
        std::string output_file = argv[2];
        std::string debug_mode;
        std::string dot_file;
        std::string recursive_output_file;
        std::string SExp_file;

        // Parse arguments
        for (int i = 3; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg[0] == '-' && arg[1] == 'd') {
                // Debug mode flag in the form of "-d<debug_mode>"
                debug_mode = arg.substr(2); // Extract the debug mode value after "-d"

                // Set the debug mode
                DEBUGMODE = std::stoi(debug_mode);

            } else if (arg == "-p") {
                // Check if there is another argument after "-p"
                if (i + 1 < argc) {
                    dot_file = argv[++i]; // Assign the next argument as the DOT file
                } else {
                    // If name is not provided after "-p"
                    // Create a default name for the DOT file
                    std::string base_name = input_file.substr(0, input_file.find_last_of("."));
                    dot_file = base_name + ".dot";
                }
            }else if(arg == "-r"){
                // Check if there is another argument after "-r"
                if (i + 1 < argc) {
                    recursive_output_file = argv[++i]; // Assign the next argument as the recursive output file
                } else {
                    std::cerr << "2Error: Invalid argument.\n";
                    return 1;
                }
            } else if(arg == "-s"){
                // Check if there is another argument after "-s"
                if (i + 1 < argc) {
                    SExp_file = argv[++i]; // Assign the next argument as the SExp output file
                }
                else {
                    std::cerr << "1Error: Invalid argument.\n";
                    return 1;
                }
            } else {
                std::cerr << "4Error: Invalid argument.\n";
                return 1;
            }
        }


    //------------------------ input file handling ------------------------
        yyin = fopen(input_file.c_str(), "r");
        if (!yyin) {
            std::cerr << "E12rror: Unable to open input file.\n";
            return 1;
        }

        freopen(output_file.c_str(), "w", stdout); // stdout will be redirected to output file
        
        //------ToDo[Later]: Redirect cerr to error.txt file------
        // cerr is not redirected to output file it will be printed to console 
        // When we need to show parser errors to the user, we can use cerr to a error.txt file (not now)

    // ------------------------ Symbol Table ------------------------
        // Create a new symbol table
        /* SymbolTable *symTable = new SymbolTable(); */


    //------------------------ Parsing ------------------------

        std::cout << "..........Starting parsing..........\n";
        yyparse();  // Call BISON's parser
        std::cout << "..........Parsing complete..........\n";




    // ------------------------- Printing Various Outputs ------------------------
    
        // Print AST as DOT file
            if(!dot_file.empty()){
                generateDOT(root, dot_file);
            }

        // Print Recursive Output
            if(!recursive_output_file.empty()){
                printASTToFile(root, recursive_output_file);
            }    

        // Print S-Expression
            if(!SExp_file.empty()){
                writeASTToSExpression(root, SExp_file);
            }

        // Print Normal AST
            if(DEBUGMODE){
                printAST(root);
            }

    //------------------------- Cleanup ------------------------
        if (yyin) fclose(yyin);  // Close the input file if opened
        return 0;
}

