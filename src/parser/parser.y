%{
#include <stdio.h>
#include <stdlib.h>
// #include "lexer.yy.h"

extern char *yytext;
extern int DEBUGMODE;
void yyerror(const char *s);
extern int yylex();

#define YYDEBUG 1



%}

%union {
    char *str;
    int num;
}


%token <str> IDENTIFIER
%token <num> NUMBER
%token ASSIGN SEMICOLON 
%token <str> UNKNOWN

%%

statements:
    statement                 { }
    | statements statement     { }
    ;


statement:
    IDENTIFIER ASSIGN NUMBER SEMICOLON {
        printf("Assignment: %s = %d\n", $1, $3);
        free($1);
    }
    ;


%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
