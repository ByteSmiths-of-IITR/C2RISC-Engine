// Forward Declaration Without Definition (struct)
struct A;

int main(){
    struct A obj; // error: storage size of ‘obj’ isn’t known
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : RecordID "A" not found
// SEMANTIC ERROR ‼️ : RecordID "A" not found
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : return 0                      
// 
