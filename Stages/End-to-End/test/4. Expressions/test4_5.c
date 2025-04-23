/*
multiplicative_expression
    : cast_expression
    | multiplicative_expression STAR cast_expression
    | multiplicative_expression DIVIDE cast_expression
    | multiplicative_expression MOD cast_expression
    ;
*/
int main() {
    int a = 10, b = 5;

    int result = a * b;
    
    result = a / b;
    
    result = a % b;

    // Negative Cases
    result = a % 3.5; // error: invalid operands to binary % (have ‘int’ and ‘double’)
    
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Operand % cannot work on types "int" and "double"
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : a$1 = 10                      
// 2          : b$1 = 5                       
// 3          : $0 = a$1 * b$1                
// 4          : result$1 = $0                 
// 5          : $1 = a$1 / b$1                
// 6          : result$1 = $1                 
// 7          : $2 = a$1 % b$1                
// 8          : result$1 = $2                 
// 9          : return 0                      
// 
