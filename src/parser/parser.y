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

#define LINE std::cerr<<__LINE__<<std::endl;
// #define LINE /**/

// Macros for Recuding Code
#define NewToken(i) ASTNode *node = new ASTNode(getTokenName($i->tokenType),$i->value,$i->position)

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

%token <tokenAtr> INVALID_TOKEN UNKOWN_TOKEN

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

%start translation_unit
%%

primary_expression
    : IDENTIFIER 
        {   LINE
            NewToken(i);
            $$ = node;
        }
    | CONSTANT 
        { 
            LINE
            NewToken(1, "Constant");
            $$ = node;
        }
    | STRING_LITERAL 
        { 
            LINE
            NewToken(1, "StringLiteral");
            $$ = node;
        }
    | LPAREN expression RPAREN 
        {   // Prarenthesis are not part of the AST
            LINE
            $$ = $2;
        }
    ;

postfix_expression
    : primary_expression 
      { 
        // cout << __LINE__ << endl;
        $$ = $1;
      }
    | postfix_expression LSQUARE expression RSQUARE 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode("ArraySubscript");
        $$->addChild($1);
        $$->addChild($3);
      }
    | postfix_expression LPAREN RPAREN 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode("FunctionCall");
        $$->addChild($1);
      }
    | postfix_expression LPAREN argument_expression_list RPAREN 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode("FunctionCall");
        $$->addChild($1);
        $$->addChild($3);
      }
    | postfix_expression DOT IDENTIFIER 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode("MemberAccess");
        $$->addChild($1);
        $$->addChild(new ASTNode($3->lineno, "Identifier", $3->value));
      }
    | postfix_expression PTR_OP IDENTIFIER 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode("PointerMemberAccess");
        $$->addChild($1);
        $$->addChild(new ASTNode($3->lineno, "Identifier", $3->value));
      }
    | postfix_expression INC_OP 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode("PostIncrement");
        $$->addChild($1);
      }
    | postfix_expression DEC_OP 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode("PostDecrement");
        $$->addChild($1);
      }
    ;

argument_expression_list
    : assignment_expression 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode("ArgumentList");
        $$->addChild($1);
      }
    | argument_expression_list COMMA assignment_expression 
      { 
        // cout << __LINE__ << endl;
        $$ = $1;
        $$->addChild($3);
      }
    ;

unary_expression
    : postfix_expression 
      { 
        // cout << __LINE__ << endl;
        $$ = $1;
      }
    | INC_OP unary_expression 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode("PreIncrement");
        $$->addChild($2);
      }
    | DEC_OP unary_expression 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode("PreDecrement");
        $$->addChild($2);
      }
    | unary_operator cast_expression 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode($1->lineno, "UnaryOp", $1->value);
        $$->addChild($2);
      }
    | SIZEOF unary_expression 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode("SizeofExpr");
        $$->addChild($2);
      }
    | SIZEOF LPAREN type_name RPAREN 
      { 
        // cout << __LINE__ << endl;
        $$ = new ASTNode("SizeofType");
        $$->addChild($3);
      }
    ;


unary_operator
    : BIT_AND 
    {
        cout<<__LINE__<<endl; 
        $$ = new ASTNode($1->lineno, "UnaryOp", "&");
    }
    | STAR 
    {
        cout<<__LINE__<<endl; 
        $$ = new ASTNode($1->lineno, "UnaryOp", "*");
    }
    | PLUS 
    {
        cout<<__LINE__<<endl; 
        $$ = new ASTNode($1->lineno, "UnaryOp", "+");
    }
    | MINUS 
    {
        cout<<__LINE__<<endl; 
        $$ = new ASTNode($1->lineno, "UnaryOp", "-");
    }
    | BIT_NOT 
    {
        cout<<__LINE__<<endl; 
        $$ = new ASTNode($1->lineno, "UnaryOp", "~");
    }
    | NOT_OP 
    {
        cout<<__LINE__<<endl; 
        $$ = new ASTNode($1->lineno, "UnaryOp", "!");
    }
    ;

cast_expression
    : unary_expression 
      { 
        // cout << __LINE__ << endl; 
        $$ = $1;
      }
    | LPAREN type_name RPAREN cast_expression 
      { 
        // cout << __LINE__ << endl; 
        $$ = new ASTNode("TypeCast");
        $$->addChild($2);
        $$->addChild($4);
      }
    ;


multiplicative_expression
    : cast_expression 
      { 
        // cout << __LINE__ << endl; 
        $$ = $1;
      }
    | multiplicative_expression STAR cast_expression 
      { 
        // cout << __LINE__ << endl; 
        $$ = new ASTNode($2->lineno, "Multiplication", "*"); 
        $$->addChild($1); 
        $$->addChild($3);
      }
    | multiplicative_expression DIVIDE cast_expression 
      { 
        // cout << __LINE__ << endl; 
        $$ = new ASTNode($2->lineno, "Division", "/"); 
        $$->addChild($1); 
        $$->addChild($3);
      }
    | multiplicative_expression MOD cast_expression 
      { 
        // cout << __LINE__ << endl; 
        $$ = new ASTNode($2->lineno, "Modulus", "%"); 
        $$->addChild($1); 
        $$->addChild($3);
      }
    ;

additive_expression
    : multiplicative_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = $1;
      }
    | additive_expression PLUS multiplicative_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "Addition", "+"); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    | additive_expression MINUS multiplicative_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "Subtraction", "-"); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    ;

shift_expression
    : additive_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = $1;
      }
    | shift_expression LEFT_OP additive_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "LeftShift", "<<"); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    | shift_expression RIGHT_OP additive_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "RightShift", ">>"); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    ;

  relational_expression
    : shift_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = $1;
      }
    | relational_expression LESSER_OP shift_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "Lesser", "<"); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    | relational_expression GREATER_OP shift_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "Greater", ">"); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    | relational_expression LE_OP shift_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "LesserEqual", "<="); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    | relational_expression GE_OP shift_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "GreaterEqual", ">="); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    ;

  equality_expression
    : relational_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = $1;
      }
    | equality_expression EQ_OP relational_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "Equal", "=="); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    | equality_expression NE_OP relational_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "NotEqual", "!="); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    ;

and_expression
    : equality_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = $1;
      }
    | and_expression BIT_AND equality_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "BitwiseAnd", "&"); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    ;

  exclusive_or_expression
    : and_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = $1;
      }       
    | exclusive_or_expression XOR and_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "BitwiseXor", "^"); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    ;

  inclusive_or_expression
    : exclusive_or_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = $1;
      }
    | inclusive_or_expression BIT_OR exclusive_or_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "BitwiseOr", "|"); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    ;

  logical_and_expression
    : inclusive_or_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = $1;
      }
    | logical_and_expression AND_OP inclusive_or_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "LogicalAnd", "&&"); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    ;

  logical_or_expression
    : logical_and_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = $1;
      }
    | logical_or_expression OR_OP logical_and_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "LogicalOr", "||"); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    ;

conditional_expression
    : logical_or_expression 
      { 
      // cout << __LINE__ << endl;  
      $$ = $1;
      }
    | logical_or_expression QUESTION expression COLON conditional_expression 
      { 
      // cout << __LINE__ << endl;
      $$ = new ASTNode("ConditionalExpression"); 
      $$->addChild($1); 
      $$->addChild($3); 
      $$->addChild($5);
      }
    ;

  assignment_expression
    : conditional_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = $1;
      }
    | unary_expression assignment_operator assignment_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($2->lineno, "AssignmentExpression", $2->value); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    ;

assignment_operator
    : ASSIGN 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($1->lineno, "AssignmentOperator", "=");
      }
    | MUL_ASSIGN 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($1->lineno, "AssignmentOperator", "*=");
      }
    | DIV_ASSIGN 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($1->lineno, "AssignmentOperator", "/=");
      }
    | MOD_ASSIGN 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($1->lineno, "AssignmentOperator", "%=");
      }
    | ADD_ASSIGN 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($1->lineno, "AssignmentOperator", "+=");
      }
    | SUB_ASSIGN 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($1->lineno, "AssignmentOperator", "-=");
      }
    | LEFT_ASSIGN 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($1->lineno, "AssignmentOperator", "<<=");
      }
    | RIGHT_ASSIGN 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($1->lineno, "AssignmentOperator", ">>=");
      }
    | AND_ASSIGN 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($1->lineno, "AssignmentOperator", "&=");
      }
    | XOR_ASSIGN 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($1->lineno, "AssignmentOperator", "^=");
      }
    | OR_ASSIGN 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode($1->lineno, "AssignmentOperator", "|=");
      }
    ;

expression
    : assignment_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = $1;
      }
    | expression COMMA assignment_expression 
      { 
      // cout << __LINE__ << endl; 
      $$ = new ASTNode("Expression"); 
      $$->addChild($1); 
      $$->addChild($3);
      }
    ;

constant_expression
    : conditional_expression {cout<<__LINE__<<endl; $$ = $1;}
    ;

declaration
    : declaration_specifiers SEMI_COLON 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("Declaration"); 
          $$->addChild($1); 
      }
    | declaration_specifiers init_declarator_list SEMI_COLON 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("Declaration"); 
          $$->addChild($1);  
          $$->addChild($2);
          handleDeclaration($1, $2);
      }
    ;

declaration_specifiers
    : storage_class_specifier 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1;
      }
    | storage_class_specifier declaration_specifiers 
      { 
          // cout << __LINE__ << endl; 
          $$ =  $1;
          $$->addChild($2);
      }
    | type_specifier 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1;
      }
    | type_specifier declaration_specifiers 
      { 
          // cout << __LINE__ << endl; 
          $$ =  $1;
          $$->addChild($2);
      }
    | type_qualifier 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1;
      }
    | type_qualifier declaration_specifiers 
      { 
          // cout << __LINE__ << endl; 
          $$ =  $1;
          $$->addChild($2);
      }
    ;
    
init_declarator_list
    : init_declarator 
    {
        // cout << __LINE__ << endl; 
        $$ = new ASTNode($1->lineno, "InitDeclaratorList", "initDeclaratorList");
        $$->addChild($1); 
    }
    | init_declarator_list COMMA init_declarator
    {
        // cout << __LINE__ << endl; 
        $$ = $1;
        $$->addChild($3);
    }
    ;

init_declarator
    : declarator 
    {
        // cout << __LINE__ << endl;  
        $$ = $1; 
    }
    | declarator ASSIGN initializer 
    {
        // cout << __LINE__ << endl; 
        $$ = new ASTNode($2->lineno, "Initializer", "="); 
        $$->addChild($1); 
        $$->addChild($3); 
    }
    ;

storage_class_specifier
    : TYPEDEF 
    {
        // cout << __LINE__ << endl; 
        $$ = new ASTNode($1->lineno, "StorageClassSpecifier", "typedef");
    }
    | EXTERN 
    {
        // cout << __LINE__ << endl; 
        $$ = new ASTNode($1->lineno, "StorageClassSpecifier", "extern");
    }
    | STATIC 
    {
        // cout << __LINE__ << endl; 
        $$ = new ASTNode($1->lineno, "StorageClassSpecifier", "static");
    }
    | AUTO 
    {
        // cout << __LINE__ << endl; 
        $$ = new ASTNode($1->lineno, "StorageClassSpecifier", "auto");
    }
    | REGISTER 
    {
        // cout << __LINE__ << endl; 
        $$ = new ASTNode($1->lineno, "StorageClassSpecifier", "register");
    }
    ;

type_specifier
    : VOID 
    {
        // cout << __LINE__ << endl; 
        // currentTypeSpecifier = "void";
        $$ = new ASTNode($1->lineno, "TypeSpecifier", "void");
    }
    | CHAR 
    {
        // cout << __LINE__ << endl;
        // currentTypeSpecifier = "char";
        $$ = new ASTNode($1->lineno, "TypeSpecifier", "char");
    }
    | SHORT 
    {
        // cout << __LINE__ << endl; 
        // currentTypeSpecifier = "short";
        $$ = new ASTNode($1->lineno, "TypeSpecifier", "short");
    }
    | INT 
    {
        // cout << __LINE__ << endl; 
        // currentTypeSpecifier = "int";
        $$ = new ASTNode($1->lineno, "TypeSpecifier", "int");
    }
    | LONG 
    {
        // cout << __LINE__ << endl; 
        // currentTypeSpecifier = "long";
        $$ = new ASTNode($1->lineno, "TypeSpecifier", "long");
    }
    | FLOAT 
    {
        // cout << __LINE__ << endl;
        // currentTypeSpecifier = "float"; 
        $$ = new ASTNode($1->lineno, "TypeSpecifier", "float");
    }
    | DOUBLE 
    {
        // cout << __LINE__ << endl;
        // currentTypeSpecifier = "double"; 
        $$ = new ASTNode($1->lineno, "TypeSpecifier", "double");
    }
    | SIGNED 
    {
        // cout << __LINE__ << endl;
        // currentTypeSpecifier = "signed";
        $$ = new ASTNode($1->lineno, "TypeSpecifier", "signed");
    }
    | UNSIGNED 
    {
        // cout << __LINE__ << endl;
        // currentTypeSpecifier = "unsigned"; 
        $$ = new ASTNode($1->lineno, "TypeSpecifier", "unsigned");
    }
    | struct_or_union_specifier 
    {
        // cout << __LINE__ << endl;
        // currentTypeSpecifier = $1->value; 
        $$ = $1;
    }
    | enum_specifier 
    {
        // cout << __LINE__ << endl; 
        // currentTypeSpecifier = "enum";
        $$ = $1;
    }
    | TYPE_NAME 
    {
        // cout << __LINE__ << endl; 
        // currentTypeSpecifier = "typeName";
        $$ = new ASTNode($1->lineno, "TypeSpecifier", "TypeName");
    }
    ;

struct_or_union_specifier
    : struct_or_union IDENTIFIER LCURLY struct_declaration_list RCURLY 
    {
        // cout << __LINE__ << endl; 
        $$ = $1;
        string isStruct = $1->value == "struct" ? "structIdentifier" : "unionIdentifier";
        $$->addChild(new ASTNode($2->lineno, isStruct, $2->value)); 
        $$->addChild($4); 
        identifierToType.push_back({$2->lineno, {$2->value, $1->value}});
    }
    | struct_or_union LCURLY struct_declaration_list RCURLY 
    {
        // cout << __LINE__ << endl; 
        $$ = $1; 
        $$->addChild($3);  
    }
    | struct_or_union IDENTIFIER 
    {
        // cout << __LINE__ << endl; 
        $$ = $1;
        string isStruct = $1->value == "struct" ? "struct" : "union";
        $$->addChild(new ASTNode($2->lineno, isStruct, $2->value));
        identifierToType.push_back({$2->lineno, {$2->value, $1->value}});
    }
    ;

struct_or_union
    : STRUCT 
    {
        // cout << __LINE__ << endl; 
        $$ = new ASTNode($1->lineno, "Struct", "struct");
    }
    | UNION 
    {
        // cout << __LINE__ << endl; 
        $$ = new ASTNode($1->lineno, "Union", "union");
    }
    ;

struct_declaration_list
    : struct_declaration 
    {
        // cout << __LINE__ << endl; 
        $$ = new ASTNode("StructOrUnionDeclarationList");
        $$->addChild($1);
    }
    | struct_declaration_list struct_declaration 
    {
        // cout << __LINE__ << endl; 
        $$ = new ASTNode("StructOrUnionDeclarationList");
        $$->addChildren($1->children);
        $$->addChild($2); 
    }
    ;

struct_declaration
    : specifier_qualifier_list struct_declarator_list SEMI_COLON 
    {
        // cout << __LINE__ << endl; 
        $$ = new ASTNode("StructOrUnionDeclaration");
        $$->addChild($1);
        $$->addChild($2);
        handleStructUnionDeclaration($1, $2);
    }
    ;

specifier_qualifier_list
    : type_specifier specifier_qualifier_list
    {
        // cout << __LINE__ << endl;
        $$ = $1;
        $$->addChild($2);
    }
    | type_specifier
    {
        // cout << __LINE__ << endl;
        $$ = $1;
    }
    | type_qualifier specifier_qualifier_list
    {
        // cout << __LINE__ << endl;
        $$ = $1;
        $$->addChild($2);
    }
    | type_qualifier
    {
        // cout << __LINE__ << endl;
        $$ = $1;
    }
    ;

struct_declarator_list
    : struct_declarator 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("StructOrUnionDeclaratorList");
          $$->addChild($1); 
      }
    | struct_declarator_list COMMA struct_declarator 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("StructOrUnionDeclaratorList");
          $$->addChildren($1->children);
          $$->addChild($3);
      }
    ;

struct_declarator
    : declarator 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1;
      }
    | COLON constant_expression 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "StructOrUnionDeclarator", ":"); 
          $$->addChild($2); 
      }
    | declarator COLON constant_expression 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($2->lineno, "StructOrUnionDeclarator", ":");
          $$->addChild($1);
          $$->addChild($3);
      }
    ;

enum_specifier
    : ENUM LCURLY enumerator_list RCURLY 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "EnumSpecifier", "enumSpecifier"); 
          $$->addChild($3);
          handleEnumDeclaration($$);
      }
    | ENUM IDENTIFIER LCURLY enumerator_list RCURLY 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "EnumSpecifier", "enumSpecifier"); 
          $$->addChild(new ASTNode($2->lineno, "enumIdentifier", $2->value));
          $$->addChild($4);
          handleEnumDeclaration($$);
      }
    | ENUM IDENTIFIER 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("EnumSpecifier", "enumSpecifier"); 
          $$->addChild(new ASTNode($2->lineno, "enumIdentifier", $2->value));
          handleEnumDeclaration($$);
      }
    ;

enumerator_list
    : enumerator 
    {
      cout<<__LINE__<<endl; 
      $$ = new ASTNode("EnumList");
      $$->addChild($1);
    }
    | enumerator_list COMMA enumerator 
    {
      cout<<__LINE__<<endl; 
      $$ = new ASTNode("EnumList");
      $$->addChildren($1->children);
      $$->addChild($3);
    }
    ;

enumerator
    : IDENTIFIER 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "EnumItem", $1->value);
      }
    | IDENTIFIER ASSIGN constant_expression 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($2->lineno, "EnumAssignment", "=");
          $$->addChild(new ASTNode($1->lineno, "EnumItem", $1->value)); 
          $$->addChild($3);  
      }
    ;

type_qualifier
    : CONST
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode($1->lineno, "TypeQualifier", "const");
      }
    | VOLATILE
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode($1->lineno, "TypeQualifier", "volatile");
      }
    ;

declarator
    : pointer direct_declarator
      {
          $$ = new ASTNode("PointerDeclarator", "pointerDeclarator");
          $$->addChild($1); 
          $$->addChild($2); 
      }
    | direct_declarator
      {
          $$ = $1;
      }
    ;

direct_declarator
    : IDENTIFIER
      {
          // cout << __LINE__ << endl;
          // identifierToType.push_back({$1->value, currentTypeSpecifier});
          $$ = new ASTNode($1->lineno, "Identifier", $1->value);
      }
    | LPAREN declarator RPAREN
      {
          // cout << __LINE__ << endl;
          $$ = $2;
      }
    | direct_declarator LSQUARE constant_expression RSQUARE
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode("ArrayDeclaration");
          $$->addChild($1);
          $$->addChild($3);
      }
    | direct_declarator LSQUARE RSQUARE
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode("ArrayDeclaration");
          $$->addChild($1);
      }
    | direct_declarator LPAREN parameter_type_list RPAREN
      {
          // cout << __LINE__ << endl;
          $$ = $1;
          $$->addChild($3);
      }
    | direct_declarator LPAREN identifier_list RPAREN
      {
          // cout << __LINE__ << endl;
          $$ = $1;
          $$->addChild($3);
      }
    | direct_declarator LPAREN RPAREN
      {
          // cout << __LINE__ << endl;
          $$ = $1;
          $1->addChild(new ASTNode($2->lineno, "EmptyList", "emptyList"));
      }
    ;

pointer
    : STAR
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode($1->lineno, "Pointer", "pointer");
      }
    | STAR type_qualifier_list
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode($1->lineno, "Pointer", "*");
          $$->addChild($2);
      }
    | STAR pointer
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode($1->lineno, "Pointer", "*");
          $$->addChild($2);
      }
    | STAR type_qualifier_list pointer
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode($1->lineno, "Pointer", "*");
          $$->addChild($2);
          $$->addChild($3);
      }
    ;

type_qualifier_list
    : type_qualifier
      {
          // cout << __LINE__ << endl;
          $$ = $1;
      }
    | type_qualifier_list type_qualifier
      {
          // cout << __LINE__ << endl;
          $$ = $1;
          $$->addChild($2);
      }
    ;
  
parameter_type_list
    : parameter_list 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | parameter_list COMMA ELLIPSIS 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
          $$->addChild(new ASTNode($3->lineno, "Ellipsis", "...")); 
      }
    ;

parameter_list
    : parameter_declaration 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("ParameterList", "parameterList");
          $$->addChild($1); 
      }
    | parameter_list COMMA parameter_declaration 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1;
          $$->addChild($3); 
      }
    ;

parameter_declaration
    : declaration_specifiers declarator
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode("ParameterDeclaration", "parameterDeclaration");
          $$->addChild($1); 
          $$->addChild($2);  
      }
    | declaration_specifiers abstract_declarator
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode("ParameterDeclaration", "parameterDeclaration");
          $$->addChild($1);  
          $$->addChild($2);  
      }
    | declaration_specifiers
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode("ParameterDeclaration", "parameterDeclaration");
          $$->addChild($1); 
      }
    ;

identifier_list
    : IDENTIFIER 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("IdentifierList", "identifierList");
          $$->addChild(new ASTNode($1->lineno, "Identifier", $1->value)); 
      }
    | identifier_list COMMA IDENTIFIER 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
          $$->addChild(new ASTNode($3->lineno, "Identifier", $3->value)); 
      }
    ;

type_name
    : specifier_qualifier_list 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | specifier_qualifier_list abstract_declarator 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
          $$->addChild($2); 
      }
    ;

abstract_declarator
    : pointer 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | direct_abstract_declarator 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | pointer direct_abstract_declarator 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
          $$->addChild($2); 
      }
    ;

direct_abstract_declarator
    : LPAREN abstract_declarator RPAREN
      {
          // cout << __LINE__ << endl;
          $$ = $2;  
      }
    | LSQUARE RSQUARE
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode("ArrayDeclaration"); 
      }
    | LSQUARE constant_expression RSQUARE
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode("ArrayDeclaration");  
          $$->addChild($2); 
      }
    | direct_abstract_declarator LSQUARE RSQUARE
      {
          // cout << __LINE__ << endl;
          $$ = $1;  
          $$->addChild(new ASTNode("ArrayDeclaration"));  
      }
    | direct_abstract_declarator LSQUARE constant_expression RSQUARE
      {
          // cout << __LINE__ << endl;
          $$ = $1;  
          $$->addChild(new ASTNode("ArrayDeclaration"));  
          $$->addChild($3);
      }
    | LPAREN RPAREN
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode("ParameterList", "parameterList"); 
      }
    | LPAREN parameter_type_list RPAREN
      {
          // cout << __LINE__ << endl;
          $$ = $2; 
      }
    | direct_abstract_declarator LPAREN RPAREN
      {
          // cout << __LINE__ << endl;
          $$ = $1; 
          $$->addChild(new ASTNode("ParameterList", "parameterList")); 
      }
    | direct_abstract_declarator LPAREN parameter_type_list RPAREN
      {
          // cout << __LINE__ << endl;
          $$ = $1; 
          $$->addChild($3); 
      }
    ;


initializer
    : assignment_expression
      {
          // cout << __LINE__ << endl;
          $$ = $1;
      }
    | LCURLY initializer_list RCURLY
      {
          // cout << __LINE__ << endl;
          $$ = $2; 
      }
    | LCURLY initializer_list COMMA RCURLY
      {
          // cout << __LINE__ << endl;
          $$ = $2;  
      }
    ;


initializer_list
    : initializer 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | initializer_list COMMA initializer 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
          $$->addChild($3); 
      }
    ;

statement
    : labeled_statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | compound_statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | expression_statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | selection_statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | iteration_statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | jump_statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | declaration 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    ;


labeled_statement
    : IDENTIFIER COLON statement
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode($1->lineno, "LabeledStatement", $1->value); 
          $$->addChild($3); 
      }
    | CASE constant_expression COLON statement
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode($1->lineno, "CaseStatement", "Case");
          $$->addChild($2); 
          $$->addChild($4);
      }
    | DEFAULT COLON statement
      {
          // cout << __LINE__ << endl;
          $$ = new ASTNode($1->lineno, "DefaultStatement", "Default"); 
          $$->addChild($3); 
      }
    ;

compound_statement
    : LCURLY RCURLY 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("CompoundStatement", "{}"); 
      }
    | LCURLY statement_list RCURLY 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("CompoundStatement", "{}"); 
          $$->addChildren($2->children); 
      }
    | LCURLY declaration_list RCURLY 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("CompoundStatement", "{}"); 
          $$->addChildren($2->children); 
      }
    | LCURLY declaration_list statement_list RCURLY 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("CompoundStatement", "{}"); 
          $$->addChildren($2->children); 
          $$->addChildren($3->children); 
      }
    ;

declaration_list
    : declaration 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | declaration_list declaration 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
          $$->addChild($2); 
      }
    ;

statement_list
    : statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("StatementList"); 
          $$->addChild($1); 
      }
    | statement_list statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
          $$->addChild($2); 
      }
    ;

expression_statement
    : SEMI_COLON 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("ExpressionStatement", ";"); 
      }
    | expression SEMI_COLON 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    ;

selection_statement
    : IF LPAREN expression RPAREN statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "IfStatement", "if"); 
          $$->addChild($3); 
          $$->addChild($5); 
      }
    | IF LPAREN expression RPAREN statement ELSE statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "IfElseStatement", "if-else"); 
          $$->addChild($3); 
          $$->addChild($5); 
          $$->addChild($7); 
      }
    | SWITCH LPAREN expression RPAREN statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "SwitchStatement", "switch"); 
          $$->addChild($3); 
          $$->addChild($5); 
      }
    ;

iteration_statement
    : WHILE LPAREN expression RPAREN statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "WhileLoop", "while"); 
          $$->addChild($3); 
          $$->addChild($5); 
      }
    | UNTIL LPAREN expression RPAREN statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "UntilLoop", "until"); 
          $$->addChild($3); 
          $$->addChild($5); 
      }
    | DO statement WHILE LPAREN expression RPAREN SEMI_COLON 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "DoWhileLoop", "do-while"); 
          $$->addChild($2); 
          $$->addChild($5); 
      }
    | FOR LPAREN expression_statement expression_statement RPAREN statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "ForLoop", "for"); 
          $$->addChild($3); 
          $$->addChild($4); 
          $$->addChild($6); 
      }
    | FOR LPAREN expression_statement expression_statement expression RPAREN statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "ForLoop", "for"); 
          $$->addChild($3); 
          $$->addChild($4); 
          $$->addChild($5); 
          $$->addChild($7); 
      }
    | FOR LPAREN declaration expression_statement expression RPAREN statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "ForLoop", "for"); 
          $$->addChild($3); 
          $$->addChild($4); 
          $$->addChild($5); 
          $$->addChild($7); 
      }
    ;

jump_statement
    : GOTO IDENTIFIER SEMI_COLON 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "GotoStatement", "goto"); 
          $$->addChild(new ASTNode("Identifier", $2->value)); 
      }
    | CONTINUE SEMI_COLON 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "ContinueStatement", "continue"); 
      }
    | BREAK SEMI_COLON 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "BreakStatement", "break"); 
      }
    | RETURN SEMI_COLON 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "ReturnStatement", "return"); 
      }
    | RETURN expression SEMI_COLON 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode($1->lineno, "ReturnStatement", "return"); 
          $$->addChild($2); 
      }
    ;

translation_unit
    : external_declaration 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("TranslationUnit", "translationUnit");
          $$->addChild($1); 
          root = $$;
      }
    | translation_unit external_declaration 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
          $$->addChild($2); 
      }
    ;

external_declaration
    : function_definition 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | declaration 
      { 
          // cout << __LINE__ << endl; 
          $$ = $1; 
      }
    | function_declaration
      {
          // cout << __LINE__ << endl;
          $$ = $1;
      }
    ;

function_declaration: 
    declaration_specifiers declarator SEMI_COLON
    {
        // cout << __LINE__ << endl;
        $$ = new ASTNode("FunctionDeclaration");
        $$->addChild($1);
        $$->addChild($2);
        handleFunctionDefinition($2);
    }
    ;
  
function_definition
    : 
    /* declaration_specifiers declarator declaration_list compound_statement 
      { 
          // cout << __LINE__ << endl;  
          $$ = new ASTNode("FunctionDefinition"); 
          $$->addChild($2); 
          $$->addChildren($3->children); 
          $$->addChild($4); 
      }
    |  */
    declaration_specifiers declarator compound_statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("FunctionDefinition"); 
          $$->addChild($2); 
          $$->addChild($3); 
          handleFunctionDefinition($2);
      }
    /* | declarator declaration_list compound_statement 
      { 
          // cout << __LINE__ << endl; 
          $$ = new ASTNode("FunctionDefinition"); 
          $$->addChild($1); 
          $$->addChildren($2->children); 
          $$->addChild($3); 
      } */
    /* | declarator compound_statement 
      { 
          // cout << __LINE__ << endl;
          $$ = new ASTNode("FunctionDefinition"); 
          $$->addChild($1); 
          $$->addChild($2); 
      } */
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
                // Ignore
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
            if(true){
                printAST(root);
            }

    //------------------------- Cleanup ------------------------
        if (yyin) fclose(yyin);  // Close the input file if opened
        return 0;
}

