//multilevel pointers with const at different levels

void main() {
    int a = 10;
    int *p = &a;
    const int **pp = &p;
    const int *const *ppp = &pp;
    //assign to const int **pp
    pp = &p; //error: assignment of read-only location ‘*pp’
    //assign to const int *const *ppp
    ppp = &pp; //error: assignment of read-only location ‘*ppp’
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC Warning ❗️: Initialization type mismatch - Expected : 'const int *const *' Found : 'const int ***'
// SEMANTIC ERROR ‼️ : For Operator "=" assignment expression's operand "ppp$1" or "$4" is not compatible
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : a$1 = 10                      
// 2          : $0 = &a$1                     
// 3          : p$1 = $0                      
// 4          : $1 = &p$1                     
// 5          : pp$1 = $1                     
// 6          : $2 = &pp$1                    
// 7          : ppp$1 = $2                    
// 8          : $3 = &p$1                     
// 9          : pp$1 = $3                     
// 10         : $4 = &pp$1                    
// 
