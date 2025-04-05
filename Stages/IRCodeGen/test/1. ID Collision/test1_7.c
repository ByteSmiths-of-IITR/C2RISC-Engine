// same struct ID in different scopes

struct A { int a; };
struct B { int a; };
struct A { char ch; }; // error: redefinition of ‘struct A’

void func(){ // no error
    struct A { float f; };
}

int main() {
    struct A { int a; }; // no error
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : RecordID "A" already 🫠 present in the current scope
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : func                          
// 1          : main                          
// 2          : return 0                      
// 
