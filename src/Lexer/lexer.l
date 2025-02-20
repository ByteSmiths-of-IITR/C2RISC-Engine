%{
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cstring>

// #define here std::cout << "HERE" << std::endl;

using namespace std;

#define DEBUGMODE 0 // 1 to show debug messages
#define SHOWERRORS 1 // 1 to show errors in error.txt 


#define TESTMODE 0
/*
1- String and Char Testing
2- Identifier Testing
*/

// Token classes
enum class TokenClass {
    KEYWORD,
    IDENTIFIER,
    LITERAL, // 2-9
    DECIMAL,
    BINARY,
    OCTAL,
    HEX,
    DOUBLE,
    CHAR,
    STRING, 
    PUNCTUATION, // 10
    OPERATOR, // 11
    UNKNOWN, // 12
    MULTI_LINE_STRING,
    MULTI_LINE_STRING_RAW,
    FLOAT, // 15
    LONG_DOUBLE // 16
};

char* tokenToString(TokenClass token) {
    int tokenValue = static_cast<int>(token);
    switch(tokenValue) {
        case 0: return "KEYWORD";
        case 1: return "IDENTIFIER";
        case 2: return "LITERAL";
        case 3: return "DECIMAL LITERAL";
        case 4: return "BINARY LITERAL";
        case 5: return "OCTAL LITERAL";
        case 6: return "HEX LITERAL";
        case 7: return "DOUBLE LITERAL";
        case 8: return "CHAR LITERAL";
        case 9: return "STRING LITERAL";
        case 10: return "PUNCTUATION";
        case 11: return "OPERATOR";
        case 12: return "UNKNOWN";
        case 13: return "MULTI_LINE_STRING";
        case 14: return "MULTI_LINE_STRING_RAW";
        case 15: return "FLOAT LIETRAL";
        case 16: return "LONG_DOUBLE LIETRAL";
        default: return "INVALID TOKEN CLASS";
    }
}


FILE *output_file;
FILE *error_file;
int line_number = 1;


// ----------- LEXER TABLE -------------------
// Define the width of each column in the lexer table 
vector<int> columnWidths = {10, 30, 50, 35};
int errorWidth = 30;


void printLexerTableSeparator() {
    fprintf(output_file, "+");
    for (int i = 0; i < columnWidths.size(); i++) {
        for (int j = 0; j < columnWidths[i]+1; j++) {
            fprintf(output_file, "-");
        }
        fprintf(output_file, "+");
    }
    fprintf(output_file, "\n");
}

void printLexerTableHeader() {
    printLexerTableSeparator();
    fprintf(output_file, "| %-*s| %-*s| %-*s| %-*s|\n", columnWidths[0], "Line No", columnWidths[1], "Token", columnWidths[2], "Lexeme", columnWidths[3], "More Info");
    printLexerTableSeparator();
}

void printLexerTable(int lineNo, char *token, char *lexeme, string moreInfo) {

    // Calculate the number of spaces to add to each column
    fprintf(output_file,"| %-*d| %-*s| %-*s| %-*s|\n", columnWidths[0], lineNo, columnWidths[1], token, columnWidths[2], lexeme, columnWidths[3], moreInfo.c_str());
    
    // Print the table separator
    printLexerTableSeparator();
}

void printLexerTable(int lineNo, char *token, char *lexeme) {
    printLexerTable(lineNo, token, lexeme, "N/A");
}


//  TOKENS----------------------------------------------

std::map<string,string> KeywordInfo;
std::map<string,string> OperatorInfo;
std::map<string,string> PunctuationInfo;

// Forward declarations of token handlers
void handleToken(TokenClass token, char *lexeme);
void handleKeyword(char *lexeme);
void handleIdentifier(char *lexeme);
void handleLiteral(TokenClass token, char *lexeme);
void handleMultiLineString(char *lexeme);
void handleMultiLineStringRAW(char *lexeme);
void handlePunctuation(char *lexeme);
void handleOperator(char *lexeme);

void handleUnknown(char *lexeme);


// Base Token Handler
void handleToken(TokenClass token, char *lexeme) {
    
    if(TESTMODE == 1){
        // Testing for string and char only
        int tokenValue = static_cast<int>(token);
        if(tokenValue != 8 && tokenValue !=9 && tokenValue != 13 && tokenValue != 14){
            return;
        }
    }

    if(TESTMODE == 2){
        // Testing for identifier only
        if(token != TokenClass::IDENTIFIER){
            return;
        }
    }


    int tokenValue = static_cast<int>(token);

    if(tokenValue == 0) {
        handleKeyword(lexeme);
    }
    else if(tokenValue == 1) {
        handleIdentifier(lexeme);
    }
    else if(tokenValue >= 2 && tokenValue <= 9 || tokenValue == 15 || tokenValue == 16) {
        handleLiteral(token, lexeme);
    }
    else if(tokenValue == 10) {
        handlePunctuation(lexeme);
    }
    else if(tokenValue == 11) {
        handleOperator(lexeme);
    }
    else if(tokenValue == 12) {
        printLexerTable(line_number, "UNKNOWN", lexeme);
    }
    else if(tokenValue == 13) {
        handleMultiLineString(lexeme);
    }
    else if(tokenValue == 14) {
        handleMultiLineStringRAW(lexeme);
    }
    else{
        printLexerTable(line_number, "Something Wrong", lexeme);
    }
}

//------------ KEYWORDS

// Adding more info to the keyword
void InitializeKeywordMap(){
    // KeywordInfo["alignas"] = "Alignment specifier";
    KeywordInfo["nullptr"] = "Pointer literal";
    KeywordInfo["true"] = "Boolean literal";
    KeywordInfo["false"] = "Boolean literal";

    KeywordInfo["new"] = "OP - P3, R-L";
    KeywordInfo["delete"] = "OP - P3, R-L";
    KeywordInfo["sizeof"] = "OP - P3, R-L";

    KeywordInfo["alignas"] = "Alignment specifier";
    KeywordInfo["int"] = "Data type";
    KeywordInfo["char"] = "Data type";
    KeywordInfo["float"] = "Data type";
    KeywordInfo["double"] = "Data type";
    KeywordInfo["void"] = "Data type";
    KeywordInfo["bool"] = "Data type";
    KeywordInfo["short"] = "Data type";
    KeywordInfo["long"] = "Data type";
    KeywordInfo["signed"] = "Data type";
    KeywordInfo["unsigned"] = "Data type";
    KeywordInfo["auto"] = "Type specifier";
    KeywordInfo["const"] = "Type qualifier";
    KeywordInfo["volatile"] = "Type qualifier";

    KeywordInfo["if"] = "Conditional statement";
    KeywordInfo["else"] = "Conditional statement";
    KeywordInfo["switch"] = "Conditional statement";
    KeywordInfo["case"] = "Conditional statement";
    KeywordInfo["default"] = "Conditional statement";
    
    KeywordInfo["for"] = "Loop statement";
    KeywordInfo["while"] = "Loop statement";
    KeywordInfo["do"] = "Loop statement";
    KeywordInfo["break"] = "Loop control statement";
    KeywordInfo["continue"] = "Loop control statement";

    KeywordInfo["return"] = "Function return statement";

}

void handleKeyword(char *lexeme) {
    string key = lexeme;
    if(KeywordInfo.find(key) != KeywordInfo.end()) {
        printLexerTable(line_number, "KEYWORD", lexeme, KeywordInfo[key]);
    }
    else{
        printLexerTable(line_number, "KEYWORD", lexeme);
    }
}

//------------- IDENTIFIERS
void handleIdentifier(char *lexeme) {

    if(strcmp(lexeme, "main") == 0){
        printLexerTable(line_number, "IDENTIFIER", lexeme, "Special Funciton Name");
        return;
    }

    printLexerTable(line_number, "IDENTIFIER", lexeme);
}


//------------- LITERALS
void handleLiteral(TokenClass token, char *lexeme) {
    // We just need to print the token and lexeme
    char* tokenString = tokenToString(token);

    printLexerTable(line_number, tokenString, lexeme);
}

//------------- MULTI LINE STRING
void handleMultiLineStringRAW(char *lexeme) {
    // we will remove the \n from the lexeme
    string lexemeString = lexeme;
    string newLexeme;
    int currLineNo = line_number;

    for(int i = 0; i < lexemeString.size(); i++){
        if(i==0 | i==2 | i==lexemeString.size()-2){
            continue;
        }
        if(lexemeString[i] == '\n'){
            line_number++;
        }
        else{
            newLexeme += lexemeString[i];
        }
    }

    char* newLexemeChar = (char*)newLexeme.c_str();
    printLexerTable(currLineNo, "STRING LITERAL", newLexemeChar,"RAW Multi Line String");
}

void handleMultiLineString(char *lexeme) {
    // we will remove the \n from the lexeme &
    string lexemeString = lexeme;
    string newLexeme;
    int currLineNo = line_number;
    
    for(int i = 0; i < lexemeString.size(); i++){
        if(lexemeString[i] == '\\' && lexemeString[i+1] == '\n'){
            line_number++;
            i++;
        }
        else{
            newLexeme += lexemeString[i];
        }
    }
    char* newLexemeChar = (char*)newLexeme.c_str();
    printLexerTable(currLineNo, "STRING LITERAL", newLexemeChar,"Multi Line String");
}

//---------- PUNCTUATION
void InitializePunctuationMap(){
    PunctuationInfo["("] = "Left Parenthesis";
    PunctuationInfo[")"] = "Right Parenthesis";
    PunctuationInfo["["] = "Left Square Bracket";
    PunctuationInfo["]"] = "Right Square Bracket";
    PunctuationInfo["{"] = "Left Curly Brace";
    PunctuationInfo["}"] = "Right Curly Brace";
    PunctuationInfo[";"] = "Semi-colon";
}

void handlePunctuation(char *lexeme) {
    string key = lexeme;
    if(PunctuationInfo.find(key) != PunctuationInfo.end()) {
        printLexerTable(line_number, "PUNCTUATION", lexeme, PunctuationInfo[key]);
    }
    else{
        printLexerTable(line_number, "PUNCTUATION", lexeme);
    }
}


//---------- OPERATORS -------------------------------
void InitializeOperatorMap(){
    //// We will be categorizing on basis of Precedence and Associativity
    OperatorInfo["::"] = "P1, L-R";

    OperatorInfo["++"] = "Depends on PostFix or Prefix"; // Postfix
    OperatorInfo["--"] = "Depends on PostFix or Prefix"; // Postfix

    OperatorInfo["~"] = "Bitwise NOT"; // Bitwise NOT (one's complement)
    OperatorInfo["!"] = "Logical NOT"; // Unary logical NOT
    OperatorInfo["-"] = "Can be \"Uniary Negation\" or \"Subtraction"; // Unary minus
    OperatorInfo["+"] = "Can be \"Uniary Plus\" or \"Addition\""; // Unary plus
    OperatorInfo["&"] = "Can be \"Address-of\" or \"Bitwise ANd\""; // Address-of
    OperatorInfo["*"] = "It can be \"Indirection\" or \"Multiplication\""; // Dereference or multiplication
    // Keyword (sizeof, new, delete) are also operators
    OperatorInfo["/"] = "Division";
    OperatorInfo["\%"] = "Modulus"; // --------__TODO

    OperatorInfo["<<"] = "Left Shift";
    OperatorInfo[">>"] = "Right Shift";

    OperatorInfo["<"] = "Less than";
    OperatorInfo[">"] = "Greater than";
    OperatorInfo["<="] = "Less than or equal to";
    OperatorInfo[">="] = "Greater than or equal to";

    OperatorInfo["=="] = "Equal to";
    OperatorInfo["!="] = "Not equal to";

    // OperatorInfo["&"] = "Bitwise AND";

    OperatorInfo["^"] = "Bitwise exclusive OR";

    // OperatorInfo["|"] = "Bitwise OR";

    OperatorInfo["&&"] = "Logical AND";

    OperatorInfo["||"] = "Logical OR";

    OperatorInfo["?"] = "Conditional Operator (Ternary)";
    OperatorInfo[":"] = "Conditional Operator (Ternary)";

    OperatorInfo["="] = "Assignment Operator";
    OperatorInfo["*="] = "MUL Assignment Operator";
    OperatorInfo["/="] = "DIV Assignment Operator";
    OperatorInfo["%="] = "MOD Assignment Operator";
    OperatorInfo["+="] = "ADD Assignment Operator";
    OperatorInfo["-="] = "SUB Assignment Operator";
    OperatorInfo["<<="] = "Left Shift Assignment Operator";
    OperatorInfo[">>="] = "Right Shift Assignment Operator";
    OperatorInfo["&="] = "Bitwise AND Assignment Operator";
    OperatorInfo["^="] = "Bitwise XOR Assignment Operator";
    OperatorInfo["|="] = "Bitwise OR Assignment Operator";

    OperatorInfo[","] = "Comma Operator";
}

void handleOperator(char *lexeme) {
    string key = lexeme;
    if(OperatorInfo.find(key) != OperatorInfo.end()) {
        printLexerTable(line_number, "OPERATOR", lexeme, OperatorInfo[key]);
    }
    else{
        printLexerTable(line_number, "OPERATOR", lexeme);
    }
}

//---------- UNKNOWN
void handleUnknown(char *lexeme) {
    printLexerTable(line_number, "UNKNOWN", lexeme);
}


//----------------------------------------------ERRORS----------------------------------------------

void handleError(char *lexeme, char *error) {
    // check if error mode
    if(!SHOWERRORS){
        return;
    }
    fprintf(error_file, "L.no: %d | ERROR: %-*s| Lexeme: %s\n", line_number, errorWidth, error, lexeme);
}


%}



%option noyywrap

/* Definitions */

PREPROCESSOR_OP "#include"|"#define"|"#undef"|"#if"|"#ifdef"|"#ifndef"|"#else"|"#elif"|"#endif"|"#error"|"#pragma"|"#line"

PREPROCESSOR_STATEMENT {PREPROCESSOR_OP}([^"//"\n"/*"])*

/* Regular Expressions */
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

MULTI_LINE_STRING \"(({INSIDE_OF_STRING}*)[\\][\n])(({INSIDE_OF_STRING}*[\\][\n])*)({INSIDE_OF_STRING}*)\"
MULTILINE_STRING_RAW "R"\""("({INSIDE_OF_STRING}*[\n])*{INSIDE_OF_STRING}*")"\"
INVALID_MULTILINE_STRING \"(.*[\n])*\"

/* NOT in USE */
INVALID_ESCAPESEQ \\[^abfnrtv\\'"]



WHITESPACE [ \t\r]+
NEWLINE    [\n]

COMMENT1   "//".*
COMMENT2   "/*"([^*]|\*+[^*/])*\*+"/"

OPERATOR   "+"|"-"|"*"|"/"|"%"|"&"|"|"|"^"|"~"|"<<"|">>"|"&&"|"||"|"!"|"=="|"!="|"<"|">"|"<="|">="|"="|"+="|"-="|"*="|"/="|"%="|"&="|"|="|"^="|"<<="|">>="|"++"|"--"|"::"|"?"|":"|","|"->*"|".*"|"."|"->"

KEYWORD  "alignas"|"alignof"|"and"|"and_eq"|"asm"|"auto"|"bitand"|"bitor"|"bool"|"break"|"case"|"catch"|"char"|"char8_t"|"char16_t"|"char32_t"|"class"|"compl"|"concept"|"const"|"consteval"|"constexpr"|"constinit"|"const_cast"|"continue"|"co_await"|"co_return"|"co_yield"|"decltype"|"default"|"delete"|"do"|"double"|"dynamic_cast"|"else"|"enum"|"explicit"|"export"|"extern"|"false"|"float"|"for"|"friend"|"goto"|"if"|"inline"|"int"|"long"|"mutable"|"namespace"|"new"|"noexcept"|"not"|"not_eq"|"nullptr"|"operator"|"or"|"or_eq"|"private"|"protected"|"public"|"register"|"reinterpret_cast"|"requires"|"return"|"short"|"signed"|"sizeof"|"static"|"static_assert"|"static_cast"|"struct"|"switch"|"template"|"this"|"thread_local"|"throw"|"true"|"try"|"typedef"|"typeid"|"typename"|"union"|"unsigned"|"using"|"virtual"|"void"|"volatile"|"wchar_t"|"while"|"xor"|"xor_eq"   

PUNCTUATOR "("|")"|"["|"]"|"{"|"}"|";"

%%

{WHITESPACE}      { /* Ignore whitespace */ }
{COMMENT1}        { DEBUGMODE ? fprintf(output_file, "COMMENT1: %s\n", yytext) : NULL; }
{COMMENT2}        { DEBUGMODE ? fprintf(output_file, "COMMENT2: %s\n", yytext) : NULL; }
{PREPROCESSOR_OP} {  }
{PREPROCESSOR_STATEMENT} { printLexerTable(line_number, "PREPROCESSOR", yytext); }

{NEWLINE}         { line_number++; }

{KEYWORD}    { handleToken(TokenClass::KEYWORD, yytext); }

{ID}             { handleToken(TokenClass::IDENTIFIER, yytext); }

{BINARY}         { handleToken(TokenClass::BINARY, yytext); }
{OCTAL}          { handleToken(TokenClass::OCTAL, yytext); }
{HEX}            { handleToken(TokenClass::HEX, yytext); }
{DECIMAL}        { handleToken(TokenClass::DECIMAL, yytext); }


{FLOAT}          { handleToken(TokenClass::FLOAT, yytext); }
{DOUBLE}         { handleToken(TokenClass::DOUBLE, yytext); }
{LONG_DOUBLE}    { handleToken(TokenClass::LONG_DOUBLE, yytext); }
{CHAR}           { handleToken(TokenClass::CHAR, yytext); }


{STRING}         { handleToken(TokenClass::STRING, yytext); }
{MULTI_LINE_STRING} { handleToken(TokenClass::MULTI_LINE_STRING, yytext); }
{MULTILINE_STRING_RAW} { handleToken(TokenClass::MULTI_LINE_STRING_RAW, yytext); }



{OPERATOR}       { handleToken(TokenClass::OPERATOR, yytext); }

{PUNCTUATOR}     { handleToken(TokenClass::PUNCTUATION, yytext); }

{INVALID_ID}     { handleError(yytext, "INVALID Identifier."); }
"\""[^\"]*"\"" { handleError(yytext, "INVALID string literal."); }
"\'"[^\']*"\'" { handleError(yytext, "INVALID character literal."); }

"\""  { handleError(yytext, "Unclosed string literal in Same Line."); }
"'"   { handleError(yytext, "Unclosed character literal."); }
"/""*" { handleError(yytext, "Unclosed comment."); }


.                { handleUnknown(yytext); handleError(yytext, "Unknown token."); }

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

    string outputFileName = "output.txt";
    string errorFileName = "error.txt";

    // we will open the output file in write mode with the name of input file
    stringstream ss(argv[1]);
    string input_name;
    getline(ss, input_name, '.');
    outputFileName = input_name + "_output.txt";
    errorFileName = input_name + "_error.txt";

    output_file = fopen(outputFileName.c_str(), "w");
    if (!output_file) {
        perror("Error opening output file");
        return 1;
    }

    if(SHOWERRORS){
    error_file = fopen(errorFileName.c_str(), "w");
    if (!error_file) {
        perror("Error opening error file");
        return 1;
    }
    }


    InitializeKeywordMap();
    InitializeOperatorMap();
    InitializePunctuationMap();
        
    // Print the header of the lexer table
    printLexerTableHeader();


    yylex();  // Start lexical analysis


    // Close the FILE pointers
    fclose(yyin);
    fclose(output_file);
    if(SHOWERRORS){
        fclose(error_file);
    }

    // Memory cleanup
    KeywordInfo.clear();
    OperatorInfo.clear();
    PunctuationInfo.clear();
    

    return 0;
}