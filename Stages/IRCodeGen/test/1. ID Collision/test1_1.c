// function and variable name collision

int func = 10;

int func(){ // error: ‘func’ redeclared as different kind of symbol
    int x = 10;
    return x;
}

int main(){
    int func = 30; // no error
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Function Definition "func" collision with variable
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : func$0 = 10                   
// 
// 1          : main                          
// 2          : func$1 = 30                   
// 3          : return 0                      
// 
