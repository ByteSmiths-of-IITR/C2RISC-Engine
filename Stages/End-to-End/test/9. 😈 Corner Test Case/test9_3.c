int short long a;
typedef int long MyInt;

char short unsigned b;

int main(){
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Declaration Specifiers Combination is not valid - [ int, short, long ]
// SEMANTIC ERROR ‼️ : Declaration Specifiers Combination is not valid - [ char, short, unsigned ]
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : return 0                      
// 
