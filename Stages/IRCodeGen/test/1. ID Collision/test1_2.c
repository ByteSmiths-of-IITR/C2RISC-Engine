// function and function name collision

int func1(){
    int a = 10;
    return a;
}

float func1(){ // error: conflicting types for ‘func1’; have ‘float()’
    float a = 10.0;
    return a;
}

int func1(int x){ // error: redefinition of ‘func1’
    return x;
}

int main(){
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Redefinition of function "func1"
// SEMANTIC ERROR ‼️ : Redefinition of function "func1"
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : func1                         
// 1          : a$1 = 10                      
// 2          : main                          
// 
