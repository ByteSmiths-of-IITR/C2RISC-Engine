%{
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Token definitions
enum TokenType {
    // Keywords
    TOK_INT, TOK_CHAR, TOK_VOID, TOK_STRUCT, TOK_ENUM, TOK_UNION,
    TOK_STATIC, TOK_TYPEDEF, TOK_IF, TOK_ELSE, TOK_FOR, TOK_WHILE,
    TOK_DO, TOK_SWITCH, TOK_CASE, TOK_DEFAULT, TOK_BREAK, TOK_CONTINUE,
    TOK_GOTO, TOK_RETURN, TOK_UNTIL, TOK_SIZEOF,
    
    // Operators
    TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH, TOK_PERCENT,
    TOK_ASSIGN, TOK_EQ, TOK_NE, TOK_LT, TOK_GT, TOK_LE, TOK_GE,
    TOK_AND, TOK_OR, TOK_NOT, TOK_INC, TOK_DEC, TOK_AMP, TOK_ARROW, TOK_DOT,
    
    // Assignment Operators
    TOK_PLUS_ASSIGN, TOK_MINUS_ASSIGN, TOK_STAR_ASSIGN,
    TOK_SLASH_ASSIGN, TOK_PERCENT_ASSIGN,
    
    // Punctuation
    TOK_LBRACE, TOK_RBRACE, TOK_LPAREN, TOK_RPAREN,
    TOK_LBRACKET, TOK_RBRACKET, TOK_SEMICOLON, TOK_COMMA,
    TOK_COLON, TOK_ELLIPSIS,
    
    // Literals
    TOK_INT_LITERAL, TOK_CHAR_LITERAL, TOK_STRING_LITERAL,
    
    // Identifier
    TOK_IDENTIFIER
};

// Symbol Table Structure
class SymbolTable {
private:
    std::unordered_map<std::string, std::pair<TokenType, std::string>> table;
    int current_scope = 0;

public:
    void insert(const std::string& name, TokenType type, const std::string& data_type = "") {
        table[name] = {type, data_type};
    }

    bool exists(const std::string& name) const {
        return table.find(name) != table.end();
    }

    void enter_scope() { current_scope++; }
    void exit_scope() { current_scope--; }

    void print() const {
        std::cout << "\nSymbol Table:\n";
        for (const auto& entry : table) {
            std::cout << entry.first << " : "
                      << entry.second.second 
                      << " (scope " << current_scope << ")\n";
        }
    }
};

extern SymbolTable symbol_table;
%}



%%

"int"       { symbol_table.insert(yytext, TOK_INT); return TOK_INT; }
"char"      { symbol_table.insert(yytext, TOK_CHAR); return TOK_CHAR; }
"void"      { return TOK_VOID; }
"struct"    { return TOK_STRUCT; }
"enum"      { return TOK_ENUM; }
"union"     { return TOK_UNION; }
"static"    { return TOK_STATIC; }
"typedef"   { return TOK_TYPEDEF; }
"if"        { return TOK_IF; }
"else"      { return TOK_ELSE; }
"for"       { return TOK_FOR; }
"while"     { return TOK_WHILE; }
"do"        { return TOK_DO; }
"switch"    { return TOK_SWITCH; }
"case"      { return TOK_CASE; }
"default"   { return TOK_DEFAULT; }
"break"     { return TOK_BREAK; }
"continue"  { return TOK_CONTINUE; }
"goto"      { return TOK_GOTO; }
"return"    { return TOK_RETURN; }
"until"     { return TOK_UNTIL; }
"sizeof"    { return TOK_SIZEOF; }


"+"         { return TOK_PLUS; }
"-"         { return TOK_MINUS; }
"*"         { return TOK_STAR; }
"/"         { return TOK_SLASH; }
"%"         { return TOK_PERCENT; }
"="         { return TOK_ASSIGN; }
"=="        { return TOK_EQ; }
"!="        { return TOK_NE; }
"<"         { return TOK_LT; }
">"         { return TOK_GT; }
"<="        { return TOK_LE; }
">="        { return TOK_GE; }
"&&"        { return TOK_AND; }
"||"        { return TOK_OR; }
"!"         { return TOK_NOT; }
"++"        { return TOK_INC; }
"--"        { return TOK_DEC; }
"&"         { return TOK_AMP; }
"->"        { return TOK_ARROW; }
"."         { return TOK_DOT; }


"+="        { return TOK_PLUS_ASSIGN; }
"-="        { return TOK_MINUS_ASSIGN; }
"*="        { return TOK_STAR_ASSIGN; }
"/="        { return TOK_SLASH_ASSIGN; }
"%="        { return TOK_PERCENT_ASSIGN; }


"{"         { return TOK_LBRACE; }
"}"         { return TOK_RBRACE; }
"("         { return TOK_LPAREN; }
")"         { return TOK_RPAREN; }
"["         { return TOK_LBRACKET; }
"]"         { return TOK_RBRACKET; }
";"         { return TOK_SEMICOLON; }
","         { return TOK_COMMA; }
":"         { return TOK_COLON; }
"..."       { return TOK_ELLIPSIS; }


[0-9]+|0[0-7]+|0x[0-9a-fA-F]+ { return TOK_INT_LITERAL; }
L?'([^'\\]|\\.)'       { return TOK_CHAR_LITERAL; }
L?\"([^"\\]|\\.)*\"    { return TOK_STRING_LITERAL; }


[a-zA-Z_][a-zA-Z0-9_]* {
    if (!symbol_table.exists(yytext)) {
        symbol_table.insert(yytext, TOK_IDENTIFIER, "undef");
    }
    return TOK_IDENTIFIER;
}


"//".*      { /* Ignore line comments */ }
"/*"(.|\n)*"*/" { /* Ignore block comments */ }
[ \t\n\r]+  { /* Ignore whitespace */ }

%%

SymbolTable symbol_table;

int main() {
    
    while(1) {
        yylex();
    }
    symbol_table.print();
    return 0;
}