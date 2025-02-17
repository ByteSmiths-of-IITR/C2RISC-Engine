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

//-------------------------------------- Industry Grade Debug mode setup
int DEBUGMODE = 0; // will be set to !0 if the program is run with -d flag
#define DEBUG 1
#define INFO 2
// 0-NoDebug
// 1-Debug [Explicit Debugging the code (using HERE function)]
// 2-Info  [Informational Messages]

std::ofstream debug_log("debug.log", std::ios::trunc);
// We need to truncate the log file every time we run the program

void DEBUG_MSG(int logLevel, std::string msg){
    if (logLevel <= DEBUGMODE){
        // std::time_t t = std::time(0);
        // std::tm* now = std::localtime(&t);
        // debug_log << "[" << now->tm_year + 1900 << '-' << now->tm_mon + 1 << '-' << now->tm_mday << ' ' << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << "] ";
        switch (logLevel){
            case DEBUG:
                debug_log << "[DEBUG]  : ";
                break;
            case INFO:
                debug_log << "[INFO]   : ";
                break;
            default:
                debug_log << "[UNKNOWN]: ";
                break;
        }
        debug_log << msg << std::endl;
    }
}

void HERE(){
    DEBUG_MSG(DEBUG, "Reaching here - " + std::to_string(__LINE__) + " in " + __FILE__);
}
//-------------------------------------- End of Debug mode setup


// AST Node
extern ASTNode *root;


//-------------------------------------- Forward declaration
int handleToken(int token, YYSTYPE &yylval, char* yytext);
// Make Sure to have yylval pass by reference

std::string getTokenName(int token);


//-------------------------------------- Function implementation
std::string getTokenName(int token) {
    switch (token) {
        case IDENTIFIER:
            return "IDENTIFIER";
        case NUMBER:
            return "NUMBER";
        case ASSIGN:
            return "ASSIGN";
        case SEMICOLON:
            return "SEMICOLON";
        case UNKNOWN:
            return "UNKNOWN";
        default:
            return "!!!INVALID TOKEN!!!";
    }
}

int handleToken(int token, YYSTYPE &yylval, char* yytext) {
    // Print the token and its value
    DEBUG_MSG(INFO, "Token: " + getTokenName(token) + " Value: " + std::string(yytext));

    // Store the value of the token in the yylval union
    switch (token) {
        case IDENTIFIER:   
        case NUMBER:
            yylval.str = strdup(yytext); // both IDENTIFIER and NUMBER are stored as strings
            break;
        default:
            break;
    }
    return token;
}

%}

%option noyywrap

%%

[a-zA-Z_][a-zA-Z0-9_]*    { return handleToken(IDENTIFIER, yylval, yytext);}

[0-9]+                     { return handleToken(NUMBER, yylval, yytext);}

"="                        { return handleToken(ASSIGN, yylval, yytext); }
";"                        { return handleToken(SEMICOLON, yylval, yytext); }
[ \t\n]                    { /* ignore whitespace */ }
.                          { return handleToken(UNKNOWN, yylval, yytext); }


%%
