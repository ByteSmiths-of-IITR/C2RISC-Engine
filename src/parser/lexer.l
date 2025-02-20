%{
#include "parser.tab.h" // Include the token definitions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "ast.h" 

std::ofstream LEXlog("LEXER_debug.log", std::ios::trunc);

// Function to handle errors
void yyerror(const char *s);
%}

%option noyywrap

DIGIT      [0-9]
LETTER     [a-zA-Z_]
ID         {LETTER}({LETTER}|{DIGIT})*
INVALID_ID ({LETTER}|{DIGIT})*
ESCAPESEQ  \\[abfnrtv\\'"]

DECIMAL    {DIGIT}+
BINARY     0b[01]+
OCTAL      0[0-7]+
HEX        0[xX][0-9a-fA-F]+

FLOAT_BASE     {DECIMAL}?(\.{DECIMAL})?([eE][-+]?{DECIMAL})?
FLOAT          {FLOAT_BASE}[fF]
DOUBLE         {FLOAT_BASE}
LONG_DOUBLE    {FLOAT_BASE}[lL]

CHAR       '([^'\\]|{ESCAPESEQ})'


INSIDE_OF_STRING ([^\"\\\n]|{ESCAPESEQ})
STRING     \"{INSIDE_OF_STRING}*\"
INVALID_STRING "\""[^\"]*"\""
INVALID_CHAR "\'"[^\']*"\'" 
UNCLOSED_STRING "\""
UNCLOSED_CHAR "'"
UNCLOSED_COMMENT2 "/""*"


MULTI_LINE_STRING \"(({INSIDE_OF_STRING}*)[\\][\n])(({INSIDE_OF_STRING}*[\\][\n])*)({INSIDE_OF_STRING}*)\"
MULTILINE_STRING_RAW "R"\""("({INSIDE_OF_STRING}*[\n])*{INSIDE_OF_STRING}*")"\"
INVALID_MULTILINE_STRING \"(.*[\n])*\"

/* NOT in USE */
INVALID_ESCAPESEQ \\[^abfnrtv\\'"]



WHITESPACE [ \t\r]+
NEWLINE    [\n]

COMMENT1   "//".*
COMMENT2   "/*"([^*]|\*+[^*/])*\*+"/"



%%



{CHAR}                       { return CONSTANT; }
{BINARY}                     { return CONSTANT; }
{OCTAL}                      { return CONSTANT; }
{HEX}                        { return CONSTANT; }
{DECIMAL}                    { return CONSTANT; }
{FLOAT}                      { return CONSTANT; }
{DOUBLE}                     { return CONSTANT; }
{LONG_DOUBLE}                { return CONSTANT; }

{MULTI_LINE_STRING}          { return STRING_LITERAL; }
{MULTILINE_STRING_RAW}       { return STRING_LITERAL; }
{STRING}                     { return STRING_LITERAL; }


"("                          { return LPAREN; }
")"                          { return RPAREN; }
"{"                          { return LCURLY; }
"}"                          { return RCURLY; }
"["                          { return LSQUARE; }
"]"                          { return RSQUARE; }
"."                          { return DOT; }
","                          { return COMMA; }
"&"                          { return BIT_AND; }
"*"                          { return STAR; }
"+"                          { return PLUS; }
"-"                          { return MINUS; }
"~"                          { return BIT_NOT; }
"!"                          { return NOT_OP; }
"/"                          { return DIVIDE; }
"%"                          { return MOD; }
"<"                          { return LESSER_OP; }
">"                          { return GREATER_OP; }
"^"                          { return XOR; }
"|"                          { return BIT_OR; }
"?"                          { return QUESTION; }
":"                          { return COLON; }
";"                          { return SEMI_COLON; }
"="                          { return ASSIGN; }

"sizeof"                     { return SIZEOF; }
"->"                         { return PTR_OP; }
"++"                         { return INC_OP; }
"--"                         { return DEC_OP; }
"<<"                         { return LEFT_OP; }
">>"                         { return RIGHT_OP; }
"<="                         { return LE_OP; }
">="                         { return GE_OP; }
"=="                         { return EQ_OP; }
"!="                         { return NE_OP; }
"&&"                         { return AND_OP; }
"||"                         { return OR_OP; }
"*="                         { return MUL_ASSIGN; }
"/="                         { return DIV_ASSIGN; }
"%="                         { return MOD_ASSIGN; }
"+="                         { return ADD_ASSIGN; }
"-="                         { return SUB_ASSIGN; }
"<<="                        { return LEFT_ASSIGN; }
">>="                        { return RIGHT_ASSIGN; }
"&="                         { return AND_ASSIGN; }
"^="                         { return XOR_ASSIGN; }
"|="                         { return OR_ASSIGN; }



"typedef"                    { return TYPEDEF; }
"extern"                     { return EXTERN; }
"static"                     { return STATIC; }
"auto"                       { return AUTO; }
"register"                   { return REGISTER; }
"char"                       { return CHAR; }
"short"                      { return SHORT; }
"int"                        { return INT; }
"long"                       { return LONG; }
"signed"                     { return SIGNED; }
"unsigned"                   { return UNSIGNED; }
"float"                      { return FLOAT; }
"double"                     { return DOUBLE; }
"const"                      { return CONST; }
"volatile"                   { return VOLATILE; }
"void"                       { return VOID; }
"struct"                     { return STRUCT; }
"union"                      { return UNION; }
"enum"                       { return ENUM; }
"..."                        { return ELLIPSIS; }
"case"                       { return CASE; }
"default"                    { return DEFAULT; }
"if"                         { return IF; }
"else"                       { return ELSE; }
"switch"                     { return SWITCH; }
"while"                      { return WHILE; }
"do"                         { return DO; }
"for"                        { return FOR; }
"goto"                       { return GOTO; }
"continue"                   { return CONTINUE; }
"break"                      { return BREAK; }
"return"                     { return RETURN; }
"until"                      { return UNTIL; }

{ID}                         { return IDENTIFIER;}

{WHITESPACE}                 { /* Ignore spaces and tabs */ }

{NEWLINE}                    { /* Ignore newlines */ }

{COMMENT1}                   { /* Ignore single-line comments */ }
{COMMENT2}                   { /* Ignore multi-line comments */ }


{INVALID_ID}                 { printf("Invalid identifier: %s\n", yytext); return INVALID_ID; }
{INVALID_MULTILINE_STRING}   { printf("Invalid multi-line string: %s\n", yytext); return INVALID_MULTILINE_STRING; }
{INVALID_STRING}             { printf("Invalid string: %s\n", yytext); return INVALID_STRING; }
{INVALID_CHAR}               { printf("Invalid char: %s\n", yytext); return INVALID_CHAR; }
{UNCLOSED_STRING}            { printf("Unclosed string: %s\n", yytext); return UNCLOSED_STRING; }
{UNCLOSED_CHAR}              { printf("Unclosed char: %s\n", yytext); return UNCLOSED_CHAR; }
{UNCLOSED_COMMENT2}          { printf("Unclosed comment: %s\n", yytext); return UNCLOSED_COMMENT2; }
.                            { printf("Unrecognized token: %s\n", yytext); return yytext[0]; }

%%

// Error handling function
void yyerror(const char *s) {
    fprintf(stderr, "Lexer Error: %s\n", s);
}
