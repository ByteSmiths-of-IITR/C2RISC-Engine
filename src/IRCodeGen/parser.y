%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>

#include "utility.h"  

#define EMPTY_VAL "!!EMPTY!!"


std::string whereWasILast;

#define TERMINAL_MESSAGE true // if you wish to check if successful parsing from terminal itself

bool TURN_OFF = true; // Turn off the custom error messages

int noOfyyerrorCalls = 0; 

// #define LINE std::cerr<< "Production - " << __LINE__<<std::endl;
#define LINE /**/
// #define LINE1 std::cerr<< __LINE__<<std::endl;
#define LINE1 /**/

#define PARSERLOGHEADER "----------------------------------- PARSER LOG -----------------------------------"
#define LOGFOOTER       "----------------------------------- END OF LOG -----------------------------------"
#define LEXERLOGHEADER  "----------------------------------- LEXER LOG ------------------------------------"
#define BISONLOGHEADER  "----------------------------------- BISON LOG ------------------------------------"

// Global DS 
std::vector<std::pair<std::pair<int,int>, std::pair<std::string, std::string>> > PARSER_TABLE;


// Handler Functions [Removed]
// void Struct_Union_Declaration_Handler(ASTNode* specifierQualifierList, ASTNode* declaratorList);
// void Enum_Declaration_Handler(ASTNode* enumSpecifier);
// void Function_Def_Handler(ASTNode* declarator);
// void Declaration_Handler(ASTNode* declarationSpecifiers, ASTNode* initDeclaratorList);


// Utility Functions
void printParserTable(std::ostream& out);
void writeLatexTable(std::ostream& out);


// Extern Variables
extern int yylineno;
extern char *yytext;
void yyerror(const char *s);
extern int yylex();
extern FILE *yyin;

extern std::vector<std::string> lexerLOG;
std::vector<std::string> parserLOG;
std::vector<std::string> bisonLOG;

extern std::string lastToken;

bool stopYYERROR = false;

bool customError = false;

std::ofstream* output = nullptr;  // Global pointer

#define YYDEBUG 1

// std::ofstream PARSERlog("parser.log", std::ios::trunc); // [[NOt in use]]

std::string getPosition(TokenAttribute* token){
    return std::to_string(token->position.first) + ":" + std::to_string(token->position.second);
}

std::string getPosition(ASTNode* node){
    return std::to_string(node->position.first) + ":" + std::to_string(node->position.second);
}


void ourError(const std::string& msg) {

    if(TURN_OFF){
        return;
    }

    std::string error = "Syntax Error at line " + std::to_string(yylineno) + " near token: " + lastToken;
    error += " | Error Description: " + msg;
    parserLOG.push_back(error);
}

void initOutputFile(const std::string& filename) {
    output = new std::ofstream(filename);
    if (!output->is_open()) {
        delete output;
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        output = nullptr;
    }
}

void closeOutputFile() {
    if (output) {
        output->close();
        delete output;
        output = nullptr;
    }
}

void signalHandler(int signum) {

    // Don't Think will be needed anymore [since we removed the handlerFunctions, which were cause of segFaults]


    *output << "\U0001F6A8 * Input Program failed in the PARSE stage \U0001F6A8" << std::endl;
    *output << "Where was I Last: " << whereWasILast << std::endl;
    *output << std::endl;
    // cerr the log
    *output << ((parserLOG.size() > 0) ? PARSERLOGHEADER : BISONLOGHEADER) << std::endl;
    for (auto& log : parserLOG) {
        *output << log << std::endl;
        // TODO ------------ Handle this [ Not printing the logs of parser ]
        if(parserLOG.size()==0){
            *output << "$(SignalHandler) Syntax Error at line " << yylineno << " near token: " << lastToken << std::endl;
        }
    }
    *output << LOGFOOTER << std::endl;
    *output << std::endl;

    *output << "--- No Further Processing will be done ---" << std::endl;
    closeOutputFile();
    exit(0); // Clean Exit
}


ASTNode *root;
%}

%union{
    struct TokenAttribute* tokenAtr;
    struct ASTNode* astNode;
}

%token <tokenAtr> IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token <tokenAtr> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token <tokenAtr> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token <tokenAtr> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token <tokenAtr> XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token <tokenAtr> LPAREN RPAREN LCURLY RCURLY LSQUARE RSQUARE
%token <tokenAtr> DOT COMMA BIT_AND STAR PLUS MINUS BIT_NOT NOT_OP DIVIDE MOD LESSER_OP GREATER_OP XOR BIT_OR QUESTION COLON SEMI_COLON ASSIGN
%token <tokenAtr> TYPEDEF EXTERN STATIC AUTO REGISTER
%token <tokenAtr> CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token <tokenAtr> VA_LIST
%token <tokenAtr> STRUCT UNION ENUM ELLIPSIS
%token <tokenAtr> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN UNTIL

%token <tokenAtr> INVALID_TOKEN UNKNOWN_TOKEN

%type <astNode> identifier constant semi_colon
%type <astNode> rparen rcurly rsquare

%type <astNode> primary_expression
%type <astNode> postfix_expression
%type <astNode> argument_expression_list
%type <astNode> unary_expression
%type <astNode> unary_operator
%type <astNode> cast_expression
%type <astNode> multiplicative_expression
%type <astNode> additive_expression
%type <astNode> shift_expression
%type <astNode> relational_expression
%type <astNode> equality_expression
%type <astNode> and_expression
%type <astNode> exclusive_or_expression
%type <astNode> inclusive_or_expression
%type <astNode> logical_and_expression
%type <astNode> logical_or_expression
%type <astNode> conditional_expression
%type <astNode> assignment_expression
%type <astNode> assignment_operator
%type <astNode> expression
%type <astNode> constant_expression
%type <astNode> declaration
%type <astNode> declaration_specifiers
%type <astNode> init_declarator_list
%type <astNode> init_declarator 
%type <astNode> storage_class_specifier
%type <astNode> type_specifier
%type <astNode> struct_or_union_specifier
%type <astNode> struct_or_union
%type <astNode> struct_declaration_list
%type <astNode> struct_declaration
%type <astNode> specifier_qualifier_list
%type <astNode> struct_declarator_list
%type <astNode> struct_declarator
%type <astNode> enum_specifier
%type <astNode> enumerator_list
%type <astNode> enumerator
%type <astNode> type_qualifier
%type <astNode> declarator
%type <astNode> direct_declarator
%type <astNode> pointer
%type <astNode> type_qualifier_list
%type <astNode> parameter_type_list
%type <astNode> parameter_list
%type <astNode> parameter_declaration
%type <astNode> identifier_list
%type <astNode> type_name
%type <astNode> abstract_declarator
%type <astNode> direct_abstract_declarator
%type <astNode> initializer
%type <astNode> initializer_list
%type <astNode> statement
%type <astNode> labeled_statement
%type <astNode> compound_statement
%type <astNode> declaration_list
%type <astNode> statement_list
%type <astNode> expression_statement
%type <astNode> selection_statement
%type <astNode> iteration_statement
%type <astNode> jump_statement
%type <astNode> translation_unit
%type <astNode> external_declaration
/* %type <astNode> function_declaration */
%type <astNode> function_definition

/* %expect-rr 96 */
/* %expect 2 */

%start translation_unit
%%


//////////////// Adding Error Production //////////////////////////////////////////////////////////


identifier
    : IDENTIFIER 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    | {stopYYERROR=true;} error 
        { 
            LINE
            $$ = new ASTNode("Error", "\U0001F6A8 Identifier");
            ourError("Expected an ID or Expression");
        }
    ;

constant 
    : CONSTANT 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    |{stopYYERROR=true;} error 
        { 
            LINE
            $$ = new ASTNode("Error", "\U0001F6A8 Constant");
            ourError("Expected a Constant or Expression");

        }
    ;

semi_colon
    : SEMI_COLON 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    | {stopYYERROR=true;} error 
        { 
            LINE
            // Program comes here after calling yy error()

            $$ = new ASTNode("Error", "\U0001F6A8 SemiColon");
            ourError("Expected a SemiColon");
            
        }
    ;

rparen
    : RPAREN 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    |{stopYYERROR=true;} error 
        { 
            LINE
            $$ = new ASTNode("Error", "\U0001F6A8 RParen");
            ourError("Expected a Right Parenthesis");

        }
    ;

rcurly
    : RCURLY 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    | {stopYYERROR=true;} error 
        { 
            LINE
            $$ = new ASTNode("Error", "\U0001F6A8 RCurly");
            ourError("Expected a Right Curly Brace");

        }
    ;

rsquare
    : RSQUARE 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    |{stopYYERROR=true;} error 
        { 
            LINE
            $$ = new ASTNode("Error", "\U0001F6A8 RSquare");
            ourError("Expected a Right Square Bracket");

        }
    ;



//////////////////////// TurnOff CustomErrors /////////////////////////////////////////////////////////////
/*

identifier
    : IDENTIFIER 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    ;

constant
    : CONSTANT 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    ;

semi_colon
    : SEMI_COLON 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    ;

rparen
    : RPAREN 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    ;

rcurly
    : RCURLY 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    ;   

rsquare
    : RSQUARE 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    ;   

*/
//////////////////////// ORIGINAL GRAMMAR ////////////////////////////////////////////////////////////////

primary_expression
    : identifier 
        {   
            LINE
            $$ = new ASTNode("primary_expression");
            $$->addChild($1);
        }
    | constant 
        { 
            LINE
            $$ = new ASTNode("primary_expression");
            $$->addChild($1);
        }
    | STRING_LITERAL 
        { 
            LINE
            $$ = new ASTNode("primary_expression");
            $$->addChild($1);
        }
    | LPAREN expression rparen 
        {   
            LINE
            $$ = new ASTNode("primary_expression");
            $$->addChild($1);
            $$->addChild($2);
            $$->addChild($3);
        }
    ;

postfix_expression
    : primary_expression 
    { 
        LINE
        $$ = $1;
    }
    | postfix_expression LSQUARE expression rsquare 
    { 
        LINE
        $$ = new ASTNode("postfix_expression");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    | postfix_expression LPAREN rparen 
    { 
        LINE
        $$ = new ASTNode("postfix_expression");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        //-
        //PARSER_TABLE.push_back({$1->position, {$1->value, "function call"}});
    }
    | postfix_expression LPAREN argument_expression_list rparen 
    { 
        LINE
        $$ = new ASTNode("postfix_expression");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    | postfix_expression DOT identifier 
    { 
        LINE
        $$ = new ASTNode("postfix_expression");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | postfix_expression PTR_OP identifier 
    { 
        LINE
        $$ = new ASTNode("postfix_expression");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | postfix_expression INC_OP 
    { 
        LINE
        $$ = new ASTNode("postfix_expression");
        $$->addChild($1);
        $$->addChild($2);
    }
    | postfix_expression DEC_OP 
    { 
        LINE
        $$ = new ASTNode("postfix_expression");
        $$->addChild($1);
        $$->addChild($2);
    }
    ;

argument_expression_list
    : assignment_expression 
    { 
        LINE
        $$ = new ASTNode("argument_expression_list");
        $$->addChild($1);
    }
    | argument_expression_list COMMA assignment_expression 
    { 
        LINE
        $$ = $1;
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

unary_expression
    : postfix_expression 
    { 
        LINE
        $$ = $1;
    }
    | INC_OP unary_expression 
    { 
        LINE
        $$ = new ASTNode("unary_expression");
        $$->addChild($1);
        $$->addChild($2);
    }
    | DEC_OP unary_expression 
    { 
        LINE
        $$ = new ASTNode("unary_expression");
        $$->addChild($1);
        $$->addChild($2);
    }
    | unary_operator cast_expression 
    { 
        LINE
        $$ = new ASTNode("unary_expression");
        $$->addChild($1);
        $$->addChild($2);
    }
    | SIZEOF unary_expression 
    { 
        LINE
        $$ = new ASTNode("unary_expression");
        $$->addChild($1);
        $$->addChild($2);
    }
    | SIZEOF LPAREN type_name rparen 
    { 
        LINE
        $$ = new ASTNode("unary_expression");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    ;

unary_operator
    : BIT_AND 
    {
        LINE 
        $$ = new ASTNode("unary_operator", $1->value);
    }
    | STAR 
    {
        LINE 
        $$ = new ASTNode("unary_operator", $1->value);
    }
    | PLUS 
    {
        LINE 
        $$ = new ASTNode("unary_operator", $1->value);
    }
    | MINUS 
    {
        LINE 
        $$ = new ASTNode("unary_operator", $1->value); 
    }
    | BIT_NOT 
    {
        LINE 
        $$ = new ASTNode("unary_operator", $1->value); 
    }
    | NOT_OP 
    {
        LINE 
        $$ = new ASTNode("unary_operator", $1->value); 
    }
    ;

cast_expression
    : unary_expression 
    { 
        LINE 
        $$ = $1;
    }
    | LPAREN type_name rparen cast_expression 
    { 
        LINE 
        $$ = new ASTNode("cast_expression");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    ;


multiplicative_expression
    : cast_expression 
    { 
        LINE
        $$ = $1;
    }
    | multiplicative_expression STAR cast_expression 
    { 
        LINE 
        $$ = new ASTNode("multiplicative_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    | multiplicative_expression DIVIDE cast_expression 
    { 
        LINE 
        $$ = new ASTNode("multiplicative_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    | multiplicative_expression MOD cast_expression 
    { 
        LINE 
        $$ = new ASTNode("multiplicative_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

additive_expression
    : multiplicative_expression 
    { 
        LINE 
        $$ = $1;
    }
    | additive_expression PLUS multiplicative_expression 
    { 
        LINE 
        $$ = new ASTNode("additive_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    | additive_expression MINUS multiplicative_expression 
    { 
        LINE 
        $$ = new ASTNode("additive_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

shift_expression
    : additive_expression 
    { 
        LINE 
        $$ = $1;
    }
    | shift_expression LEFT_OP additive_expression 
    { 
        LINE 
        $$ = new ASTNode("shift_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    | shift_expression RIGHT_OP additive_expression 
    { 
        LINE 
        $$ = new ASTNode("shift_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

relational_expression
    : shift_expression 
    { 
        LINE 
        $$ = $1;
    }
    | relational_expression LESSER_OP shift_expression 
    { 
        LINE 
        $$ = new ASTNode("relational_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    | relational_expression GREATER_OP shift_expression 
    { 
        LINE 
        $$ = new ASTNode("relational_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    | relational_expression LE_OP shift_expression 
    { 
        LINE 
        $$ = new ASTNode("relational_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    | relational_expression GE_OP shift_expression 
    { 
        LINE 
        $$ = new ASTNode("relational_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

equality_expression
    : relational_expression 
    { 
        LINE 
        $$ = $1;
    }
    | equality_expression EQ_OP relational_expression 
    { 
        LINE 
        $$ = new ASTNode("equality_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    | equality_expression NE_OP relational_expression 
    { 
        LINE 
        $$ = new ASTNode("equality_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

and_expression
    : equality_expression 
    { 
        LINE 
        $$ = $1;
    }
    | and_expression BIT_AND equality_expression 
    { 
        LINE 
        $$ = new ASTNode("and_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

exclusive_or_expression
    : and_expression 
    { 
        LINE 
        $$ = $1;
    }       
    | exclusive_or_expression XOR and_expression 
    { 
        LINE 
        $$ = new ASTNode("exclusive_or_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

inclusive_or_expression
    : exclusive_or_expression 
    { 
        LINE
        $$ = $1;
    }
    | inclusive_or_expression BIT_OR exclusive_or_expression 
    { 
        LINE 
        $$ = new ASTNode("inclusive_or_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

logical_and_expression
    : inclusive_or_expression 
    { 
        LINE 
        $$ = $1;
    }
    | logical_and_expression AND_OP inclusive_or_expression 
    { 
        LINE 
        $$ = new ASTNode("logical_and_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

logical_or_expression
    : logical_and_expression 
    { 
        LINE 
        $$ = $1;
    }
    | logical_or_expression OR_OP logical_and_expression 
    { 
        LINE 
        $$ = new ASTNode("logical_or_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

conditional_expression
    : logical_or_expression 
    { 
        LINE 
        $$ = $1;
    }
    | logical_or_expression QUESTION expression COLON conditional_expression 
    { 
        LINE
        $$ = new ASTNode("conditional_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($5);
    }
    ;

assignment_expression
    : conditional_expression 
    { 
        LINE 
        $$ = $1;
    }
    | unary_expression assignment_operator assignment_expression 
    { 
        LINE 
        $$ = new ASTNode("assignment_expression");
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

assignment_operator
    : ASSIGN 
    { 
        LINE 
        $$ = new ASTNode("assignment_operator", $1->value);
    }
    | MUL_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode("assignment_operator", $1->value);;
    }
    | DIV_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode("assignment_operator", $1->value);;
    }
    | MOD_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode("assignment_operator", $1->value);;
    }
    | ADD_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode("assignment_operator", $1->value);
    }
    | SUB_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode("assignment_operator", $1->value);
    }
    | LEFT_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode("assignment_operator", $1->value);
    }
    | RIGHT_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode("assignment_operator", $1->value);
    }
    | AND_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode("assignment_operator", $1->value);
    }
    | XOR_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode("assignment_operator", $1->value);
    }
    | OR_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode("assignment_operator", $1->value);
    }
    ;


expression
    : assignment_expression 
    { 
        LINE
        $$ = $1;
    }
    | expression COMMA assignment_expression 
    { 
        LINE
        $$ = new ASTNode("expression"); 
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

constant_expression
    : conditional_expression 
    {
        LINE
        // $$ = new ASTNode("constant_expression");
        // $$->addChild($1);
        // ShortHand
        $$ = $1;
    }
    ;

declaration
    : declaration_specifiers semi_colon 
    { 
        LINE 
        $$ = new ASTNode("declaration"); 
        $$->addChild($1); 
        $$->addChild($2);
    }
    | declaration_specifiers init_declarator_list semi_colon 
    { 
        LINE
        $$ = new ASTNode("declaration"); 
        $$->addChild($1);  
        $$->addChild($2);
        $$->addChild($3);
        // Declaration_Handler($1, $2);
    }
    ;

declaration_specifiers
    : storage_class_specifier 
    { 
        LINE
        $$ = new ASTNode("declaration_specifiers");
        $$->addChild($1);
    }
    | storage_class_specifier declaration_specifiers 
    { 
        LINE
        $$ = new ASTNode("declaration_specifiers");
        $$->addChild($1);
        $$->addChildren($2->children);
    }
    | type_specifier 
    { 
        LINE
        $$ = new ASTNode("declaration_specifiers");
        $$->addChild($1);
    }
    | type_specifier declaration_specifiers 
    { 
        LINE
        $$ = new ASTNode("declaration_specifiers");
        $$->addChild($1);
        $$->addChildren($2->children);
    }
    | type_qualifier 
    { 
        LINE
        $$ = new ASTNode("declaration_specifiers");
        $$->addChild($1);
    }
    | type_qualifier declaration_specifiers 
    { 
        LINE
        $$ = new ASTNode("declaration_specifiers");
        $$->addChild($1);
        $$->addChildren($2->children);
    }
    ;

init_declarator_list
    : init_declarator 
    {
        LINE
        $$ = new ASTNode("init_declarator_list");
        $$->addChild($1); 
    }
    | init_declarator_list COMMA init_declarator
    {
        LINE
        $$ = $1;
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

init_declarator
    : declarator 
    {
        LINE  
        $$ = new ASTNode("init_declarator");
        $$->addChild($1); 
    }
    | declarator ASSIGN initializer 
    {
        LINE 
        $$ = new ASTNode("init_declarator"); 
        $$->addChild($1); 
        $$->addChild($2); 
        $$->addChild($3); 
    }
    ;

storage_class_specifier
    : /*TYPEDEF 
    {
        LINE 
        $$ = new ASTNode("storage_class_specifier");
        $$->addChild($1);
    }
    |*/ EXTERN 
    {
        LINE 
        $$ = new ASTNode("storage_class_specifier");
        $$->addChild($1);    
    }
    | STATIC 
    {
        LINE 
        $$ = new ASTNode("storage_class_specifier");
        $$->addChild($1);    
    }
    | AUTO 
    {
        LINE 
        $$ = new ASTNode("storage_class_specifier");
        $$->addChild($1);    
    }
    | REGISTER 
    {
        LINE 
        $$ = new ASTNode("storage_class_specifier");
        $$->addChild($1);    
    }
    ;

type_specifier
    : VA_LIST 
    {
        LINE 
        $$ = new ASTNode("type_specifier", $1->value);
    }
    | VOID 
    {
        LINE
        $$ = new ASTNode("type_specifier", $1->value);
    }
    | CHAR 
    {
        LINE
        $$ = new ASTNode("type_specifier", $1->value);
    }
    | SHORT 
    {
        LINE 
        $$ = new ASTNode("type_specifier", $1->value);
    }
    | INT 
    {
        LINE 
        $$ = new ASTNode("type_specifier", $1->value);
    }
    | LONG 
    {
        LINE 
        $$ = new ASTNode("type_specifier", $1->value);
    }
    | FLOAT 
    {
        LINE
        $$ = new ASTNode("type_specifier", $1->value);
    }
    | DOUBLE 
    {
        LINE
        $$ = new ASTNode("type_specifier", $1->value);
    }
    | SIGNED 
    {
        LINE
        $$ = new ASTNode("type_specifier", $1->value);
    }
    | UNSIGNED 
    {
        LINE
        $$ = new ASTNode("type_specifier", $1->value);
    }
    | struct_or_union_specifier 
    {
        LINE
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
    }
    | enum_specifier 
    {
        LINE 
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
    }
    | TYPE_NAME 
    {
        LINE 
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
    }
    ;

struct_or_union_specifier
    : struct_or_union identifier LCURLY struct_declaration_list rcurly 
    {
        LINE 
        $$ = new ASTNode("struct_or_union_specifier");
        $$->addChild($1);
        $$->addChild(new ASTNode("struct_UnionID", $2->value));
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($5);
        PARSER_TABLE.push_back({$2->position, {$2->value, $1->value}});
    }
    | struct_or_union LCURLY struct_declaration_list rcurly 
    {
        LINE 
        $$ = new ASTNode("struct_or_union_specifier");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    | struct_or_union identifier 
    {
        LINE 
        $$ = new ASTNode("struct_or_union_specifier");
        $$->addChild($1);
        $$->addChild(new ASTNode("struct_UnionID", $2->value));
        PARSER_TABLE.push_back({$2->position, {$2->value, $1->value}});
    }
    ;

struct_or_union
    : STRUCT 
    {
        LINE 
        $$ = new ASTNode("Struct", "struct");
    }
    | UNION 
    {
        LINE 
        $$ = new ASTNode("Union", "union");
    }
    ;

struct_declaration_list
    : struct_declaration 
    {
        LINE 
        $$ = new ASTNode("struct_declaration_list");
        $$->addChild($1);
    }
    | struct_declaration_list struct_declaration 
    {
        LINE 
        $$ = $1;
        $$->addChild($2);
    }
    ;

struct_declaration
    : specifier_qualifier_list struct_declarator_list semi_colon 
    {
        LINE 
        $$ = new ASTNode("struct_declaration");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        // Struct_Union_Declaration_Handler($1, $2);
    }
    ;

specifier_qualifier_list
    : type_specifier specifier_qualifier_list
    {
        LINE
        $$ = new ASTNode("specifier_qualifier_list");
        $$->addChild($1);
        $$->addChildren($2->children);
    }
    | type_specifier
    {
        LINE
        $$ = new ASTNode("specifier_qualifier_list");
        $$->addChild($1);
    }
    | type_qualifier specifier_qualifier_list
    {
        LINE
        $$ = new ASTNode("specifier_qualifier_list");
        $$->addChild($1);
        $$->addChildren($2->children);
    }
    | type_qualifier
    {
        LINE
        $$ = new ASTNode("specifier_qualifier_list");
        $$->addChild($1);
    }
    ;

struct_declarator_list
    : struct_declarator 
    { 
        LINE 
        $$ = new ASTNode("struct_declarator_list");
        $$->addChild($1);
    }
    | struct_declarator_list COMMA struct_declarator 
    { 
        LINE 
        $$ = $1;
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

struct_declarator
    : declarator 
    { 
        LINE 
        $$ = new ASTNode("struct_declarator");
        $$->addChild($1);
    }
    | COLON constant_expression 
    { 
        LINE 
        $$ = new ASTNode("struct_declarator");
        $$->addChild($1);
        $$->addChild($2);
    }
    | declarator COLON constant_expression 
    { 
        LINE 
        $$ = new ASTNode("struct_declarator");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

enum_specifier
    : ENUM LCURLY enumerator_list rcurly 
    { 
        LINE 
        $$ = new ASTNode("enum_specifier");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        // Enum_Declaration_Handler($$);
    }
    | ENUM identifier LCURLY enumerator_list rcurly 
    { 
        LINE 
        $$ = new ASTNode("enum_specifier");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($5);
        // Enum_Declaration_Handler($$);
    }
    | ENUM identifier 
    { 
        LINE 
        $$ = new ASTNode("enum_specifier");
        $$->addChild($1);
        $$->addChild($2);
        // Enum_Declaration_Handler($$);
    }
    ;



enumerator_list
    : enumerator 
    {
        LINE 
        $$ = new ASTNode("enumerator_list");
        $$->addChild($1);
    }
    | enumerator_list COMMA enumerator 
    {
        LINE 
        $$ = $1;
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

enumerator
    : identifier 
    { 
        LINE 
        $$ = new ASTNode("enumerator");
        $$->addChild($1);
    }
    | identifier ASSIGN constant_expression 
    { 
        LINE 
        $$ = new ASTNode("enumerator");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

type_qualifier
    : CONST
    {
        LINE
        $$ = new ASTNode("type_qualifier");
        $$->addChild($1);
    }
    | VOLATILE
    {
        LINE
        $$ = new ASTNode("type_qualifier");
        $$->addChild($1);
    }
    ;

declarator
    : pointer direct_declarator
    {
        LINE
        $$ = new ASTNode("declarator");
        $$->addChild($1); 
        $$->addChild($2); 
    }
    | direct_declarator
    {
        LINE
        $$ = new ASTNode("declarator");
        $$->addChild($1);
    }
    ;

direct_declarator
    : identifier
    {
        LINE
        $$ = new ASTNode("direct_declarator");
        $$->addChild($1);
    }
    | LPAREN declarator rparen
    {
        LINE
        $$ = new ASTNode("direct_declarator");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | direct_declarator LSQUARE constant_expression rsquare
    {
        LINE
        $$ = new ASTNode("direct_declarator");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    | direct_declarator LSQUARE rsquare
    {
        LINE
        $$ = new ASTNode("direct_declarator");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | direct_declarator LPAREN parameter_type_list rparen
    {
        LINE
        $$ = new ASTNode("direct_declarator");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    | direct_declarator LPAREN identifier_list rparen
    {
        LINE
        $$ = new ASTNode("direct_declarator");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    | direct_declarator LPAREN rparen
    {
        LINE
        $$ = new ASTNode("direct_declarator");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

pointer
    : STAR
    {
        LINE
        $$ = new ASTNode("pointer");
        $$->addChild($1);
    }
    | STAR type_qualifier_list
    {
        LINE
        $$ = new ASTNode("pointer");
        $$->addChild($1);
        $$->addChild($2);
    }
    | STAR pointer
    {
        LINE
        $$ = new ASTNode("pointer");
        $$->addChild($1);
        $$->addChild($2);
    }
    | STAR type_qualifier_list pointer
    {
        LINE
        $$ = new ASTNode("pointer");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

type_qualifier_list
    : type_qualifier
    {
        LINE
        $$ = new ASTNode("type_qualifier_list");
        $$->addChild($1);
    }
    | type_qualifier_list type_qualifier
    {
        LINE
        $$ = $1;
        $$->addChild($2);
    }
    ;

parameter_type_list
    : parameter_list 
    { 
        LINE 
        $$ = new ASTNode("parameter_type_list");
        $$->addChild($1); 
    }
    | parameter_list COMMA ELLIPSIS 
    { 
        LINE 
        $$ = new ASTNode("parameter_type_list");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

parameter_list
    : parameter_declaration 
    { 
        LINE 
        $$ = new ASTNode("parameter_list");
        $$->addChild($1); 
    }
    | parameter_list COMMA parameter_declaration 
    { 
        LINE 
        $$ = $1;
        $$->addChild($2);
        $$->addChild($3);
    }
    ;


parameter_declaration
    : declaration_specifiers declarator
    {
        LINE
        $$ = new ASTNode("parameter_declaration");
        $$->addChild($1); 
        $$->addChild($2);  
    }
    | declaration_specifiers abstract_declarator
    {
        LINE
        $$ = new ASTNode("parameter_declaration");
        $$->addChild($1);  
        $$->addChild($2);  
    }
    | declaration_specifiers
    {
        LINE
        $$ = new ASTNode("parameter_declaration");
        $$->addChild($1); 
    }
    ;

identifier_list
    : identifier 
    { 
        LINE 
        $$ = new ASTNode("identifier_list");
        $$->addChild($1);
    }
    | identifier_list COMMA identifier 
    { 
        LINE 
        $$ = $1; 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

type_name
    : specifier_qualifier_list 
    { 
        LINE 
        $$ = new ASTNode("type_name");
        $$->addChild($1); 
    }
    | specifier_qualifier_list abstract_declarator 
    { 
        LINE 
        $$ = new ASTNode("type_name");
        $$->addChild($1); 
        $$->addChild($2); 
    }
    ;

abstract_declarator
    : pointer 
    { 
        LINE 
        $$ = new ASTNode("abstract_declarator");
        $$->addChild($1); 
    }
    | direct_abstract_declarator 
    { 
        LINE 
        $$ = new ASTNode("abstract_declarator");
        $$->addChild($1); 
    }
    | pointer direct_abstract_declarator 
    { 
        LINE 
        $$ = new ASTNode("abstract_declarator");
        $$->addChild($1); 
        $$->addChild($2); 
    }
    ;

direct_abstract_declarator
    : LPAREN abstract_declarator rparen
    {
        LINE
        $$ = new ASTNode("direct_abstract_declarator");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | LSQUARE rsquare
    {
        LINE
        $$ = new ASTNode("direct_abstract_declarator");
        $$->addChild($1);
        $$->addChild($2);
    }
    | LSQUARE constant_expression rsquare
    {
        LINE
        $$ = new ASTNode("direct_abstract_declarator");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | direct_abstract_declarator LSQUARE rsquare
    {
        LINE
        $$ = $1;  
        $$->addChild($2);
        $$->addChild($3);
    }
    | direct_abstract_declarator LSQUARE constant_expression rsquare
    {
        LINE
        $$ = $1;  
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    | LPAREN rparen
    {
        LINE
        $$ = new ASTNode("direct_abstract_declarator");
        $$->addChild($1);
        $$->addChild($2);
    }
    | LPAREN parameter_type_list rparen
    {
        LINE
        $$ = new ASTNode("direct_abstract_declarator");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | direct_abstract_declarator LPAREN rparen
    {
        LINE
        $$ = $1; 
        $$->addChild($2);
        $$->addChild($3);
    }
    | direct_abstract_declarator LPAREN parameter_type_list rparen
    {
        LINE
        $$ = $1; 
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    ;

initializer
    : assignment_expression
    {
        LINE
        $$ = new ASTNode("initializer");
        $$->addChild($1);
    }
    | LCURLY initializer_list rcurly
    {
        LINE
        $$ = new ASTNode("initializer");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | LCURLY initializer_list COMMA rcurly
    {
        LINE
        $$ = new ASTNode("initializer");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    ;

initializer_list
    : initializer 
    { 
        LINE 
        $$ = new ASTNode("initializer_list");
        $$->addChild($1); 
    }
    | initializer_list COMMA initializer 
    { 
        LINE 
        $$ = $1; 
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

statement
    : labeled_statement 
    { 
        LINE 
        $$ = new ASTNode("statement");
        $$->addChild($1); 
    }
    | compound_statement 
    { 
        LINE 
        $$ = new ASTNode("statement");
        $$->addChild($1); 
    }
    | expression_statement 
    { 
        LINE 
        $$ = new ASTNode("statement");
        $$->addChild($1); 
    }
    | selection_statement 
    { 
        LINE 
        $$ = new ASTNode("statement");
        $$->addChild($1); 
    }
    | iteration_statement 
    { 
        LINE 
        $$ = new ASTNode("statement");
        $$->addChild($1); 
    }
    | jump_statement 
    { 
        LINE 
        $$ = new ASTNode("statement");
        $$->addChild($1); 
    }
    | declaration 
    { 
        LINE 
        $$ = new ASTNode("statement");
        $$->addChild($1); 
    }
    ;

labeled_statement
    : identifier COLON statement
    {
        LINE
        $$ = new ASTNode("labeled_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | CASE constant_expression COLON statement
    {
        LINE
        $$ = new ASTNode("labeled_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    | DEFAULT COLON statement
    {
        LINE
        $$ = new ASTNode("labeled_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

compound_statement
    : LCURLY rcurly 
    { 
        LINE 
        $$ = new ASTNode("compound_statement");
        $$->addChild($1);
        $$->addChild($2);
    }
    | LCURLY statement_list rcurly 
    { 
        LINE 
        $$ = new ASTNode("compound_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | LCURLY declaration_list rcurly 
    { 
        LINE 
        $$ = new ASTNode("compound_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | LCURLY declaration_list statement_list rcurly 
    { 
        LINE 
        $$ = new ASTNode("compound_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    ;

declaration_list
    : declaration 
    { 
        LINE 
        $$ = new ASTNode("declaration_list");
        $$->addChild($1); 
    }
    | declaration_list declaration 
    { 
        LINE 
        $$ = $1; 
        $$->addChild($2); 
    }
    ;

//-----
statement_list
    : statement 
    { 
        LINE 
        $$ = new ASTNode("statement_list"); 
        $$->addChild($1); 
    }
    | statement_list statement 
    { 
        LINE 
        $$ = $1;
        $$->addChild($2); 
    }
    ;

expression_statement
    : semi_colon 
    { 
        LINE 
        $$ = new ASTNode("expression_statement"); 
        $$->addChild($1);
    }
    | expression semi_colon 
    { 
        LINE 
        $$ = new ASTNode("expression_statement");
        $$->addChild($1);
        $$->addChild($2);
    }
    ;

selection_statement
    : IF LPAREN expression rparen statement 
    { 
        LINE 
        $$ = new ASTNode("selection_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3); 
        $$->addChild($4);
        $$->addChild($5); 
    }
    | IF LPAREN expression rparen statement ELSE statement 
    { 
        LINE 
        $$ = new ASTNode("selection_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3); 
        $$->addChild($4);
        $$->addChild($5); 
        $$->addChild($6);
        $$->addChild($7); 
    }
    | SWITCH LPAREN expression rparen statement 
    { 
        LINE 
        $$ = new ASTNode("selection_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3); 
        $$->addChild($4);
        $$->addChild($5); 
    }
    ;

iteration_statement
    : WHILE LPAREN expression rparen statement 
    { 
        LINE 
        $$ = new ASTNode("iteration_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3); 
        $$->addChild($4);
        $$->addChild($5); 
    }
    | UNTIL LPAREN expression rparen statement 
    { 
        LINE 
        $$ = new ASTNode("iteration_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3); 
        $$->addChild($4);
        $$->addChild($5); 
    }
    | DO statement WHILE LPAREN expression rparen semi_colon 
    { 
        LINE 
        $$ = new ASTNode("iteration_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3); 
        $$->addChild($4);
        $$->addChild($5); 
        $$->addChild($6);
        $$->addChild($7); 
    }
    | FOR LPAREN expression_statement expression_statement rparen statement 
    { 
        LINE 
        $$ = new ASTNode("iteration_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3); 
        $$->addChild($4);
        $$->addChild($5); 
        $$->addChild($6); 
    }
    | FOR LPAREN expression_statement expression_statement expression rparen statement 
    { 
        LINE 
        $$ = new ASTNode("iteration_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3); 
        $$->addChild($4);
        $$->addChild($5); 
        $$->addChild($6);
        $$->addChild($7); 
    }
    | FOR LPAREN declaration expression_statement expression rparen statement 
    { 
        LINE 
        $$ = new ASTNode("iteration_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3); 
        $$->addChild($4);
        $$->addChild($5); 
        $$->addChild($6);
        $$->addChild($7); 
    }
    ;

jump_statement
    : GOTO identifier semi_colon 
    { 
        LINE 
        $$ = new ASTNode("jump_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | CONTINUE semi_colon 
    { 
        LINE 
        $$ = new ASTNode("jump_statement");
        $$->addChild($1);
        $$->addChild($2);
    }
    | BREAK semi_colon 
    { 
        LINE 
        $$ = new ASTNode("jump_statement");
        $$->addChild($1);
        $$->addChild($2);
    }
    | RETURN semi_colon 
    { 
        LINE 
        $$ = new ASTNode("jump_statement");
        $$->addChild($1);
        $$->addChild($2);
    }
    | RETURN expression semi_colon 
    { 
        LINE 
        $$ = new ASTNode("jump_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    ;


// START
translation_unit
    : external_declaration 
    { 
        LINE 
        $$ = new ASTNode("translation_unit");
        $$->addChild($1);
        root = $$;
    }
    | translation_unit external_declaration 
    { 
        LINE 
        $$ = $1;
        $$->addChild($2); 
        root = $$;
    }
    /* | error { yyerrok; } */
    ;

external_declaration
    : function_definition 
    { 
        LINE 
        $$ = new ASTNode("external_declaration");
        $$->addChild($1); 
    }
    | declaration 
    { 
        LINE 
        $$ = new ASTNode("external_declaration");
        $$->addChild($1); 
    }
    /* | error { yyerrok; } */
    ;

function_definition
    : // This in not supported [ToHandle]
    declaration_specifiers declarator declaration_list compound_statement 
    { 
        LINE  
        $$ = new ASTNode("function_definition"); 
        $$->addChild($2); 
        $$->addChild($3);
        $$->addChild($4); 
    }
    | 
    declaration_specifiers declarator compound_statement 
    { 
        LINE
        $$ = new ASTNode("function_definition"); 
        $$->addChild($1);
        $$->addChild($2); 
        $$->addChild($3); 
        // Function_Def_Handler($2);
    }
    //This is Depriecated [ToHandle]
    | declarator declaration_list compound_statement 
    { 
        LINE
        $$ = new ASTNode("function_definition"); 
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3); 
    } 
    // This is Depriecated [ToHandle]
    | declarator compound_statement 
    { 
        LINE
        $$ = new ASTNode("function_definition"); 
        $$->addChild($1); 
        $$->addChild($2); 
    }
    ;

%%


// main function

int main(int argc, char **argv) {
    whereWasILast = "main";

    signal(SIGSEGV, signalHandler); // Catch segmentation fault

    //------------------------ cmd line arguments handling ------------------------

        std::string inputInstructions = "Usage: " + std::string(argv[0]) + " <input_file> <output_file> [-ast <dot_file>] [-r] [-pt] [-s] \n";
        inputInstructions += "Options: \n";
        inputInstructions += "[-ast <dot_file>] : Generate AST as DOT file\n";
        inputInstructions += "[-r] : Generate Recursive Output\n";
        inputInstructions += "[-pt <parser_table_file>] : Generate Parser Table\n";
        inputInstructions += "[-s <SExp_file>] : Generate S-Expression\n";

        /* std::cout << "argc: " << argc << std::endl; */
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> [-ast <dot_file>] [-r] [-pt] [-s] \n";
            return 1;
        }

        std::string input_file = argv[1];
        std::string output_file = argv[2];
        std::string dot_file = "ast_graph.dot";
        std::string recursive_output_file = "recursive_output.txt";
        std::string parser_table_file = "parser_table.txt";
        std::string SExp_file = "SExp.txt";
        std::string LaTeXParserTable = "parser_table.tex";    

        bool ast_flag = false;
        bool recursive_flag = false;
        bool parser_table_flag = false;
        bool SExp_flag = false;

        // Open default output file
        yyin = fopen(input_file.c_str(), "r");
        if (!yyin) {
            std::cerr << "Error: Unable to open input file\n";
            return 1;
        }
        LINE
        initOutputFile(output_file); // open output file

        LINE

        // Parse command line arguments
        for (int i = 3; i < argc; i++) {
            if (std::string(argv[i]) == "-ast") {
                ast_flag = true;
                if (i + 1 < argc) {
                    dot_file = argv[i + 1];
                    i++;
                } else {
                    std::cerr << "Error: Missing argument for -ast\n";
                    std::cerr << inputInstructions;
                    return 1;
                }
            } else if (std::string(argv[i]) == "-r") {
                recursive_flag = true;
            } else if (std::string(argv[i]) == "-pt") {
                std::cerr << "This feature is Removed\n";
                return 0;
                /* parser_table_flag = true; */
                
            } else if (std::string(argv[i]) == "-s") {
                SExp_flag = true;
            } else {
                std::cerr << "Error: Invalid argument\n";
                std::cerr << inputInstructions;
                return 1;
            }
        }

    // ------------------------ Symbol Table ------------------------
        // Create a new symbol table
        /* SymbolTable *symTable = new SymbolTable(); */

    LINE
    //------------------------ Parsing ------------------------

    yyparse();  // Call BISON's parser
    
    LINE
    // ------------------------- Parser Phase Completion Checks ------------------------

    bool lexerFailed = (lexerLOG.size() > 0);

    bool parseError = (parserLOG.size() > 0);
    bool bisonError = (bisonLOG.size() > 0);

    bool syntaxError = parseError || lexerFailed || bisonError;

    if(lexerFailed){
        *output << "\U0001F6A8 Input Program failed in Lexical Analysis Phase \U0001F6A8\n" << std::endl;
        if(TERMINAL_MESSAGE){
            std::cout << "\U0001F6A8 Input Program failed in Lexical Analysis Phase \U0001F6A8" << std::endl;
        }
        
        *output << LEXERLOGHEADER << std::endl;
        for(auto log : lexerLOG){
            *output << log << std::endl;
        }
        *output << LOGFOOTER << std::endl;
        *output << std::endl;

        *output << "----No Further Processing----\n";
        // Clean Up
        fclose(yyin);
        closeOutputFile();
        return 0;
    }

    if(syntaxError){
        *output << "\U0001F6A8 Input Program failed in Syntax Analysis Phase \U0001F6A8\n" << std::endl;
        
        *output << "\U0001F6A8 yyerror() was called " << noOfyyerrorCalls << " times \U0001F6A8\n" << std::endl;

        if(TERMINAL_MESSAGE){
            std::cout << "\U0001F6A8 Input Program failed in Syntax Analysis Phase \U0001F6A8" << std::endl;
        }

        // We print ourCustom Error Only if Bison-don't Report any Error

        if(parseError && !TURN_OFF){
            *output << PARSERLOGHEADER << std::endl;
            for(auto log : parserLOG){
                *output << log << std::endl;
            }

            *output << LOGFOOTER << std::endl;
            *output << std::endl;
        }
        
        if(bisonError){
            *output << BISONLOGHEADER << std::endl;
            for(auto log : bisonLOG){
                *output << log << std::endl;
            }
            *output << LOGFOOTER << std::endl;
        }
        
        *output << std::endl;

        if(!bisonError){
            *output << "----No Further Processing----\n";

        // If we only have custom error - i.e no bison error then we can print the AST
            // Clean Up
            fclose(yyin);
            closeOutputFile();
            return 0; // For now even if there is a syntax error, we will continue to print the AST
        }
    }
    LINE

    // Success message
    
    if(!syntaxError){
        *output << "\U0001F44D Input Program passed Syntax Analysis Phase \U0001F44D\n" << std::endl;

        if(TERMINAL_MESSAGE){
            std::cout << "\U0001F44D Input Program passed Syntax Analysis Phase \U0001F44D" << std::endl;
        }
    }
    // ------------------------- Printing Various Outputs ------------------------

    if(ast_flag){
        // Print AST to DOT file
        generateDOT(root, dot_file);
        *output << "\U0001F53A AST generated as DOT file: " << dot_file << " can be visualized using Graphviz\n";
    }

    if(recursive_flag){
        // Print Recursive Output
        printASTToFile(root, recursive_output_file);
        *output << "\U0001F53A Recursive Output generated as: " << recursive_output_file << "\n";
    }

    if(SExp_flag){
        // Print S-Expression
        writeASTToSExpression(root, SExp_file);
        *output << "\U0001F53A S-Expression generated as: " << SExp_file << "\n";
    }

    if(parser_table_flag){
        // Print Parser Table
        std::ofstream parser_table;
        parser_table.open(parser_table_file);
        printParserTable(parser_table);
        parser_table.close();
        *output << "\U0001F53A Parser Table (TXT) generated as: " << parser_table_file << "\n";
    }
    LINE

    // Removing PARSE_TABLE
    /* // MUST PRINT PARSER_LaTeX_TABLE
    std::ofstream LaTeXTable;
    LaTeXTable.open(LaTeXParserTable);
    writeLatexTable(LaTeXTable);
    LaTeXTable.close();
    *output << "\U00002B55 Parser Table (LaTeX) generated as: " << LaTeXParserTable << " can be visualized using LaTeX\n"; */

    LINE
    //------------------------- Cleanup ------------------------
    if (yyin) fclose(yyin);  // Close the input file if opened
    closeOutputFile();  // Close the output file
    return 0;
}

// Error handling function
void yyerror(const char* s) {
    // We stop Custom Error Handling 
    // add to bison LOG
    noOfyyerrorCalls++;
    if(!TURN_OFF && stopYYERROR) return;

    std::string error = "Syntax Error: " + std::string(s) + " at Line: " + std::to_string(yylineno) + " near Token: " + yytext;
    bisonLOG.push_back(error);
    yyclearin; // Clear the buffer
}

// Handler Functions Removed

// PARSER_TABLE
void printParserTable(std::ostream& out) {
    // Sort by (lineNo, columnNo)
    std::sort(PARSER_TABLE.begin(), PARSER_TABLE.end(), 
        [](const auto& a, const auto& b) {
            return (a.first.first < b.first.first) || 
                   (a.first.first == b.first.first && a.first.second < b.first.second);
        });

    // Set dynamic column widths
    int positionWidth = 14;   // Width for "LineNo:Column"
    int idNameWidth = 20;     // Width for Identifier Name
    int idTypeWidth = 35;     // Width for Identifier Type

    // Print table header
    out << "+" << std::string(positionWidth + 2, '-') 
        << "+" << std::string(idNameWidth + 2, '-') 
        << "+" << std::string(idTypeWidth + 2, '-') 
        << "+" << std::endl;

    out << "| " << std::setw(positionWidth) << std::left << "Position"
        << " | " << std::setw(idNameWidth) << std::left << "Identifier Name"
        << " | " << std::setw(idTypeWidth) << std::left << "Identifier Type"
        << " |" << std::endl;

    out << "+" << std::string(positionWidth + 2, '-') 
        << "+" << std::string(idNameWidth + 2, '-') 
        << "+" << std::string(idTypeWidth + 2, '-') 
        << "+" << std::endl;

    // Print each entry
    for (const auto& entry : PARSER_TABLE) {
        int line = entry.first.first;
        int column = entry.first.second;
        std::string idName = entry.second.first;
        std::string idType = entry.second.second;

        out << "| " << std::setw(positionWidth) << std::left << (std::to_string(line) + ":" + std::to_string(column))
            << " | " << std::setw(idNameWidth) << std::left << idName
            << " | " << std::setw(idTypeWidth) << std::left << idType
            << " |" << std::endl;
    }

    // Print table footer
    out << "+" << std::string(positionWidth + 2, '-') 
        << "+" << std::string(idNameWidth + 2, '-') 
        << "+" << std::string(idTypeWidth + 2, '-') 
        << "+" << std::endl;
}

void writeLatexTable(std::ostream &out) {
    // LaTeX document header
    out << "\\documentclass{article}\n";
    out << "\\usepackage[a4paper,margin=1in]{geometry}\n";
    out << "\\usepackage{longtable}\n";
    out << "\\usepackage[table]{xcolor}\n";
    out << "\\definecolor{headercolor}{RGB}{79, 129, 189}\n";
    out << "\\definecolor{rowcolor}{RGB}{217, 225, 242}\n";
    out << "\\begin{document}\n\n";
    out << "\\begin{center}\n";
    out << "    {\\LARGE \\textbf{Parser Table of Input Program}} \\\\[10pt]\n";
    out << "\\end{center}\n\n";
    out << "\\renewcommand{\\arraystretch}{1.3}\n";
    out << "\\setlength{\\arrayrulewidth}{0.7mm}\n";
    out << "\\rowcolors{2}{rowcolor}{white}\n";

    
    // Begin table
    out << "\\begin{longtable}{|l|c|c|}\n";
    out << "    \\hline\n";
    out << "    \\rowcolor{headercolor} \\textbf{lineNo:columnNo} & \\textbf{Identifier Name} & \\textbf{Identifier Type} \\\\ \n";
    out << "    \\hline\n";
    out << "    \\endfirsthead\n";
    out << "    \\hline\n";
    out << "    \\rowcolor{headercolor} \\textbf{lineNo:columnNo} & \\textbf{Identifier Name} & \\textbf{Identifier Type} \\\\ \n";
    out << "    \\hline\n";
    out << "    \\endhead\n";
    // Populate table rows from PARSER_TABLE
    for (const auto &entry : PARSER_TABLE) {
        std::string correctTokenName;
        // Replace _ with \\_
        for (char c : entry.second.first) {
            if (c == '_') correctTokenName += "\\_";
            else correctTokenName += c;
        }
        out << "    " << entry.first.first << ":" << entry.first.second << " & "
            << correctTokenName << " & "
            << entry.second.second << " \\\\ \n";
        out << "    \\hline\n";
    }

    // End table and document
    out << "\\end{longtable}\n\n";
    out << "\\end{document}\n";
}