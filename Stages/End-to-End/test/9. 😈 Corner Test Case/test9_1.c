struct A{
    struct A *next;
}

struct B{
    struct B next;
} b1, b2;

int main(){
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Invalid type specifier (width can't be found) in struct_declaration : struct B S0
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : return 0                      
// 
