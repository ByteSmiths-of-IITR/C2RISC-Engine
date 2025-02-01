%{
#include <stdio.h>
#include "tokens.h"  // Include token definitions
#include <string.h>

#define DEBUGMODE 0

#define TableSep "+-----------+-------------------------------+-------------------------------+-----------+\n"

FILE *output_file;
int line_number = 1;

// Define the width of each column in the lexer table
int lineNoWidth = 10;
int tokenWidth = 30;
int lexemeWidth = 30;
int valueWidth = 10;

// Function to print the lexer table
void printLexerTable(int lineNo, char *token, char *lexeme) {

        // Calculate the number of spaces to add to each column
        fprintf(output_file,"| %-*d| %-*s| %-*s| %-*s|\n", lineNoWidth, lineNo, tokenWidth, token, lexemeWidth, lexeme, valueWidth, "N/A");

        // Print the table separator
        fprintf(output_file, TableSep);
}

%}



%option noyywrap

/* Definitions */

PREPROCESSOR_OP "#include"|"#define"|"#undef"|"#if"|"#ifdef"|"#ifndef"|"#else"|"#elif"|"#endif"|"#error"|"#pragma"|"#line"

PREPROCESSOR_STATEMENT {PREPROCESSOR_OP}([^"//"\n"/*"])*


DIGIT      [0-9]
LETTER     [a-zA-Z_]
ID         {LETTER}({LETTER}|{DIGIT})*
DECIMAL    {DIGIT}+
OCTAL      0[0-7]+
HEX        0[xX][0-9a-fA-F]+
FLOAT      {DECIMAL}(\.{DECIMAL})?([eE][-+]?{DECIMAL})?
CHAR       '([^'\\]|\\.)+'
STRING     \"([^\"\\]|\\.)*\"

WHITESPACE [ \t\r]+
NEWLINE    [\n]
COMMENT1   "//".*
COMMENT2   "/*"([^*]|\*+[^*/])*\*+"/"
REL_OP     "=="|"!="|"<="|">="|"<"|">"
ARITH_OP   "\+"|"-"|"*"|"/"|"%"
LOGICAL_OP "&&"|"||"|"!"
BITWISE_OP "&"|"|"|"^"|"<<"|">>"|"~"
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
{COMMENT1}        { DEBUGMODE ? fprintf(output_file, "COMMENT1: %s\n", yytext) : NULL; }
{COMMENT2}        { DEBUGMODE ? fprintf(output_file, "COMMENT2: %s\n", yytext) : NULL; }
{PREPROCESSOR_OP} {  }
{PREPROCESSOR_STATEMENT} { printLexerTable(line_number, "PREPROCESSOR_STATEMENT", yytext); }

{NEWLINE}         { line_number++; }

"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"inline"|"int"|"long"|"register"|"restrict"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while" { printLexerTable(line_number, "KEYWORD", yytext); }

{ID}             { printLexerTable(line_number,"IDENTIFIER", yytext); }
{HEX}            { printLexerTable(line_number, "HEX_LITERAL", yytext); }
{OCTAL}          { printLexerTable(line_number, "OCT_LITERAL", yytext); }
{DECIMAL}        { printLexerTable(line_number, "DECIMAL_LITERAL", yytext); }
{FLOAT}          { printLexerTable(line_number, "FLOAT_LITERAL", yytext); }
{CHAR}           { printLexerTable(line_number, "CHAR_LITERAL", yytext); }
{STRING}         { printLexerTable(line_number, "STRING_LITERAL", yytext); }

{REL_OP}         { printLexerTable(line_number,"RELATIONAL_OP", yytext); }
{ARITH_OP}       { printLexerTable(line_number, "ARITHMETIC_OP", yytext); }
{LOGICAL_OP}     { printLexerTable(line_number, "LOGICAL_OP", yytext); }
{BITWISE_OP}     { printLexerTable(line_number, "BITWISE_OP", yytext); }
{ASSIGN_OP}      { printLexerTable(line_number, "ASSIGNMENT_OP", yytext); }
{INC_DEC_OP}     { printLexerTable(line_number, "INC_DEC_OP", yytext); }

{LPAREN}         { printLexerTable(line_number, "LPAREN", yytext); }
{RPAREN}         { printLexerTable(line_number, "RPAREN", yytext); }
{LBRACE}         { printLexerTable(line_number, "LBRACE", yytext); }
{RBRACE}         { printLexerTable(line_number, "RBRACE", yytext); }
{LBRACKET}       { printLexerTable(line_number, "LBRACKET", yytext); }
{RBRACKET}       { printLexerTable(line_number, "RBRACKET", yytext); }
{SEMICOLON}      { printLexerTable(line_number, "SEMICOLON", yytext); }
{COMMA}          { printLexerTable(line_number, "COMMA", yytext); }
{DOT}            { printLexerTable(line_number, "DOT", yytext); }












.                { printLexerTable(line_number, "UNKNOWN", yytext); }

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

        // output_file = stdout;

        // Print the table header
        fprintf(output_file, TableSep);
        
        fprintf(output_file,"| %-*s| %-*s| %-*s| %-*s|\n", lineNoWidth, "Line No", tokenWidth, "Token", lexemeWidth, "Lexeme", valueWidth, "Value");

        fprintf(output_file, TableSep);


        
    yylex();  // Start lexical analysis


    fclose(yyin);
    fclose(output_file);
    return 0;
}