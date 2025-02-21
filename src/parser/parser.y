%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "utility.h"  

#define EMPTY_VAL "!!EMPTY!!"

// #define LINE std::cerr<<__LINE__<<std::endl;
#define LINE /**/

// Global DS 
std::vector<std::pair<std::pair<int,int>, std::pair<std::string, std::string>> > PARSER_TABLE;


// Handler Functions
void Struct_Union_Declaration_Handler(ASTNode* specifierQualifierList, ASTNode* declaratorList);
void Enum_Declaration_Handler(ASTNode* enumSpecifier);
void Function_Def_Handler(ASTNode* declarator);
void Declaration_Handler(ASTNode* declarationSpecifiers, ASTNode* initDeclaratorList);

// Extern Variables
extern int yylineno;
extern char *yytext;
void yyerror(const char *s);
extern int yylex();
extern FILE *yyin;

#define YYDEBUG 1

std::ofstream PARSERlog("PARSER_debug.log", std::ios::trunc);

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
%token <tokenAtr> STRUCT UNION ENUM ELLIPSIS
%token <tokenAtr> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN UNTIL

%token <tokenAtr> INVALID_TOKEN UNKNOWN_TOKEN

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
%type <astNode> function_declaration
%type <astNode> function_definition

/* %expect-rr 96 */
/* %expect 2 */

%start translation_unit
%%

primary_expression
    : IDENTIFIER 
        {   
            LINE
            $$ = new ASTNode($1);
        }
    | CONSTANT 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    | STRING_LITERAL 
        { 
            LINE
            $$ = new ASTNode($1);
        }
    | LPAREN expression RPAREN 
        {   
            // Parenthesis are not part of the AST
            LINE
            $$ = $2;
        }
    ;

postfix_expression
    : primary_expression 
    { 
        LINE
        $$ = $1;
    }
    | postfix_expression LSQUARE expression RSQUARE 
    { 
        LINE
        $$ = new ASTNode("ArrayAccess");
    }
    | postfix_expression LPAREN RPAREN 
    { 
        LINE
        $$ = new ASTNode("FunctionCall");
        $$->addChild($1);
    }
    | postfix_expression LPAREN argument_expression_list RPAREN 
    { 
        LINE
        $$ = new ASTNode("FunctionCall");
        $$->addChild($1);
        $$->addChild($3);
    }
    | postfix_expression DOT IDENTIFIER 
    { 
        LINE
        $$ = new ASTNode("Member Access");
        $$->addChild($1);
        $$->addChild($3);
    }
    | postfix_expression PTR_OP IDENTIFIER 
    { 
        LINE
        $$ = new ASTNode("Pointer Member Access");
        $$->addChild($1);
        // $$->addChild(new ASTNode($3->position, "Identifier", $3->value));
        $$->addChild($3);
    }
    | postfix_expression INC_OP 
    { 
        LINE
        $$ = new ASTNode("PostIncrement");
        $$->addChild($1);
    }
    | postfix_expression DEC_OP 
    { 
        LINE
        $$ = new ASTNode("PostDecrement");
        $$->addChild($1);
    }
    ;

argument_expression_list
    : assignment_expression 
    { 
        LINE
        $$ = new ASTNode("Argument List");
        $$->addChild($1);
    }
    | argument_expression_list COMMA assignment_expression 
    { 
        LINE
        $$ = $1;
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
        $$ = new ASTNode("PreIncrement");
        $$->addChild($2);
    }
    | DEC_OP unary_expression 
    { 
        LINE
        $$ = new ASTNode("PreDecrement");
        $$->addChild($2);
    }
    | unary_operator cast_expression 
    { 
        LINE
        $$ = new ASTNode("UnaryOperation",$1->value,$1->position);
        $$->addChild($2);
    }
    | SIZEOF unary_expression 
    { 
        LINE
        $$ = new ASTNode("SizeofExpr");
        $$->addChild($2);
    }
    | SIZEOF LPAREN type_name RPAREN 
    { 
        LINE
        $$ = new ASTNode("SizeofType");
        $$->addChild($3);
    }
    ;


unary_operator
    : BIT_AND 
    {
        LINE 
        $$ = new ASTNode($1);
    }
    | STAR 
    {
        LINE 
        $$ = new ASTNode($1); 
    }
    | PLUS 
    {
        LINE 
        $$ = new ASTNode($1); 
    }
    | MINUS 
    {
        LINE 
        $$ = new ASTNode($1); 
    }
    | BIT_NOT 
    {
        LINE 
        $$ = new ASTNode($1); 
    }
    | NOT_OP 
    {
        LINE 
        $$ = new ASTNode($1); 
    }
    ;

cast_expression
    : unary_expression 
    { 
        LINE 
        $$ = $1;
    }
    | LPAREN type_name RPAREN cast_expression 
    { 
        LINE 
        $$ = new ASTNode("TypeCast");
        $$->addChild($2);
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
        $$ = new ASTNode("Multiplication", "*", $2->position); 
        $$->addChild($1); 
        $$->addChild($3);
    }
    | multiplicative_expression DIVIDE cast_expression 
    { 
        LINE 
        $$ = new ASTNode("Division", "/", $2->position); 
        $$->addChild($1); 
        $$->addChild($3);
    }
    | multiplicative_expression MOD cast_expression 
    { 
        LINE 
        $$ = new ASTNode("Modulus", "%", $2->position);
        $$->addChild($1); 
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
        $$ = new ASTNode("Addition", "+", $2->position);
        $$->addChild($1); 
        $$->addChild($3);
    }
    | additive_expression MINUS multiplicative_expression 
    { 
        LINE 
        $$ = new ASTNode("Subtraction", "-", $2->position); 
        $$->addChild($1); 
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
        $$ = new ASTNode("LeftShift", "<<", $2->position); 
        $$->addChild($1); 
        $$->addChild($3);
    }
    | shift_expression RIGHT_OP additive_expression 
    { 
        LINE 
        $$ = new ASTNode("RightShift", ">>", $2->position); 
        $$->addChild($1); 
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
        $$ = new ASTNode("Lesser", "<", $2->position); 
        $$->addChild($1); 
        $$->addChild($3);
    }
    | relational_expression GREATER_OP shift_expression 
    { 
        LINE 
        $$ = new ASTNode("Greater", ">", $2->position); 
        $$->addChild($1); 
        $$->addChild($3);
    }
    | relational_expression LE_OP shift_expression 
    { 
        LINE 
        $$ = new ASTNode("LesserEqual", "<=", $2->position); 
        $$->addChild($1); 
        $$->addChild($3);
    }
    | relational_expression GE_OP shift_expression 
    { 
        LINE 
        $$ = new ASTNode("GreaterEqual", ">=", $2->position); 
        $$->addChild($1); 
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
        $$ = new ASTNode("Equal", "==", $2->position); 
        $$->addChild($1); 
        $$->addChild($3);
    }
    | equality_expression NE_OP relational_expression 
    { 
        LINE 
        $$ = new ASTNode("NotEqual", "!=", $2->position); 
        $$->addChild($1); 
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
        $$ = new ASTNode("BitwiseAnd", "&", $2->position); 
        $$->addChild($1); 
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
        $$ = new ASTNode("BitwiseXor", "^", $2->position); 
        $$->addChild($1); 
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
        $$ = new ASTNode("BitwiseOr", "|", $2->position); 
        $$->addChild($1); 
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
        $$ = new ASTNode("LogicalAnd", "&&", $2->position); 
        $$->addChild($1); 
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
        $$ = new ASTNode("LogicalOr", "||", $2->position); 
        $$->addChild($1); 
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
        $$ = new ASTNode("Conditional_Expression"); 
        $$->addChild($1); 
        $$->addChild($3); 
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
        $$ = new ASTNode("AssignmentExpression", $2->value, $2->position); 
        $$->addChild($1); 
        $$->addChild($3);
    }
    ;

assignment_operator
    : ASSIGN 
    { 
        LINE 
        $$ = new ASTNode($1);
    }
    | MUL_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode($1);
    }
    | DIV_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode($1);
    }
    | MOD_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode($1);
    }
    | ADD_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode($1);
    }
    | SUB_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode($1);
    }
    | LEFT_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode($1);
    }
    | RIGHT_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode($1);
    }
    | AND_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode($1);
    }
    | XOR_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode($1);
    }
    | OR_ASSIGN 
    { 
        LINE 
        $$ = new ASTNode($1);
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
        $$ = new ASTNode("Expression"); 
        $$->addChild($1); 
        $$->addChild($3);
    }
    ;

constant_expression
    : conditional_expression {
        LINE
        $$ = $1;
    }
    ;

declaration
    : declaration_specifiers SEMI_COLON 
    { 
        LINE 
        $$ = new ASTNode("Declaration"); 
        $$->addChild($1); 
    }
    | declaration_specifiers init_declarator_list SEMI_COLON 
    { 
        LINE
        $$ = new ASTNode("Declaration"); 
        $$->addChild($1);  
        $$->addChild($2);
        Declaration_Handler($1, $2);
    }
    ;

declaration_specifiers
    : storage_class_specifier 
    { 
        LINE
        $$ = $1;
    }
    | storage_class_specifier declaration_specifiers 
    { 
        LINE
        $$ = $1;
        $$->addChild($2);
    }
    | type_specifier 
    { 
        LINE
        $$ = $1;
    }
    | type_specifier declaration_specifiers 
    { 
        LINE
        $$ = $1;
        $$->addChild($2);
    }
    | type_qualifier 
    { 
        LINE
        $$ = $1;
    }
    | type_qualifier declaration_specifiers 
    { 
        LINE
        $$ = $1;
        $$->addChild($2);
    }
    ;


    
init_declarator_list
    : init_declarator 
    {
        LINE
        $$ = new ASTNode("Initialization or Declaration List", EMPTY_VAL, $1->position);
        $$->addChild($1); 
    }
    | init_declarator_list COMMA init_declarator
    {
        LINE
        $$ = $1;
        $$->addChild($3);
    }
    ;


init_declarator
    : declarator 
    {
        LINE  
        $$ = $1; 
    }
    | declarator ASSIGN initializer 
    {
        LINE 
        $$ = new ASTNode("Initializer", "=", $2->position); 
        $$->addChild($1); 
        $$->addChild($3); 
    }
    ;

storage_class_specifier
    : TYPEDEF 
    {
        LINE 
        $$ = new ASTNode("Storage Class Specifier", "typedef", $1->position);
    }
    | EXTERN 
    {
        LINE 
        $$ = new ASTNode("Storage Class Specifier", "extern", $1->position);
    }
    | STATIC 
    {
        LINE 
        $$ = new ASTNode("Storage Class Specifier", "static", $1->position);
    }
    | AUTO 
    {
        LINE 
        $$ = new ASTNode("Storage Class Specifier", "auto", $1->position);
    }
    | REGISTER 
    {
        LINE 
        $$ = new ASTNode("Storage Class Specifier", "register", $1->position);
    }
    ;

type_specifier
    : VOID 
    {
        LINE 
        $$ = new ASTNode("Type Specifier", "void", $1->position);
    }
    | CHAR 
    {
        LINE
        $$ = new ASTNode("Type Specifier", "char", $1->position);
    }
    | SHORT 
    {
        LINE 
        $$ = new ASTNode("Type Specifier", "short", $1->position);
    }
    | INT 
    {
        LINE 
        $$ = new ASTNode("Type Specifier", "int", $1->position);
    }
    | LONG 
    {
        LINE 
        $$ = new ASTNode("Type Specifier", "long", $1->position);
    }
    | FLOAT 
    {
        LINE
        $$ = new ASTNode("Type Specifier", "float", $1->position);
    }
    | DOUBLE 
    {
        LINE
        $$ = new ASTNode("Type Specifier", "double", $1->position);
    }
    | SIGNED 
    {
        LINE
        $$ = new ASTNode("Type Specifier", "signed", $1->position);
    }
    | UNSIGNED 
    {
        LINE
        $$ = new ASTNode("Type Specifier", "unsigned", $1->position);
    }
    | struct_or_union_specifier 
    {
        LINE
        $$ = $1;
    }
    | enum_specifier 
    {
        LINE 
        $$ = $1;
    }
    | TYPE_NAME 
    {
        LINE 
        $$ = new ASTNode("Type Specifier", "TypeName", $1->position);
    }
    ;

struct_or_union_specifier
    : struct_or_union IDENTIFIER LCURLY struct_declaration_list RCURLY 
    {
        LINE 
        $$ = $1;
        std::string isStruct = $1->value == "struct" ? "structID" : "unionID";
        $$->addChild(isStruct, $2->value,$2->position);
        $$->addChild($4); 
        PARSER_TABLE.push_back({$2->position, {$2->value, $1->value}});
    }
    | struct_or_union LCURLY struct_declaration_list RCURLY 
    {
        LINE 
        $$ = $1; 
        $$->addChild($3);  
    }
    | struct_or_union IDENTIFIER 
    {
        LINE 
        $$ = $1;
        std::string isStruct = $1->value == "struct" ? "struct" : "union";
        $$->addChild(isStruct, $2->value,$2->position);
        PARSER_TABLE.push_back({$2->position, {$2->value, $1->value}});
    }
    ;


struct_or_union
    : STRUCT 
    {
        LINE 
        $$ = new ASTNode("Struct", "struct", $1->position);
    }
    | UNION 
    {
        LINE 
        $$ = new ASTNode("Union", "union", $1->position);
    }
    ;


struct_declaration_list
    : struct_declaration 
    {
        LINE 
        $$ = new ASTNode("Struct or Union Declaration List");
        $$->addChild($1);
    }
    | struct_declaration_list struct_declaration 
    {
        LINE 
        $$ = new ASTNode("Struct or Union Declaration List");
        $$->addChildren($1->children);
        $$->addChild($2); 
    }
    ;


struct_declaration
    : specifier_qualifier_list struct_declarator_list SEMI_COLON 
    {
        LINE 
        $$ = new ASTNode("Struct or Union Declaration");
        $$->addChild($1);
        $$->addChild($2);
        Struct_Union_Declaration_Handler($1, $2);
    }
    ;

specifier_qualifier_list
    : type_specifier specifier_qualifier_list
    {
        LINE
        $$ = $1;
        $$->addChild($2);
    }
    | type_specifier
    {
        LINE
        $$ = $1;
    }
    | type_qualifier specifier_qualifier_list
    {
        LINE
        $$ = $1;
        $$->addChild($2);
    }
    | type_qualifier
    {
        LINE
        $$ = $1;
    }
    ;

struct_declarator_list
    : struct_declarator 
    { 
        LINE 
        $$ = new ASTNode("Struct or Union Declarator List");
        $$->addChild($1); 
    }
    | struct_declarator_list COMMA struct_declarator 
    { 
        LINE 
        $$ = new ASTNode("Struct or Union Declarator List");
        $$->addChildren($1->children);
        $$->addChild($3);
    }
    ;

struct_declarator
    : declarator 
    { 
        LINE 
        $$ = $1;
    }
    | COLON constant_expression 
    { 
        LINE 
        $$ = new ASTNode("Struct or Union Declarator", ":", $1->position); 
        $$->addChild($2); 
    }
    | declarator COLON constant_expression 
    { 
        LINE 
        $$ = new ASTNode("Struct or Union Declarator", ":", $2->position);
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

enum_specifier
    : ENUM LCURLY enumerator_list RCURLY 
    { 
        LINE 
        $$ = new ASTNode("Enum Specifier", EMPTY_VAL, $1->position);
        $$->addChild($3);
        Enum_Declaration_Handler($$);
    }
    | ENUM IDENTIFIER LCURLY enumerator_list RCURLY 
    { 
        LINE 
        $$ = new ASTNode("Enum Specifier", EMPTY_VAL, $1->position);
        $$->addChild("enumID", $2->value,$2->position);
        $$->addChild($4);
        Enum_Declaration_Handler($$);
    }
    | ENUM IDENTIFIER 
    { 
        LINE 
        $$ = new ASTNode("Enum Specifier", EMPTY_VAL); 
        $$->addChild("enumID", $2->value,$2->position);
        Enum_Declaration_Handler($$);
    }
    ;

enumerator_list
    : enumerator 
    {
        LINE 
        $$ = new ASTNode("Enum List");
        $$->addChild($1);
    }
    | enumerator_list COMMA enumerator 
    {
        LINE 
        $$ = new ASTNode("Enum List");
        $$->addChildren($1->children);
        $$->addChild($3);
    }
    ;

enumerator
    : IDENTIFIER 
    { 
        LINE 
        $$ = new ASTNode("Enum Element", $1->value, $1->position);
    }
    | IDENTIFIER ASSIGN constant_expression 
    { 
        LINE 
        $$ = new ASTNode("Enum Assignment",EMPTY_VAL , $2->position);
        $$->addChild("Enum Element", $1->value,$1->position); 
        $$->addChild($3);  
    }
    ;

type_qualifier
    : CONST
    {
        LINE
        $$ = new ASTNode("Type Qualifier", "const", $1->position);
    }
    | VOLATILE
    {
        LINE
        $$ = new ASTNode("Type Qualifier", "volatile", $1->position);
    }
    ;

declarator
    : pointer direct_declarator
    {
        LINE
        $$ = new ASTNode("Pointer Declarator", EMPTY_VAL);
        $$->addChild($1); 
        $$->addChild($2); 
    }
    | direct_declarator
    {
        LINE
        $$ = $1;
    }
    ;

direct_declarator
    : IDENTIFIER
    {
        LINE
        $$ = new ASTNode($1);
    }
    | LPAREN declarator RPAREN
    {
        LINE
        $$ = $2;
    }
    | direct_declarator LSQUARE constant_expression RSQUARE
    {
        LINE
        $$ = new ASTNode("Array Declaration");
        $$->addChild($1);
        $$->addChild($3);
    }
    | direct_declarator LSQUARE RSQUARE
    {
        LINE
        $$ = new ASTNode("Array Declaration");
        $$->addChild($1);
    }
    | direct_declarator LPAREN parameter_type_list RPAREN
    {
        LINE
        $$ = $1;
        $$->addChild($3);
    }
    | direct_declarator LPAREN identifier_list RPAREN
    {
        LINE
        $$ = $1;
        $$->addChild($3);
    }
    | direct_declarator LPAREN RPAREN
    {
        LINE
        $$ = $1;
        $1->addChild("Empty Parameter List", EMPTY_VAL, $1->position);
    }
    ;

    

pointer
    : STAR
    {
        LINE
        $$ = new ASTNode("Pointer", "*", $1->position);
    }
    | STAR type_qualifier_list
    {
        LINE
        $$ = new ASTNode("Pointer", "*", $1->position);
        $$->addChild($2);
    }
    | STAR pointer
    {
        LINE
        $$ = new ASTNode("Pointer", "*", $1->position);
        $$->addChild($2);
    }
    | STAR type_qualifier_list pointer
    {
        LINE
        $$ = new ASTNode("Pointer", "*", $1->position);
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

type_qualifier_list
    : type_qualifier
    {
        LINE
        $$ = $1;
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
        $$ = $1; 
    }
    | parameter_list COMMA ELLIPSIS 
    { 
        LINE 
        $$ = $1; 
        $$->addChild("Ellipsis", "...", $3->position); 
    }
    ;

parameter_list
    : parameter_declaration 
    { 
        LINE 
        $$ = new ASTNode("Parameter List", EMPTY_VAL);
        $$->addChild($1); 
    }
    | parameter_list COMMA parameter_declaration 
    { 
        LINE 
        $$ = $1;
        $$->addChild($3); 
    }
    ;

parameter_declaration
    : declaration_specifiers declarator
    {
        LINE
        $$ = new ASTNode("Parameter Declaration", "parameterDeclaration");
        $$->addChild($1); 
        $$->addChild($2);  
    }
    | declaration_specifiers abstract_declarator
    {
        LINE
        $$ = new ASTNode("Parameter Declaration", "parameterDeclaration");
        $$->addChild($1);  
        $$->addChild($2);  
    }
    | declaration_specifiers
    {
        LINE
        $$ = new ASTNode("Parameter Declaration", "parameterDeclaration");
        $$->addChild($1); 
    }
    ;

identifier_list
    : IDENTIFIER 
    { 
        LINE 
        $$ = new ASTNode("IdentifierList", "identifierList");
        $$->addChild($1);
    }
    | identifier_list COMMA IDENTIFIER 
    { 
        LINE 
        $$ = $1; 
        $$->addChild($3);
    }
    ;

type_name
    : specifier_qualifier_list 
    { 
        LINE 
        $$ = $1; 
    }
    | specifier_qualifier_list abstract_declarator 
    { 
        LINE 
        $$ = $1; 
        $$->addChild($2); 
    }
    ;

abstract_declarator
    : pointer 
    { 
        LINE 
        $$ = $1; 
    }
    | direct_abstract_declarator 
    { 
        LINE 
        $$ = $1; 
    }
    | pointer direct_abstract_declarator 
    { 
        LINE 
        $$ = $1; 
        $$->addChild($2); 
    }
    ;

direct_abstract_declarator
    : LPAREN abstract_declarator RPAREN
    {
        LINE
        $$ = $2;  
    }
    | LSQUARE RSQUARE
    {
        LINE
        $$ = new ASTNode("Array Declaration"); 
    }
    | LSQUARE constant_expression RSQUARE
    {
        LINE
        $$ = new ASTNode("Array Declaration");  
        $$->addChild($2); 
    }
    | direct_abstract_declarator LSQUARE RSQUARE
    {
        LINE
        $$ = $1;  
        $$->addChild("Array Declaration");  
    }
    | direct_abstract_declarator LSQUARE constant_expression RSQUARE
    {
        LINE
        $$ = $1;  
        $$->addChild(new ASTNode("Array Declaration"));  
        $$->addChild($3);
    }
    | LPAREN RPAREN
    {
        LINE
        $$ = new ASTNode("Parameter List", EMPTY_VAL); 
    }
    | LPAREN parameter_type_list RPAREN
    {
        LINE
        $$ = $2; 
    }
    | direct_abstract_declarator LPAREN RPAREN
    {
        LINE
        $$ = $1; 
        $$->addChild("Parameter List", EMPTY_VAL); 
    }
    | direct_abstract_declarator LPAREN parameter_type_list RPAREN
    {
        LINE
        $$ = $1; 
        $$->addChild($3); 
    }
    ;

initializer
    : assignment_expression
    {
        LINE
        $$ = $1;
    }
    | LCURLY initializer_list RCURLY
    {
        LINE
        $$ = $2; 
    }
    | LCURLY initializer_list COMMA RCURLY
    {
        LINE
        $$ = $2;  
    }
    ;


initializer_list
    : initializer 
    { 
        LINE 
        $$ = $1; 
    }
    | initializer_list COMMA initializer 
    { 
        LINE 
        $$ = $1; 
        $$->addChild($3); 
    }
    ;

statement
    : labeled_statement 
    { 
        LINE 
        $$ = $1; 
    }
    | compound_statement 
    { 
        LINE 
        $$ = $1; 
    }
    | expression_statement 
    { 
        LINE 
        $$ = $1; 
    }
    | selection_statement 
    { 
        LINE 
        $$ = $1; 
    }
    | iteration_statement 
    { 
        LINE 
        $$ = $1; 
    }
    | jump_statement 
    { 
        LINE 
        $$ = $1; 
    }
    | declaration 
    { 
        LINE 
        $$ = $1; 
    }
    ;


labeled_statement
    : IDENTIFIER COLON statement
    {
        LINE
        $$ = new ASTNode("Labeled Statement", $1->value, $1->position);
        $$->addChild($3); 
    }
    | CASE constant_expression COLON statement
    {
        LINE
        $$ = new ASTNode("Case Statement", "Case", $1->position);
        $$->addChild($2); 
        $$->addChild($4);
    }
    | DEFAULT COLON statement
    {
        LINE
        $$ = new ASTNode("Default Statement", "Default", $1->position);
        $$->addChild($3); 
    }
    ;

compound_statement
    : LCURLY RCURLY 
    { 
        LINE 
        $$ = new ASTNode("Compound Statement", "{  }"); 
    }
    | LCURLY statement_list RCURLY 
    { 
        LINE 
        $$ = new ASTNode("Compound Statement", "{  }"); 
        $$->addChildren($2->children); 
    }
    | LCURLY declaration_list RCURLY 
    { 
        LINE 
        $$ = new ASTNode("Compound Statement", "{  }"); 
        $$->addChildren($2->children); 
    }
    | LCURLY declaration_list statement_list RCURLY 
    { 
        LINE 
        $$ = new ASTNode("Compound Statement", "{  }"); 
        $$->addChildren($2->children); 
        $$->addChildren($3->children); 
    }
    ;

declaration_list
    : declaration 
    { 
        LINE 
        $$ = $1; 
    }
    | declaration_list declaration 
    { 
        LINE 
        $$ = $1; 
        $$->addChild($2); 
    }
    ;

statement_list
    : statement 
    { 
        LINE 
        $$ = new ASTNode("Statement List"); 
        $$->addChild($1); 
    }
    | statement_list statement 
    { 
        LINE 
        $$ = $1; 
        $$->addChild($2); 
    }
    ;

    //---------Done till here
expression_statement
    : SEMI_COLON 
    { 
        LINE 
        $$ = new ASTNode("Expression Statement", ";"); 
    }
    | expression SEMI_COLON 
    { 
        LINE 
        $$ = $1; 
    }
    ;

selection_statement
    : IF LPAREN expression RPAREN statement 
    { 
        LINE 
        $$ = new ASTNode("If Statement", "if", $1->position);
        $$->addChild($3); 
        $$->addChild($5); 
    }
    | IF LPAREN expression RPAREN statement ELSE statement 
    { 
        LINE 
        $$ = new ASTNode("If Else Statement", "if-else", $1->position);
        $$->addChild($3); 
        $$->addChild($5); 
        $$->addChild($7); 
    }
    | SWITCH LPAREN expression RPAREN statement 
    { 
        LINE 
        $$ = new ASTNode("Switch Statement", "switch", $1->position);
        $$->addChild($3); 
        $$->addChild($5); 
    }
    ;

iteration_statement
    : WHILE LPAREN expression RPAREN statement 
    { 
        LINE 
        $$ = new ASTNode("While Loop", "while", $1->position);
        $$->addChild($3); 
        $$->addChild($5); 
    }
    | UNTIL LPAREN expression RPAREN statement 
    { 
        LINE 
        $$ = new ASTNode("Until Loop", "until", $1->position);
        $$->addChild($3); 
        $$->addChild($5); 
    }
    | DO statement WHILE LPAREN expression RPAREN SEMI_COLON 
    { 
        LINE 
        $$ = new ASTNode("DoWhile Loop", "do-while", $1->position);
        $$->addChild($2); 
        $$->addChild($5); 
    }
    | FOR LPAREN expression_statement expression_statement RPAREN statement 
    { 
        LINE 
        $$ = new ASTNode("For Loop", "for", $1->position); 
        $$->addChild($3); 
        $$->addChild($4); 
        $$->addChild($6); 
    }
    | FOR LPAREN expression_statement expression_statement expression RPAREN statement 
    { 
        LINE 
        $$ = new ASTNode("For Loop", "for", $1->position);
        $$->addChild($3); 
        $$->addChild($4); 
        $$->addChild($5); 
        $$->addChild($7); 
    }
    | FOR LPAREN declaration expression_statement expression RPAREN statement 
    { 
        LINE 
        $$ = new ASTNode("For Loop", "for", $1->position); 
        $$->addChild($3); 
        $$->addChild($4); 
        $$->addChild($5); 
        $$->addChild($7); 
    }
    ;

jump_statement
    : GOTO IDENTIFIER SEMI_COLON 
    { 
        LINE 
        $$ = new ASTNode("Goto Statement", "goto", $1->position); 
        $$->addChild($2);
    }
    | CONTINUE SEMI_COLON 
    { 
        LINE 
        $$ = new ASTNode("Continue Statement", "continue", $1->position);
    }
    | BREAK SEMI_COLON 
    { 
        LINE 
        $$ = new ASTNode("Break Statement", "break", $1->position);
    }
    | RETURN SEMI_COLON 
    { 
        LINE 
        $$ = new ASTNode("Return Statement", "return", $1->position);
    }
    | RETURN expression SEMI_COLON 
    { 
        LINE 
        $$ = new ASTNode("Return Statement", "return", $1->position); 
        $$->addChild($2); 
    }
    ;

translation_unit
    : external_declaration 
    { 
        LINE 
        $$ = new ASTNode("Translation Unit", EMPTY_VAL);
        $$->addChild($1); 
        root = $$;
    }
    | translation_unit external_declaration 
    { 
        LINE 
        $$ = $1; 
        $$->addChild($2); 
    }
    ;

external_declaration
    : function_definition 
    { 
        LINE 
        $$ = $1; 
    }
    | declaration 
    { 
        LINE 
        $$ = $1; 
    }
    | function_declaration
    {
        LINE
        $$ = $1;
    }
    ;

function_declaration
    : declaration_specifiers declarator SEMI_COLON
    {
        LINE
        $$ = new ASTNode("Function Declaration");
        $$->addChild($1);
        $$->addChild($2);
        Function_Def_Handler($2);
    }
    ;

function_definition
    :
    /* declaration_specifiers declarator declaration_list compound_statement 
    { 
        LINE  
        $$ = new ASTNode("Function Definition"); 
        $$->addChild($2); 
        $$->addChildren($3->children); 
        $$->addChild($4); 
    }
    |  */
    declaration_specifiers declarator compound_statement 
    { 
        LINE
        $$ = new ASTNode("Function Definition"); 
        $$->addChild($2); 
        $$->addChild($3); 
        Function_Def_Handler($2);
    }
    /* | declarator declaration_list compound_statement 
    { 
        LINE
        $$ = new ASTNode("Function Definition"); 
        $$->addChild($1); 
        $$->addChildren($2->children); 
        $$->addChild($3); 
      } */
    /* | declarator compound_statement 
    { 
        LINE
        $$ = new ASTNode("Function Definition"); 
        $$->addChild($1); 
        $$->addChild($2); 
      } */
    ;

%%


// main function

int main(int argc, char **argv) {

    //------------------------ cmd line arguments handling ------------------------

        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> [-p [<DOTFileName>] ] [-r <recursiveOutputFile]\n";
            return 1;
        }

        std::string input_file = argv[1];
        std::string output_file = argv[2];
        std::string dot_file;
        std::string recursive_output_file;
        std::string SExp_file;

        // Parse arguments
        for (int i = 3; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-p") {
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

    
    yyparse();  // Call BISON's parser
    




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
            if(true){
                printAST(root);
            }

    //------------------------- Cleanup ------------------------
        if (yyin) fclose(yyin);  // Close the input file if opened
        return 0;
}

// Error handling function
void yyerror(const char* s) {
    std::cerr<<"Line Number: "<<yylineno<<". Error: "<<s<<"."<<std::endl;
}

//Handler Functions
int noOfPointers(ASTNode* node){
    if(node->children.size()==0) return 1;

    return 1+noOfPointers(node->children[0]);
}

void E_S_U_Declaration_Handler(ASTNode* declarationSpecifiers, ASTNode* initDeclaratorList,std::string s1,std::string s2){
    for(auto item : initDeclaratorList->children){
        if(item->type == "Initializer"){
            PARSER_TABLE.push_back({item->children[0]->position,{item->children[0]->value, s2}});
        } else {
            PARSER_TABLE.push_back({item->position,{item->value, s2}});
        }
    }
}

void Declaration_Handler(ASTNode* declarationSpecifiers, ASTNode* initDeclaratorList){
    std::string type="";
    ASTNode* node = declarationSpecifiers;
    
    if(declarationSpecifiers->type == "Enum Specifier"){
        E_S_U_Declaration_Handler(declarationSpecifiers, initDeclaratorList, "enum", "enumElement");
        return;
    }

    if(declarationSpecifiers->type == "Struct"){
        E_S_U_Declaration_Handler(declarationSpecifiers, initDeclaratorList, "struct", "structInstance"); 
        return;
    }

    if(declarationSpecifiers->type == "Union"){
        E_S_U_Declaration_Handler(declarationSpecifiers, initDeclaratorList, "union", "unionInstance");
        return;
    }

    int typeSpec=0, typeQual=0, storageClass=0;
    while(node){
        if(node->type == "Type Specifier"){
            type = node->value;
            typeSpec++;
        }else if(node->type == "Storage Class Specifier") {
            storageClass++; 
        }
        node=(node->children.size())?node->children[0]:nullptr; //Move down the tree
    }
    if(typeSpec>1 || storageClass>1){
        yyerror("NOT-ALLOWED | Multiple type specifiers/qualifiers/storage classes in declaration");
        return;
    }
    if(type == "") type = "int"; // default type is int
    for(auto children : initDeclaratorList->children){
        int pointCount=0, arrayCount=0;
        ASTNode* tempNode = children;
        if(children->type == "Initializer") tempNode = children->children[0];
        if(tempNode->type == "Pointer Declarator"){
            pointCount=noOfPointers(tempNode->children[0]);
            std::cout<<pointCount<<std::endl;
            tempNode=tempNode->children[1];
        }
        if(tempNode->type == "Array Declaration"){
            while(tempNode->type == "Array Declaration"){
            arrayCount++;
            tempNode = tempNode->children[0];
            }
        }
        PARSER_TABLE.push_back({tempNode->position,{tempNode->value, type+(pointCount?(" "+std::to_string(pointCount)+"-D ptr "):"")+(arrayCount?(" "+std::to_string(arrayCount)+"-D Arr "):"")}});
    }
}

void Function_Def_Handler(ASTNode* declarator){
    std::string functionName=declarator->value;
    PARSER_TABLE.push_back({declarator->position, {functionName, "function"}});
    declarator = declarator->children[0];
    if(declarator->type == "EmptyList") return;
    else if(declarator->type == "Parameter List"){
        for(auto parameter: declarator->children){
            std::string type="";
            ASTNode* tempInitDeclList = new ASTNode("Initialization or Declaration List", "initDeclaratorList");
            tempInitDeclList->addChild(parameter->children[1]);
            Declaration_Handler(parameter->children[0], tempInitDeclList);
        }
    }
}

void Struct_Union_Declaration_Handler(ASTNode* specifierQualifierList, ASTNode* structDeclaratorList){
    std::string type="";
    ASTNode* node = specifierQualifierList;
    int typeSpec=0, typeQual=0, storageClass=0;
    while(node){
        if(node->type == "Type Specifier"){
            type = node->value;
            typeSpec++;
        } else if(node->type == "Storage Class Specifier") storageClass++;

        node=(node->children.size())?node->children[0]:nullptr;
    }
    if(storageClass>1){
        yyerror("Multiple storage classes in declaration");
        return;
    }
    if(type == "") type = "int";
    for(auto children : structDeclaratorList->children){
        if(children->type == "Struct or Union Declarator"){
            PARSER_TABLE.push_back({children->children[0]->position, {children->children[0]->value, type}});
        }else if(children->type == "Identifier"){
            PARSER_TABLE.push_back({children->position,{children->value, type}});
        }
    }
}

void Enum_Declaration_Handler(ASTNode* enumSpecifier){
    for(auto children : enumSpecifier->children){
        if(children->type == "enumID"){
            PARSER_TABLE.push_back({children->position, {children->value, "enum"}});
        } else if(children->type == "Enum List"){
            for(auto item : children->children){
                if(item->type == "Enum Assignment"){
                    PARSER_TABLE.push_back({item->children[0]->position, {item->children[0]->value, "enumElement"}});
                } else {
                    PARSER_TABLE.push_back({item->position, {item->value, "enumElement"}});
                }
            }
        }
    }
}
