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
// SEMANTIC ERROR ‼️ : Function Definition "func1" signature mismatch with previous declaration
// SEMANTIC ERROR ‼️ : Function Definition "func1" signature mismatch with previous declaration
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : func1                         
// 1          : a$1 = 10                      
// 2          : return a$1                    
// 
// 3          : func1                         
// 4          : $0 = (float)10.000000         
// 5          : a$2 = $0                      
// 6          : $1 = (int)a$2                 
// 7          : return $1                     
// 
// 8          : func1                         
// 9          : return x$3                    
// 
// 10         : main                          
// 11         : return 0                      
// 
