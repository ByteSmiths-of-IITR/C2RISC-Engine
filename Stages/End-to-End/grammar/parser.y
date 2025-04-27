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
#include "header.h"

// exterstd::set<std::string> typeDefIDs; // Will come from utility.h

std::string whereWasILast;

#define TERMINAL_MESSAGE true // if you wish to check if successful parsing from terminal itself

bool TURN_OFF = true; // Turn off the custom error messages

int noOfyyerrorCalls = 0; 

// #define LINE std::cerr<< "Production - " << __LINE__<<std::endl;
#define LINE /**/


#define PARSERLOGHEADER "----------------------------------- PARSER LOG -----------------------------------"
#define LOGFOOTER       "----------------------------------- END OF LOG -----------------------------------"
#define LEXERLOGHEADER  "----------------------------------- LEXER LOG ------------------------------------"
#define BISONLOGHEADER  "----------------------------------- BISON LOG ------------------------------------"
#define SEMANTICLOGHEADER "----------------------------------- SEMANTIC LOG -----------------------------------"

// Global DS 
std::vector<std::pair<std::pair<int,int>, std::pair<std::string, std::string>> > PARSER_TABLE;

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
extern std::vector<std::string> semanticLOG;
extern std::vector<std::string> compilerLOG;

extern std::string lastToken;

bool stopYYERROR = false;

bool customError = false;

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


ASTNode *root;
ASTNode* topNode;

std::string input_file;

int compilerMode = 0; // 0-Output to Terminal, 1-output_file, 2-TestMode (send to inputFile itself)
std::string output_file;
std::string error_file;
std::ostringstream outputStream;
std::ostringstream notificationStream;
std::ostringstream errorStream;


bool ptree = false;
bool Aptree = false;
std::string dot_file;
bool stopAtIR = false; // If true, stop at IR code generation
bool cfg_code = false; // If true, generate CFG code

//How to view the ParseTree
bool compressed = false; // Default is PTree, if AST is needed, change it to false

//========================= SEMANTIC + IRCode Gen Phase =========================
// SymbolTable SYM_TABLE;
// TAC IR_CODE; [Are declared in handler.cpp]

void exit_compiler(){
    // std::cerr << "Compiler Mode: " << compilerMode << std::endl;
    // std::cerr << "Debugging Mode d1: " << (ptree ? "ON" : "OFF") << std::endl;
    // std::cerr << "Debugging Mode d2: " << (Aptree ? "ON" : "OFF") << std::endl;
    // First we print output depending on the mode
    if(compilerMode == 0){ //Terminal
        std::cout << outputStream.str() << std::endl;
        // std::cout << errorStream.str() << std::endl; [NO NEED TO REPORT ERROR IN TERMINAL]
        std::cout << notificationStream.str() << std::endl;
    }else if(compilerMode == 1){ //Output to file
        std::cout << notificationStream.str() << std::endl;
        std::cout << "Output MODE | Result in " << output_file << " & Error in " << error_file << std::endl;
        std::ofstream out(output_file);
        if(out.is_open()){
            out << outputStream.str() << std::endl;
            out << errorStream.str() << std::endl;
            out.close();
        }else{
            std::cerr << "Error opening file: " << output_file << std::endl;
        }
        std::ofstream errFile(error_file);
        if(errFile.is_open()){
            errFile << errorStream.str() << std::endl;
            errFile.close();
        }else{
            std::cerr << "Error opening file: error.log" << std::endl;
        }

    }else if(compilerMode == 2){ //TestMode
        std::ostringstream testStream;
        std::cout << "Testing MODE | Results + Error appended to " << input_file << std::endl;
        testStream << notificationStream.str() << std::endl;
        testStream << std::string(100, '-') << std::endl;
        testStream << errorStream.str() << std::endl;
        int errorSize = errorStream.str().size();
        if(errorSize > 0){
            testStream << std::string(100, '-') << std::endl;
        }
        testStream << outputStream.str() << std::endl;
        insertAfterMarker(input_file,MARKER,testStream);
    }

    // Now if debugging mode is on, we generate a dot file
    if(ptree){
        generateDOT(topNode, dot_file);
    }
    
    if(Aptree){
        generateDOT_A(topNode, dot_file);
    }

    return;
}


void signalHandler(int signum) {

    // Don't Think will be needed anymore [since we removed the handlerFunctions, which were cause of segFaults]


    std::string signalName = "Unknown Signal";
    switch (signum) {
        case SIGINT:
            signalName = "SIGINT";
            break;
        case SIGTERM:
            signalName = "SIGTERM";
            break;
        case SIGSEGV:
            signalName = "SIGSEGV";
            break;
        case SIGABRT:
            signalName = "SIGABRT";
            break;
        default:
            signalName = "Unknown Signal";
    }
    std::string signalMessage = "Just Kidding it's just my SignalHandler 💥 catching " + signalName + " and exit gracefully 😎\n";

    // std::cout << signalMessage << std::endl;
    // errorStream << "The Last Function Called - " << lastFuncCalled << std::endl;
    
    // notificationStream << signalMessage << std::endl;

    // errorStream <<  "😎 Exiting gracefully 😎\n" << std::endl;
    
    errorStream <<  SEMANTICLOGHEADER << std::endl;
    for(const auto& log : semanticLOG){
        errorStream <<  log << std::endl;
    }
    errorStream <<  LOGFOOTER << std::endl;
    std::string suicideMessage = "My Name is " + std::to_string(getpid()) + " and I am commiting Suicide 😵 at " + getCurrentTime() + " 🪦\n";
    notificationStream << suicideMessage;
    notificationStream << signalMessage;
    std::cout << suicideMessage << std::endl;
    exit_compiler();

    kill(getpid(), SIGKILL);  // Sends SIGKILL to itself
    exit(0); // Clean Exit
}



%}

%union{
    class TokenAttribute* tokenAtr;
    class ASTNode* astNode;
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("postfix_expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("argument_expression_list");
            $$->addChild($1);
        }
        $$->addChild($2);
        $$->addChild($3);
    }
    | type_name 
    { 
        LINE
        $$ = new ASTNode("argument_expression_list");
        $$->addChild($1);
    }
    | argument_expression_list COMMA type_name 
    { 
        LINE
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("argument_expression_list");
            $$->addChild($1);
        }
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

unary_expression
    : postfix_expression 
    { 
        LINE
        if(compressed){
            $$ = $1; // to get AST
        }else{
            $$ = new ASTNode("unary_expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("cast_expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("multiplicative_expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("additive_expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("shift_expression");
            $$->addChild($1);
        }

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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("relational_expression");
            $$->addChild($1);
        }

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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("equality_expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("and_expression");
            $$->addChild($1);
        }

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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("exclusive_or_expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("inclusive_or_expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("logical_and_expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("logical_or_expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("conditional_expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("assignment_expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("expression");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("constant_expression");
            $$->addChild($1);
        }
    }
    ;

declaration
    : declaration_specifiers semi_colon 
    { 
        LINE 
        $$ = new ASTNode("declaration"); 
        $$->addChild($1); 
        $$->addChild($2);
        
        std::string specifier = $1->value;

        if(specifier == TYPEDEF_FOUND){
            std::string error = "Syntax Error at line " + std::to_string(yylineno) + " near token: " + lastToken;
            error += " | Error Description: Typedef Declaration without Declarator";
            parserLOG.push_back(error);
        }
        expectingTypeName = true;
    }
    | declaration_specifiers init_declarator_list semi_colon 
    { 
        LINE
        $$ = new ASTNode("declaration"); 
        $$->addChild($1);  
        $$->addChild($2);
        $$->addChild($3);

        // Here we need to handler TYPEDEF for Inserting them in a set so lexer can detect them
        std::string specifier = $1->value;
        std::string declarator = $2->value;

        if(specifier == TYPEDEF_FOUND){
            typeDefIDs.insert(declarator);
            // std::cerr << "Inserting \'" << declarator << "\' in typedefID's SET" << std::endl;
        }
        expectingTypeName = true;
    }
    ;

declaration_specifiers
    : storage_class_specifier 
    { 
        LINE
        std::string p1 = $1->value;
        std::string final = EMPTY_VAL;
        if(p1 == TYPEDEF_FOUND){
            final = TYPEDEF_FOUND;
        }
        $$ = new ASTNode("declaration_specifiers", final);
        $$->addChild($1);
    }
    | storage_class_specifier declaration_specifiers 
    { 
        LINE
        std::string p1 = $1->value;
        std::string p2 = $2->value;
        std::string final = EMPTY_VAL;
        if(p1 == TYPEDEF_FOUND || p2 == TYPEDEF_FOUND){
            final = TYPEDEF_FOUND;
        }
        $$ = new ASTNode("declaration_specifiers", final);
        $$->addChild($1);
        if(compressed){
            $$->addChildren($2->children); //In case of compressed, add all children
        }else{
            $$->addChild($2); // if needed to be shown as tree
        }
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
        std::string p1 = $1->value;
        std::string p2 = $2->value;
        std::string final = EMPTY_VAL;
        if(p1 == TYPEDEF_FOUND || p2 == TYPEDEF_FOUND){
            final = TYPEDEF_FOUND;
        }
        $$ = new ASTNode("declaration_specifiers", final);
        $$->addChild($1);
        if(compressed){
            $$->addChildren($2->children); //In case of compressed, add all children
        }else{
            $$->addChild($2); // if needed to be shown as tree
        }
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
        std::string p1 = $1->value;
        std::string p2 = $2->value;
        std::string final = EMPTY_VAL;
        if(p1 == TYPEDEF_FOUND || p2 == TYPEDEF_FOUND){
            final = TYPEDEF_FOUND;
        }
        $$ = new ASTNode("declaration_specifiers", final);
        $$->addChild($1);
        if(compressed){
            $$->addChildren($2->children); //In case of compressed, add all children
        }else{
            $$->addChild($2); // if needed to be shown as tree
        }
    }
    ;

init_declarator_list
    : init_declarator
    {
        LINE
        $$ = new ASTNode("init_declarator_list",$1->value);
        $$->addChild($1); 
    }
    | init_declarator_list COMMA init_declarator
    {
        LINE
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("init_declarator_list", $1->value);
            $$->addChild($1);
        }
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

init_declarator
    : declarator 
    {
        LINE  
        $$ = new ASTNode("init_declarator",$1->value);
        $$->addChild($1); 
    }
    | declarator ASSIGN initializer 
    {
        LINE 
        $$ = new ASTNode("init_declarator", $1->value);
        $$->addChild($1); 
        $$->addChild($2); 
        $$->addChild($3); 
    }
    ;

storage_class_specifier
    : TYPEDEF 
    {
        LINE 
        $$ = new ASTNode("storage_class_specifier", TYPEDEF_FOUND);
        $$->addChild($1);
    }
    | EXTERN 
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
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
        
    }
    | VOID 
    {
        LINE
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
        
    }
    | CHAR 
    {
        LINE
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
        
    }
    | SHORT 
    {
        LINE 
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
        
    }
    | INT 
    {
        LINE 
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
        
    }
    | LONG 
    {
        LINE 
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
        
    }
    | FLOAT 
    {
        LINE
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
        
    }
    | DOUBLE 
    {
        LINE
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
        
    }
    | SIGNED 
    {
        LINE
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
        
    }
    | UNSIGNED 
    {
        LINE
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
        
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
        expectingTypeName = false;
    } /* THIS APPROACH WILL NEVER WORK ❌ ❌ ❌ ❌ [NO way to support typedef as of now]
    | identifier 
    {
        // To Support typedef
        LINE 
        $$ = new ASTNode("type_specifier");
        $$->addChild($1);
    } */
    ;

struct_or_union_specifier
    : struct_or_union identifier LCURLY struct_declaration_list rcurly 
    {
        LINE 
        $$ = new ASTNode("struct_or_union_specifier");
        $$->addChild($1);
        $$->addChild(new ASTNode("IDENTIFIER", $2->value));
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($5);
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
        $$->addChild(new ASTNode("IDENTIFIER", $2->value));
    }
    ;

struct_or_union
    : STRUCT 
    {
        LINE 
        $$ = new ASTNode("struct_or_union", "struct");
        expectingTypeName = false;
    }
    | UNION 
    {
        LINE 
        $$ = new ASTNode("struct_or_union", "union");
        expectingTypeName = false;
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("struct_declaration_list");
            $$->addChild($1);
        }
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
    }
    ;

specifier_qualifier_list
    : type_specifier specifier_qualifier_list
    {
        LINE
        $$ = new ASTNode("specifier_qualifier_list");
        $$->addChild($1);
        if(compressed){
            $$->addChildren($2->children);
        }else{
            $$->addChild($2);
        }
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
        if(compressed){
            $$->addChildren($2->children);
        }else{
            $$->addChild($2);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("struct_declarator_list");
            $$->addChild($1);
        }
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
    }
    | ENUM identifier 
    { 
        LINE 
        $$ = new ASTNode("enum_specifier");
        $$->addChild($1);
        $$->addChild($2);
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("enumerator_list");
            $$->addChild($1);
        }
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
        $$ = new ASTNode("declarator", $2->value); // Pass the identifier value up
        $$->addChild($1); 
        $$->addChild($2); 
    }
    | direct_declarator
    {
        LINE
        $$ = new ASTNode("declarator", $1->value); // Pass the identifier value up
        $$->addChild($1);
    }
    ;

direct_declarator
    : identifier
    {
        LINE
        $$ = new ASTNode("direct_declarator", $1->value); // Pass the identifier value up
        $$->addChild($1);
    }
    | LPAREN declarator rparen
    {
        LINE
        $$ = new ASTNode("direct_declarator",$2->value);
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | direct_declarator LSQUARE constant_expression rsquare
    {
        LINE
        $$ = new ASTNode("direct_declarator", $1->value);
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    | direct_declarator LSQUARE rsquare
    {
        LINE
        $$ = new ASTNode("direct_declarator", $1->value);
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
    }
    | direct_declarator LPAREN parameter_type_list rparen
    {
        LINE
        $$ = new ASTNode("direct_declarator", $1->value);
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    | direct_declarator LPAREN identifier_list rparen
    {
        LINE
        $$ = new ASTNode("direct_declarator", $1->value);
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
    }
    | direct_declarator LPAREN rparen
    {
        LINE
        $$ = new ASTNode("direct_declarator", $1->value);
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
        if(compressed){
            $$ = $1;
        }
        else{
            $$ = new ASTNode("type_qualifier_list");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("parameter_list");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("identifier_list");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("direct_abstract_declarator");
            $$->addChild($1);
        }
        $$->addChild($2);
        $$->addChild($3);
    }
    | direct_abstract_declarator LSQUARE constant_expression rsquare
    {
        LINE
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("direct_abstract_declarator");
            $$->addChild($1);
        }
        
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("direct_abstract_declarator");
            $$->addChild($1);
        }
        $$->addChild($2);
        $$->addChild($3);
    }
    | direct_abstract_declarator LPAREN parameter_type_list rparen
    {
        LINE
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("direct_abstract_declarator");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("initializer_list");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("declaration_list");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("statement_list");
            $$->addChild($1);
        }
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
        if(compressed){
            $$ = $1;
        }else{
            $$ = new ASTNode("translation_unit");
            $$->addChild($1);
        }
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
    : 
    declaration_specifiers declarator declaration_list compound_statement 
    { // This in not supported [ToHandle]
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
    }
    
    | declarator declaration_list compound_statement 
    { //This is Depriecated [ToHandle]
        LINE
        $$ = new ASTNode("function_definition"); 
        $$->addChild($1); 
        $$->addChild($2);
        $$->addChild($3); 
    } 
    | declarator compound_statement 
    {  // This is Depriecated [ToHandle]
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
    signal(SIGTRAP, signalHandler);
    signal(SIGABRT, signalHandler); // Catch abort signal
    signal(SIGINT, signalHandler); // Catch interrupt signal
    signal(SIGFPE, signalHandler); // Catch floating point exception
    signal(SIGILL, signalHandler); // Catch illegal instruction
    signal(SIGBUS, signalHandler); // Catch bus error
    /* signal(SIGQUIT, signalHandler); // Catch quit signal */
    /* signal(SIGTERM, signalHandler); // Catch termination signal */


    //------------------------ cmd line arguments handling ------------------------

        std::string inputInstructions = "Usage: " + std::string(argv[0]) + " <input_file> [ -o <output_file> ]/[ -t ] [ -d{1,2} <dot_file> ]\n";

        inputInstructions += "----------Compiler Options----------\n";
        inputInstructions += "  No Arguments       : Send output to stdout(terminal)\n";
        inputInstructions += "  -o [<output_file>] : Send output to a file to <output_file> else same name as input create a output file base + (.s)\n";
        inputInstructions += "  -t                 : TestingMode - Append output to <input_file> \n";
        inputInstructions += "----------Debugging Options----------\n";
        inputInstructions += " -d1 <dot_file>      : Print PTree to <dot_file>\n";
        inputInstructions += " -d2 <dot_file>      : Print Annotated PTree to <dot_file>\n";
        inputInstructions += " -ir                 : Stop at IR Phase Only \n";
        
        if(argc < 2){

            std::cerr << inputInstructions << std::endl;
            return 0;
        }

        input_file = argv[1];
        compilerMode = 0; // Default mode
        // take base name of input file by removing .c extentino
        size_t dotPos = input_file.find_last_of('.');
        std::string baseName = (dotPos == std::string::npos) ? input_file : input_file.substr(0, dotPos);
        output_file = baseName + ".s";
        error_file = baseName + ".log";

        ptree = false;
        Aptree = false;
        dot_file = "graph.dot"; // Default dot file name
        cfg_code = false;


        // Open default output file
        yyin = fopen(input_file.c_str(), "r");
        if (!yyin) {
            std::cerr << "Error: Unable to open input file\n";
            return 1;
        }
        
        // Parse command line arguments
        for (int i = 2; i < argc; ++i) {
            if (strcmp(argv[i], "-o") == 0) {
                compilerMode = 1; // Output mode
                if (i + 1 < argc) {
                    output_file = argv[++i];
                } else {
                    // Okay will use default output file name
                }
            } else if (strcmp(argv[i], "-t") == 0) {
                compilerMode = 2; // Testing mode
            } else if (strcmp(argv[i], "-d1") == 0) {
                ptree = true;
                if(i + 1 < argc) {
                    dot_file = argv[++i];
                } else {
                    std::cerr << "Error: No output file specified for -d1 option\n";
                    return 1;
                }
            } else if (strcmp(argv[i], "-d2") == 0) {
                Aptree = true;
                cfg_code = true;
                if(i + 1 < argc) {
                    dot_file = argv[++i];
                } else {
                    std::cerr << "Error: No output file specified for -d2 option\n";
                    return 1;
                }
            }else if(strcmp(argv[i], "-ir")==0){
                stopAtIR = true;
            }
            else {
                std::cerr << "Error: Unknown option " << argv[i] << "\n";
                return 1;
            }
        }


    // ------------------------ Symbol Table ------------------------
        // Create a new symbol table
        /* SymbolTable *symTable = new SymbolTable(); */

    /* LINE */
    //------------------------ Parsing ------------------------

    yyparse();  // Call BISON's parser
    
    /* LINE */
    // ------------------------- Parser Phase Completion Checks ------------------------

    bool lexerFailed = (lexerLOG.size() > 0);

    bool parseError = (parserLOG.size() > 0);
    bool bisonError = (bisonLOG.size() > 0);

    bool syntaxError = parseError || lexerFailed || bisonError;

    std::string terminalMsg = "";

    if(lexerFailed){
        notificationStream << "Lexical Analysis ❌\n";
        
        errorStream <<  LEXERLOGHEADER << std::endl;
        for(auto log : lexerLOG){
            errorStream <<  log << std::endl;
        }
        errorStream <<  LOGFOOTER << std::endl;
        errorStream <<  std::endl;

        notificationStream <<  "😊 Thanku for using our \"C2RISC-Engine\" " << std::endl;   
        // Clean Up
        fclose(yyin);
        exit_compiler();
        return 0;
    }

    if(syntaxError){
        notificationStream << "Lexical Analysis 👍 | Syntax Analysis ❌\n";
        /* errorStream <<  "\U0001F6A8 yyerror() was called " << noOfyyerrorCalls << " times \U0001F6A8\n" << std::endl; */

        // We print ourCustom Error Only if Bison-don't Report any Error

        if(parseError && !TURN_OFF){
            errorStream <<  PARSERLOGHEADER << std::endl;
            for(auto log : parserLOG){
                errorStream <<  log << std::endl;
            }

            errorStream <<  LOGFOOTER << std::endl;
            errorStream <<  std::endl;
        }
        
        if(bisonError){
            errorStream <<  BISONLOGHEADER << std::endl;
            for(auto log : bisonLOG){
                errorStream <<  log << std::endl;
            }
            errorStream <<  LOGFOOTER << std::endl;
        }
        
        errorStream <<  std::endl;

        notificationStream <<  "😊 Thanku for using our \"C2RISC-Engine\" " << std::endl;

        // If we only have custom error - i.e no bison error then we can print the AST
        // Clean Up
        fclose(yyin);
        exit_compiler();
        return 0; // For now even if there is a syntax error, we will continue to print the AST
    }
    
    // Adding a Extra Node on the top of the Ptree
    ASTNode* temp = new ASTNode("Program");
    topNode = temp;
    topNode->addChild(root);
    topNode->attributes.push_back(getCurrentTime());

    // Early exit if we are in debugging mode and to print pTree Only
    if(ptree){
        // We are in debugging mode and exit after parsing stage
        notificationStream <<  " 🌲 Parser Tree generated can be used for debugging\n";
        notificationStream << "Lexical Analysis 👍 | Syntax Analysis 👍\n";
        
        notificationStream <<  "😊 Thanku for using our \"C2RISC-Engine\" (Till Syntax Phase) " << std::endl << std::endl;
        // Clean Up and exit
        if(yyin) fclose(yyin);  // Close the input file
        exit_compiler(); // This will handle printing of ptree
        return 0;
    }

    LINE1;

    /*

                                🅾️ SEMANTIC PHASE + 🔖IR Code Gen

    */

    //SYM_TABLE & IR_CODE are globaly defined



    

    semanticPass(topNode); // Call the semantic pass 
    
    // We print the semantic log in the output file
    bool semanticFailed = (semanticLOG.size() > 0);
    if(semanticFailed){
        notificationStream <<  "Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌" << std::endl;
        notificationStream <<  "🥺 Sorry for the inconvenience, please try again later with next release \n";
        errorStream <<  SEMANTICLOGHEADER << std::endl;
        for(auto log : semanticLOG){
            errorStream <<  log << std::endl;
        }
        errorStream <<  LOGFOOTER << std::endl;
    }
    else{
    }


    // Print the IR code

    // Print the Annotated Parse Tree
    if(Aptree){
        notificationStream <<  "🌴 APTree 🌴 has been generated, can be used for debugging ❤️‍🩹 \n";
    }

    /*
                                🅾️ MachineIndependent Optimization
    */

    /* TAC oldTAC = IR_CODE; // Save the old TAC for later use */
    if(stopAtIR){
        outputStream << "\n ---- IR Code Before Machine Independent Optimization ---- \n";
        IR_CODE.printTAC(outputStream);
    }

    

    int optStatus = OKAY;

    optStatus = machineIndependentOptimization();

    if(optStatus != OKAY){
        notificationStream <<  "Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | Machine Independent Optimization ❌\n";
        errorStream <<  "Machine Independent Optimization failed with error code: " << optStatus << std::endl;
        notificationStream <<  "🥺 Sorry for the inconvenience, please try again later with next release \n";
        if(yyin) fclose(yyin);  // Close the input file
        exit_compiler(); // Clean up and exit
        return 0;
    }


    if(stopAtIR){
        outputStream << "\n ---- IR Code After Machine Independent Optimization ---- \n";
        IR_CODE.printTAC(outputStream);
        notificationStream <<  "Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | Machine Independent Optimization 👍 |  🔖 IRCode Gen" << std::endl;
        notificationStream <<  "😊 Thanku for using our \"C2RISC-Engine\" (Till IR Phase) " << std::endl;
        if(yyin) fclose(yyin);  // Close the input file
        exit_compiler(); // Clean up and exit
        return 0;
    }

    /*

                                🅾️ FINAL PHASE + 🧬 RISC-V Code Gen

    */
    RISCV_CODE finalCode; 

    int riscvCodeGenStatus = codeGen(); // Call the RISC-V code generation function

    if(riscvCodeGenStatus != 0){
        notificationStream <<  "Lexical 👍 | Syntax 👍 | Semantic 👍 | Machine Indepenent Opt 👍 | RISC-V Code Generation ❌\n";
        errorStream <<  "RISC-V Code Generation failed with error code: " << riscvCodeGenStatus << std::endl;
        notificationStream <<  "🥺 Sorry for the inconvenience, please try again later with next release \n";
        if(yyin) fclose(yyin);  // Close the input file
        exit_compiler(); // Clean up and exit
        return 0;
    }

    // Print the CFG_CODE
    if(cfg_code){
    outputStream << "\n\U0001F3A8 CFG Code Generation completed successfully \U0001F3A8\n";
    notificationStream << " 📈 CFG Code Generation in progress \n";
    outputStream << "#-------------------------------------------------------------------------\n";
    CFG_CODE.printCode(outputStream);
    outputStream << "#-------------------------------------------------------------------------\n";
    outputStream << std::endl << std::endl;
    }
    
    notificationStream <<  "Lexical 👍 | Syntax 👍 | Semantic 👍 | Machine Indepenent Opt 👍 | RISC-V Code Generation 👍\n";
    std::string Time = getCurrentTime();
    outputStream << "#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(" << Time << ") 🎨 ---------\n";
    /* outputStream << "#-------------------------------------------------------------------------\n"; */
    outputStream << std::endl;

    // Print the RISC-V code
    FINAL_CODE.printCode(outputStream);
    outputStream << "#-------------------------------------------------------------------------\n";
    notificationStream <<  "😊 Thanku for using our \"C2RISC-Engine\" (Till RISC-V CodeGen Phase) " << std::endl;

    if (yyin) fclose(yyin);  // Close the input file if opened
    exit_compiler(); // Clean up and exit
    return 0;
}


// Error handling function
void yyerror(const char* s) {
    // We stop Custom Error Handling 
    // add to bison LOG
    noOfyyerrorCalls++;


    std::string error = "Syntax Error: " + std::string(s) + " at Line: " + std::to_string(yylineno) + " near Token: " + yytext;
    bisonLOG.push_back(error);
    yyclearin; // Clear the buffer
}

