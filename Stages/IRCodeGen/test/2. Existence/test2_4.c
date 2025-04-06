// variable scope conflict

void func(){
    {
        int A = 2;
    }
    int x = A; // error: ‘A’ undeclared (first use in this function)
}

int main(){
    x = 4; // error: ‘x’ undeclared (first use in this function)
    {
        int a = 2;
    }
    int b = a; // error: ‘a’ undeclared (first use in this function)
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Identifier "A" not 🫠 found in the current scope
// SEMANTIC ERROR ‼️ : Identifier "x" not 🫠 found in the current scope
// SEMANTIC ERROR ‼️ : Identifier "a" not 🫠 found in the current scope
// SEMANTIC ERROR ‼️ : Function 'main's return type is not void but no return statement found
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : func                          
// 1          : A$2 = 2                       
// 
// 2          : main                          
// 3          : a$4 = 2                       
// 
