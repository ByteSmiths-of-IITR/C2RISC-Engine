int main(){
    int a = 10;
    int *const ptr = &a;

    ptr++; // error: increment of read-only location ‘ptr’

    const int *const ptr2 = &a;
    ptr2++; // error: increment of read-only location ‘ptr2’
    (*ptr2)++; // error: increment of read-only location ‘*ptr2’
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Inc or Dec expression "ptr$1" is not a modifiable lvalue
// SEMANTIC ERROR ‼️ : Inc or Dec expression "ptr2$1" is not a modifiable lvalue
// SEMANTIC ERROR ‼️ : Inc or Dec expression "ptr2$1" is not a modifiable lvalue
// SEMANTIC ERROR ‼️ : Function 'main's return type is not void but no return statement found
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : a$1 = 10                      
// 2          : $0 = &a$1                     
// 3          : ptr$1 = $0                    
// 4          : $1 = &a$1                     
// 5          : ptr2$1 = $1                   
// 
