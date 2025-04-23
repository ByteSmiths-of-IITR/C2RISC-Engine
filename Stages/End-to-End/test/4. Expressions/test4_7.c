/*
shift_expression
    : additive_expression
    | shift_expression LEFT_OP additive_expression
    | shift_expression RIGHT_OP additive_expression
    ;
*/
int main() {
    int a = 4;
    int result = a << 1;
    result = a >> 1;
    
    // Negative Cases
    result = a << -1; // Error: left shift count is negative
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : a$1 = 4                       
// 2          : $0 = a$1 << 1                 
// 3          : result$1 = $0                 
// 4          : $1 = a$1 >> 1                 
// 5          : result$1 = $1                 
// 6          : $2 = 0 - 1                    
// 7          : $3 = a$1 << $2                
// 8          : result$1 = $3                 
// 9          : return 0                      
// 
