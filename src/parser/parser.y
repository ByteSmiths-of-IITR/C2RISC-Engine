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

%token <str> IDENTIFIER NUMBER STRING_LITERAL CHAR_LITERAL
%token ASSIGN SEMICOLON COMMA
%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token EQUAL NOT_EQUAL LESS GREATER LESS_EQUAL GREATER_EQUAL
%token AND OR NOT
%token IF ELSE WHILE DO FOR SWITCH CASE DEFAULT BREAK CONTINUE GOTO RETURN
%token INT CHAR VOID STRUCT STATIC
%token PRINTF SCANF
%token AMPERSAND LBRACKET RBRACKET LPAREN RPAREN LBRACE RBRACE COLON
%token UNKNOWN

//left and right shift
%left LEFT_SHIFT RIGHT_SHIFT

%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS GREATER LESS_EQUAL GREATER_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right NOT

%type <node> statements statement expression term factor 
%type <node> selection_statement iteration_statement jump_statement
%type <node>  function_call  argument_list
%type <node> declaration type_specifier array_declaration pointer_declaration
%type <node> structure_declaration
%type <node> function_definition

%%

statements:
    statement { $$ = new ASTNode("statements"); $$->addChild($1); root = $$; }
    | statements statement { $$ = $1; $$->addChild($2); }
;

statement:
    declaration SEMICOLON { $$ = $1; }
    | selection_statement { $$ = $1; }
    | iteration_statement { $$ = $1; }
    | jump_statement { $$ = $1; }
    | function_call SEMICOLON { $$ = $1; }
    | expression SEMICOLON { $$ = $1; }
    | function_definition { $$ = $1; }  // Add this line to include function definitions
;


declaration:
    type_specifier IDENTIFIER ASSIGN expression { $$ = new ASTNode("declaration"); $$->createChild("type", $1->type); $$->createChild("identifier", $2); $$->addChild($4); }
    | type_specifier IDENTIFIER { $$ = new ASTNode("declaration"); $$->createChild("type", $1->type); $$->createChild("identifier", $2); }
;


type_specifier:
    INT { $$ = new ASTNode("type"); $$->createChild("INT",""); }
    | CHAR { $$ = new ASTNode("type"); $$->createChild("CHAR",""); }
    | VOID { $$ = new ASTNode("type"); $$->createChild("VOID",""); }
    | STRUCT IDENTIFIER { $$ = new ASTNode("type"); $$->createChild("STRUCT", $2); }
    | STATIC type_specifier { $$ = new ASTNode("type"); $$->createChild("STATIC", ""); $$->addChild($2); }
    | type_specifier AMPERSAND { $$ = new ASTNode("type"); $$->createChild("POINTER", ""); $$->addChild($1); }
    | array_declaration { $$ = $1; }
;

selection_statement:
    IF LPAREN expression RPAREN statement ELSE statement { $$ = new ASTNode("if-else"); $$->addChild($3); $$->addChild($5); $$->addChild($7); }
    | IF LPAREN expression RPAREN statement { $$ = new ASTNode("if"); $$->addChild($3); $$->addChild($5); }
;

iteration_statement:
    WHILE LPAREN expression RPAREN statement { $$ = new ASTNode("while"); $$->addChild($3); $$->addChild($5); }
    | DO statement WHILE LPAREN expression RPAREN SEMICOLON { $$ = new ASTNode("do-while"); $$->addChild($2); $$->addChild($5); }
    | FOR LPAREN expression SEMICOLON expression SEMICOLON expression RPAREN statement { $$ = new ASTNode("for"); $$->addChild($3); $$->addChild($5); $$->addChild($7); $$->addChild($9); }
;

jump_statement:
    RETURN expression SEMICOLON { $$ = new ASTNode("return"); $$->addChild($2); }
    | BREAK SEMICOLON { $$ = new ASTNode("break"); }
    | CONTINUE SEMICOLON { $$ = new ASTNode("continue"); }
    | GOTO IDENTIFIER SEMICOLON { $$ = new ASTNode("goto"); $$->createChild("label", $2); }
;

expression:
    expression PLUS term { $$ = new ASTNode("+"); $$->addChild($1); $$->addChild($3); }
    | expression MINUS term { $$ = new ASTNode("-"); $$->addChild($1); $$->addChild($3); }
    | expression MULTIPLY term { $$ = new ASTNode("*"); $$->addChild($1); $$->addChild($3); }
    | expression DIVIDE term { $$ = new ASTNode("/"); $$->addChild($1); $$->addChild($3); }
    | expression MODULO term { $$ = new ASTNode("%"); $$->addChild($1); $$->addChild($3); }
    | expression EQUAL term { $$ = new ASTNode("=="); $$->addChild($1); $$->addChild($3); }
    | expression NOT_EQUAL term { $$ = new ASTNode("!="); $$->addChild($1); $$->addChild($3); }
    | expression LESS term { $$ = new ASTNode("<"); $$->addChild($1); $$->addChild($3); }
    | expression GREATER term { $$ = new ASTNode(">"); $$->addChild($1); $$->addChild($3); }
    | expression LESS_EQUAL term { $$ = new ASTNode("<="); $$->addChild($1); $$->addChild($3); }
    | expression GREATER_EQUAL term { $$ = new ASTNode(">="); $$->addChild($1); $$->addChild($3); }
    | expression AND term { $$ = new ASTNode("&&"); $$->addChild($1); $$->addChild($3); }
    | expression OR term { $$ = new ASTNode("||"); $$->addChild($1); $$->addChild($3); }
    | NOT term { $$ = new ASTNode("!"); $$->addChild($2); }
    | term { $$ = $1; }
;

term:
    term MULTIPLY factor { $$ = new ASTNode("*"); $$->addChild($1); $$->addChild($3); }
    | term DIVIDE factor { $$ = new ASTNode("/"); $$->addChild($1); $$->addChild($3); }
    | factor { $$ = $1; }
;

factor:
    NUMBER { $$ = new ASTNode("number"); $$->createChild("value", $1); }
    | IDENTIFIER { $$ = new ASTNode("identifier"); $$->createChild("name", $1); }
    | function_call { $$ = $1; }
    | LPAREN expression RPAREN { $$ = $2; }
;

function_call:
    IDENTIFIER LPAREN argument_list RPAREN { $$ = new ASTNode("function_call"); $$->createChild("name", $1); $$->addChild($3); }
    | IDENTIFIER LPAREN RPAREN { $$ = new ASTNode("function_call"); $$->createChild("name", $1); }
;

argument_list:
    expression { $$ = new ASTNode("arguments"); $$->addChild($1); }
    | argument_list COMMA expression { $$ = $1; $$->addChild($3); }
;

function_definition:
    type_specifier IDENTIFIER LPAREN RPAREN LBRACE statements RBRACE { $$ = new ASTNode("function_definition"); $$->createChild("return_type", $1->type); $$->createChild("name", $2); $$->addChild($6); }
;

array_declaration:
    type_specifier IDENTIFIER LBRACKET NUMBER RBRACKET { $$ = new ASTNode("array"); $$->createChild("type", $1->type); $$->createChild("name", $2); $$->createChild("size", $4); }
;

pointer_declaration:
    type_specifier AMPERSAND IDENTIFIER { $$ = new ASTNode("pointer"); $$->createChild("type", $1->type); $$->createChild("name", $3); }
;

structure_declaration:
    STRUCT IDENTIFIER LBRACE statements RBRACE { $$ = new ASTNode("structure"); $$->createChild("name", $2); $$->addChild($4); }
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

