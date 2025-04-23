/* goto - simpler version */

int main() {
    int a = 0;

    goto label;
    a = 10; // This statement is skipped

    label:
    a = 20;
    
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Function 'main's return type is not void but no return statement found
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : a$1 = 0                       
// 2          : goto L(4)                     
// 3          : a$1 = 10                      
// 4          : a$1 = 20                      
// 
