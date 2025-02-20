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


%}

%option noyywrap

D [0-9]
L [a-zA-Z_]


%%
[0-9]+          {   LEXlog << "Number token " << yytext << std::endl;
                    yylval.str = strdup(yytext);
                    return NUMBER;
                }

{L}({L}|{D})*   {   LEXlog << "IDENTIFIER token: " << yytext << std::endl;
                    yylval.str = strdup(yytext);
                    return IDENTIFIER;
                }

"="             {   LEXlog << "ASSIGN token: " << yytext << std::endl;
                    return ASSIGN; 
                }

";"             {   LEXlog << "SEMICOLON token: " << yytext << std::endl;
                    return SEMICOLON; 
                }

[ \t\n]         ; // Ignore whitespace

.               {   LEXlog << "UNKNOWN token: " << yytext << std::endl;
                    yylval.str = strdup(yytext);
                    return UNKNOWN;
                }
