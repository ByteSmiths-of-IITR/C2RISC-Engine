// Function calling before declaration 

int main(){
    func(); // error: implicit declaration of function 'func'
    return 0;
}

void func(){
    int a = 1;
    return;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Identifier "func" not 🫠 found in the current scope
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : return 0                      
// 
// 2          : func                          
// 3          : a$2 = 1                       
// 4          : return                        
// 
