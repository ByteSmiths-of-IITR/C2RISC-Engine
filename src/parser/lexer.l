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
#define TOKEN(t) column+=yyleng; yylval.tokenAtr = new TokenAttribute(t,yytext, line, column); return t;


std::ofstream LEXlog("LEXER_debug.log", std::ios::trunc);

//Position of the token
int line = 1;
int column = 1;


// Function to handle errors
void yyerror(const char *s);
%}

%option noyywrap

PREPROCESSOR_OP "#include"|"#define"|"#undef"|"#if"|"#ifdef"|"#ifndef"|"#else"|"#elif"|"#endif"|"#error"|"#pragma"|"#line"

PREPROCESSOR_STATEMENT {PREPROCESSOR_OP}([^"//"\n"/*"])*

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

{PREPROCESSOR_STATEMENT}        { /* Ignore preprocessor statements */ }

{CHAR}                          { TOKEN(CONSTANT)  }
{BINARY}                        { TOKEN(CONSTANT)  }
{OCTAL}                         { TOKEN(CONSTANT)  }
{HEX}                           { TOKEN(CONSTANT)  }
{DECIMAL}                       { TOKEN(CONSTANT)  }
{FLOAT}                         { TOKEN(CONSTANT)  }
{DOUBLE}                        { TOKEN(CONSTANT)  }
{LONG_DOUBLE}                   { TOKEN(CONSTANT)  }

{MULTI_LINE_STRING}             { TOKEN(STRING_LITERAL)  }
{MULTILINE_STRING_RAW}          { TOKEN(STRING_LITERAL)  }
{STRING}                        { TOKEN(STRING_LITERAL)  }

"("                             { TOKEN(LPAREN)  }
")"                             { TOKEN(RPAREN)  }
"{"                             { TOKEN(LCURLY)  }
"}"                             { TOKEN(RCURLY)  }
"["                             { TOKEN(LSQUARE)  }
"]"                             { TOKEN(RSQUARE)  }
"."                             { TOKEN(DOT)  }
","                             { TOKEN(COMMA)  }
"&"                             { TOKEN(BIT_AND)  }
"*"                             { TOKEN(STAR)  }
"+"                             { TOKEN(PLUS)  }
"-"                             { TOKEN(MINUS)  }
"~"                             { TOKEN(BIT_NOT)  }
"!"                             { TOKEN(NOT_OP)  }
"/"                             { TOKEN(DIVIDE)  }
"%"                             { TOKEN(MOD)  }
"<"                             { TOKEN(LESSER_OP)  }
">"                             { TOKEN(GREATER_OP)  }
"^"                             { TOKEN(XOR)  }
"|"                             { TOKEN(BIT_OR)  }
"?"                             { TOKEN(QUESTION)  }
":"                             { TOKEN(COLON)  }
";"                             { TOKEN(SEMI_COLON)  }
"="                             { TOKEN(ASSIGN)  }

"sizeof"                        { TOKEN(SIZEOF)  }
"->"                            { TOKEN(PTR_OP)  }
"++"                            { TOKEN(INC_OP)  }
"--"                            { TOKEN(DEC_OP)  }
"<<"                            { TOKEN(LEFT_OP)  }
">>"                            { TOKEN(RIGHT_OP)  }
"<="                            { TOKEN(LE_OP)  }
">="                            { TOKEN(GE_OP)  }
"=="                            { TOKEN(EQ_OP)  }
"!="                            { TOKEN(NE_OP)  }
"&&"                            { TOKEN(AND_OP)  }
"||"                            { TOKEN(OR_OP)  }
"*="                            { TOKEN(MUL_ASSIGN)  }
"/="                            { TOKEN(DIV_ASSIGN)  }
"%="                            { TOKEN(MOD_ASSIGN)  }
"+="                            { TOKEN(ADD_ASSIGN)  }
"-="                            { TOKEN(SUB_ASSIGN)  }
"<<="                           { TOKEN(LEFT_ASSIGN)  }
">>="                           { TOKEN(RIGHT_ASSIGN)  }
"&="                            { TOKEN(AND_ASSIGN)  }
"^="                            { TOKEN(XOR_ASSIGN)  }
"|="                            { TOKEN(OR_ASSIGN)  }

"typedef"                       { TOKEN(TYPEDEF)  }
"extern"                        { TOKEN(EXTERN)  }
"static"                        { TOKEN(STATIC)  }
"auto"                          { TOKEN(AUTO)  }
"register"                      { TOKEN(REGISTER)  }
"char"                          { TOKEN(CHAR)  }
"short"                         { TOKEN(SHORT)  }
"int"                           { TOKEN(INT)  }
"long"                          { TOKEN(LONG)  }
"signed"                        { TOKEN(SIGNED)  }
"unsigned"                      { TOKEN(UNSIGNED)  }
"float"                         { TOKEN(FLOAT)  }
"double"                        { TOKEN(DOUBLE)  }
"const"                         { TOKEN(CONST)  }
"volatile"                      { TOKEN(VOLATILE)  }
"void"                          { TOKEN(VOID)  }
"struct"                        { TOKEN(STRUCT)  }
"union"                         { TOKEN(UNION)  }
"enum"                          { TOKEN(ENUM)  }
"..."                           { TOKEN(ELLIPSIS)  }
"case"                          { TOKEN(CASE)  }
"default"                       { TOKEN(DEFAULT)  }
"if"                            { TOKEN(IF)  }
"else"                          { TOKEN(ELSE)  }
"switch"                        { TOKEN(SWITCH)  }
"while"                         { TOKEN(WHILE)  }
"do"                            { TOKEN(DO)  }
"for"                           { TOKEN(FOR)  }
"goto"                          { TOKEN(GOTO)  }
"continue"                      { TOKEN(CONTINUE)  }
"break"                         { TOKEN(BREAK)  }
"return"                        { TOKEN(RETURN)  }
"until"                         { TOKEN(UNTIL)  }

{ID}                            { TOKEN(IDENTIFIER)  }

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
{INVALID_STRING}             { printf("Invalid string: %s at line %d, column %d\n", yytext, line, column); COLUMN  return INVALID_TOKEN; }
{INVALID_CHAR}               { printf("Invalid char: %s at line %d, column %d\n", yytext, line, column); COLUMN return INVALID_TOKEN; }
{UNCLOSED_STRING}            { printf("Unclosed string: %s at line %d, column %d\n", yytext, line, column);COLUMN  return INVALID_TOKEN; }
{UNCLOSED_CHAR}              { printf("Unclosed char: %s at line %d, column %d\n", yytext, line, column); COLUMN return INVALID_TOKEN; }
{UNCLOSED_COMMENT2}          { printf("Unclosed comment: %s at line %d, column %d\n", yytext, line, column); COLUMN return INVALID_TOKEN; }

.                            { printf("Unrecognized token: %s at line %d, column %d\n", yytext, line, column); COLUMN return UNKNOWN_TOKEN; }

%%
