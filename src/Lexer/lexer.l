%{
#include <stdio.h>
#include "tokens.h"  // Include token definitions

FILE *output_file;
%}

%option noyywrap

/* Definitions */
DIGIT      [0-9]
LETTER     [a-zA-Z_]
ID         {LETTER}({LETTER}|{DIGIT})*
DECIMAL    {DIGIT}+
OCTAL      0[0-7]+
HEX        0[xX][0-9a-fA-F]+
FLOAT      {DECIMAL}(\.{DECIMAL})?([eE][-+]?{DECIMAL})?
CHAR       '([^'\\]|\\.)+'
STRING     \"([^\"\\]|\\.)*\"

WHITESPACE [ \t\r\n]+
COMMENT1   "//".*
COMMENT2   "/*"([^*]|\*+[^*/])*\*+"/"
REL_OP     "=="|"!="|"<="|">="|"<"|">"
ARITH_OP   "\+"|"-"|"*"|"/"|"%"
LOGICAL_OP "&&"|"||"|"!"
BITWISE_OP "&"|"|"|"^"|"<<"|">>"
ASSIGN_OP  "="|"+="|"-="|"*="|"/="|"%="|"<<="|">>="|"&="|"|="|"^="
INC_DEC_OP "++"|"--"

LPAREN     "("
RPAREN     ")"
LBRACE     "{"
RBRACE     "}"
LBRACKET   "["
RBRACKET   "]"
SEMICOLON  ";"
COMMA      ","
DOT        "."

%%

{WHITESPACE}      { /* Ignore whitespace */ }
{COMMENT1}        { /* Ignore single-line comments */ }
{COMMENT2}        { /* Ignore multi-line comments */ }

"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"inline"|"int"|"long"|"register"|"restrict"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while" { fprintf(output_file, "KEYWORD: %s\n", yytext); }

{ID}             { fprintf(output_file, "IDENTIFIER: %s\n", yytext); }
{HEX}            { fprintf(output_file, "HEX_LITERAL: %s\n", yytext); }
{OCTAL}          { fprintf(output_file, "OCT_LITERAL: %s\n", yytext); }
{DECIMAL}        { fprintf(output_file, "DECIMAL_LITERAL: %s\n", yytext); }
{FLOAT}          { fprintf(output_file, "FLOAT_LITERAL: %s\n", yytext); }
{CHAR}           { fprintf(output_file, "CHAR_LITERAL: %s\n", yytext); }
{STRING}         { fprintf(output_file, "STRING_LITERAL: %s\n", yytext); }

{REL_OP}         { fprintf(output_file, "RELATIONAL_OP: %s\n", yytext); }
{ARITH_OP}       { fprintf(output_file, "ARITHMETIC_OP: %s\n", yytext); }
{LOGICAL_OP}     { fprintf(output_file, "LOGICAL_OP: %s\n", yytext); }
{BITWISE_OP}     { fprintf(output_file, "BITWISE_OP: %s\n", yytext); }
{ASSIGN_OP}      { fprintf(output_file, "ASSIGNMENT_OP: %s\n", yytext); }
{INC_DEC_OP}     { fprintf(output_file, "INC_DEC_OP: %s\n", yytext); }

{LPAREN}         { fprintf(output_file, "LPAREN: %s\n", yytext); }
{RPAREN}         { fprintf(output_file, "RPAREN: %s\n", yytext); }
{LBRACE}         { fprintf(output_file, "LBRACE: %s\n", yytext); }
{RBRACE}         { fprintf(output_file, "RBRACE: %s\n", yytext); }
{LBRACKET}       { fprintf(output_file, "LBRACKET: %s\n", yytext); }
{RBRACKET}       { fprintf(output_file, "RBRACKET: %s\n", yytext); }
{SEMICOLON}      { fprintf(output_file, "SEMICOLON: %s\n", yytext); }
{COMMA}          { fprintf(output_file, "COMMA: %s\n", yytext); }
{DOT}            { fprintf(output_file, "DOT: %s\n", yytext); }

.                { fprintf(output_file, "UNKNOWN: %s\n", yytext); }

%%

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening input file");
        return 1;
    }

    output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Error opening output file");
        return 1;
    }

    yylex();  // Start lexical analysis

    fclose(yyin);
    fclose(output_file);
    return 0;
}
