// struct, union, enum, function name collision

struct A{
    int a;
    int b;
};

union A{ // error: ‘A’ defined as wrong kind of tag
    int a;
    int b;
};

enum A{ // error: ‘A’ defined as wrong kind of tag
    RED, GREEN, BLUE
};

void A(); // no error (collision) here

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
