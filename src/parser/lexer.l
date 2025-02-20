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
#include "utility.h" 

// Some MACROS to reduce the Written Content in the Lexer
#define COLUMN column+=yyleng;
#define TOKEN_ATTR(t) yylval.tokenAtr = new TokenAttribute(t,yytext, line, column); return t;


std::ofstream LEXlog("LEXER_debug.log", std::ios::trunc);

//Position of the token
int line = 1;
int column = 1;


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
/* MultiLine Comment Can Disture the LineNo  */


%%


{CHAR}                          { TOKEN_ATTR(CONSTANT) COLUMN }
{BINARY}                        { TOKEN_ATTR(CONSTANT) COLUMN }
{OCTAL}                         { TOKEN_ATTR(CONSTANT) COLUMN }
{HEX}                           { TOKEN_ATTR(CONSTANT) COLUMN }
{DECIMAL}                       { TOKEN_ATTR(CONSTANT) COLUMN }
{FLOAT}                         { TOKEN_ATTR(CONSTANT) COLUMN }
{DOUBLE}                        { TOKEN_ATTR(CONSTANT) COLUMN }
{LONG_DOUBLE}                   { TOKEN_ATTR(CONSTANT) COLUMN }

{MULTI_LINE_STRING}             { TOKEN_ATTR(STRING_LITERAL) COLUMN }
{MULTILINE_STRING_RAW}          { TOKEN_ATTR(STRING_LITERAL) COLUMN }
{STRING}                        { TOKEN_ATTR(STRING_LITERAL) COLUMN }

"("                             { TOKEN_ATTR(LPAREN) COLUMN }
")"                             { TOKEN_ATTR(RPAREN) COLUMN }
"{"                             { TOKEN_ATTR(LCURLY) COLUMN }
"}"                             { TOKEN_ATTR(RCURLY) COLUMN }
"["                             { TOKEN_ATTR(LSQUARE) COLUMN }
"]"                             { TOKEN_ATTR(RSQUARE) COLUMN }
"."                             { TOKEN_ATTR(DOT) COLUMN }
","                             { TOKEN_ATTR(COMMA) COLUMN }
"&"                             { TOKEN_ATTR(BIT_AND) COLUMN }
"*"                             { TOKEN_ATTR(STAR) COLUMN }
"+"                             { TOKEN_ATTR(PLUS) COLUMN }
"-"                             { TOKEN_ATTR(MINUS) COLUMN }
"~"                             { TOKEN_ATTR(BIT_NOT) COLUMN }
"!"                             { TOKEN_ATTR(NOT_OP) COLUMN }
"/"                             { TOKEN_ATTR(DIVIDE) COLUMN }
"%"                             { TOKEN_ATTR(MOD) COLUMN }
"<"                             { TOKEN_ATTR(LESSER_OP) COLUMN }
">"                             { TOKEN_ATTR(GREATER_OP) COLUMN }
"^"                             { TOKEN_ATTR(XOR) COLUMN }
"|"                             { TOKEN_ATTR(BIT_OR) COLUMN }
"?"                             { TOKEN_ATTR(QUESTION) COLUMN }
":"                             { TOKEN_ATTR(COLON) COLUMN }
";"                             { TOKEN_ATTR(SEMI_COLON) COLUMN }
"="                             { TOKEN_ATTR(ASSIGN) COLUMN }

"sizeof"                        { TOKEN_ATTR(SIZEOF) COLUMN }
"->"                            { TOKEN_ATTR(PTR_OP) COLUMN }
"++"                            { TOKEN_ATTR(INC_OP) COLUMN }
"--"                            { TOKEN_ATTR(DEC_OP) COLUMN }
"<<"                            { TOKEN_ATTR(LEFT_OP) COLUMN }
">>"                            { TOKEN_ATTR(RIGHT_OP) COLUMN }
"<="                            { TOKEN_ATTR(LE_OP) COLUMN }
">="                            { TOKEN_ATTR(GE_OP) COLUMN }
"=="                            { TOKEN_ATTR(EQ_OP) COLUMN }
"!="                            { TOKEN_ATTR(NE_OP) COLUMN }
"&&"                            { TOKEN_ATTR(AND_OP) COLUMN }
"||"                            { TOKEN_ATTR(OR_OP) COLUMN }
"*="                            { TOKEN_ATTR(MUL_ASSIGN) COLUMN }
"/="                            { TOKEN_ATTR(DIV_ASSIGN) COLUMN }
"%="                            { TOKEN_ATTR(MOD_ASSIGN) COLUMN }
"+="                            { TOKEN_ATTR(ADD_ASSIGN) COLUMN }
"-="                            { TOKEN_ATTR(SUB_ASSIGN) COLUMN }
"<<="                           { TOKEN_ATTR(LEFT_ASSIGN) COLUMN }
">>="                           { TOKEN_ATTR(RIGHT_ASSIGN) COLUMN }
"&="                            { TOKEN_ATTR(AND_ASSIGN) COLUMN }
"^="                            { TOKEN_ATTR(XOR_ASSIGN) COLUMN }
"|="                            { TOKEN_ATTR(OR_ASSIGN) COLUMN }

"typedef"                       { TOKEN_ATTR(TYPEDEF) COLUMN }
"extern"                        { TOKEN_ATTR(EXTERN) COLUMN }
"static"                        { TOKEN_ATTR(STATIC) COLUMN }
"auto"                          { TOKEN_ATTR(AUTO) COLUMN }
"register"                      { TOKEN_ATTR(REGISTER) COLUMN }
"char"                          { TOKEN_ATTR(CHAR) COLUMN }
"short"                         { TOKEN_ATTR(SHORT) COLUMN }
"int"                           { TOKEN_ATTR(INT) COLUMN }
"long"                          { TOKEN_ATTR(LONG) COLUMN }
"signed"                        { TOKEN_ATTR(SIGNED) COLUMN }
"unsigned"                      { TOKEN_ATTR(UNSIGNED) COLUMN }
"float"                         { TOKEN_ATTR(FLOAT) COLUMN }
"double"                        { TOKEN_ATTR(DOUBLE) COLUMN }
"const"                         { TOKEN_ATTR(CONST) COLUMN }
"volatile"                      { TOKEN_ATTR(VOLATILE) COLUMN }
"void"                          { TOKEN_ATTR(VOID) COLUMN }
"struct"                        { TOKEN_ATTR(STRUCT) COLUMN }
"union"                         { TOKEN_ATTR(UNION) COLUMN }
"enum"                          { TOKEN_ATTR(ENUM) COLUMN }
"..."                           { TOKEN_ATTR(ELLIPSIS) COLUMN }
"case"                          { TOKEN_ATTR(CASE) COLUMN }
"default"                       { TOKEN_ATTR(DEFAULT) COLUMN }
"if"                            { TOKEN_ATTR(IF) COLUMN }
"else"                          { TOKEN_ATTR(ELSE) COLUMN }
"switch"                        { TOKEN_ATTR(SWITCH) COLUMN }
"while"                         { TOKEN_ATTR(WHILE) COLUMN }
"do"                            { TOKEN_ATTR(DO) COLUMN }
"for"                           { TOKEN_ATTR(FOR) COLUMN }
"goto"                          { TOKEN_ATTR(GOTO) COLUMN }
"continue"                      { TOKEN_ATTR(CONTINUE) COLUMN }
"break"                         { TOKEN_ATTR(BREAK) COLUMN }
"return"                        { TOKEN_ATTR(RETURN) COLUMN }
"until"                         { TOKEN_ATTR(UNTIL) COLUMN }

{ID}                            { TOKEN_ATTR(IDENTIFIER) COLUMN }

{WHITESPACE}                    { COLUMN /* Ignore spaces and tabs */ }

{NEWLINE}                       { line++; column = 1; /* Ignore newlines */ }

{COMMENT1}                      { COLUMN /* Ignore single-line comments */ }
{COMMENT2}                      { 
                                    for (int i = 0; yytext[i] != '\0'; i++) {
                                        if (yytext[i] == '\n') {
                                            line++;
                                        }
                                    }
                                    COLUMN /* Ignore multi-line comments */ 
                                }

{INVALID_ID}                 { printf("Invalid identifier: %s at line %d, column %d\n", yytext, line, column); COLUMN return INVALID_TOKEN; }
{INVALID_MULTILINE_STRING}   { printf("Invalid multi-line string: %s at line %d, column %d\n", yytext, line, column); COLUMN return INVALID_TOKEN; }
{INVALID_STRING}             { printf("Invalid string: %s at line %d, column %d\n", yytext, line, column); COLUMN return INVALID_TOKEN; }
{INVALID_CHAR}               { printf("Invalid char: %s at line %d, column %d\n", yytext, line, column); COLUMN return INVALID_TOKEN; }
{UNCLOSED_STRING}            { printf("Unclosed string: %s at line %d, column %d\n", yytext, line, column); COLUMN return INVALID_TOKEN; }
{UNCLOSED_CHAR}              { printf("Unclosed char: %s at line %d, column %d\n", yytext, line, column); COLUMN return INVALID_TOKEN; }
{UNCLOSED_COMMENT2}          { printf("Unclosed comment: %s at line %d, column %d\n", yytext, line, column); COLUMN return INVALID_TOKEN; }

.                            { printf("Unrecognized token: %s at line %d, column %d\n", yytext, line, column); COLUMN return UNKNOWN_TOKEN; }

%%

// Error handling function
void yyerror(const char *s) {
    fprintf(stderr, "Lexer Error: %s\n", s);
}
