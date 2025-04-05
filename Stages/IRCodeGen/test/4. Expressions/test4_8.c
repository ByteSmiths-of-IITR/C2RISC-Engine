/*
relational_expression
    : shift_expression
    | relational_expression LESSER_OP shift_expression
    | relational_expression GREATER_OP shift_expression
    | relational_expression LE_OP shift_expression
    | relational_expression GE_OP shift_expression
    ;
*/
int main() {
    int a = 10, b = 20;
    
    int result = a < b;
    result = a > b;
    result = a <= b;
    result = a >= b;
    
    // Negative Cases
    result = a < b; // Error: comparison between pointer and integer
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
// 0          : main                          
// 1          : a$1 = 10                      
// 2          : b$1 = 20                      
// 3          : $0 = a$1 < b$1                
// 4          : result$1 = $0                 
// 5          : $1 = a$1 > b$1                
// 6          : result$1 = $1                 
// 7          : $2 = a$1 <= b$1               
// 8          : result$1 = $2                 
// 9          : $3 = a$1 >= b$1               
// 10         : result$1 = $3                 
// 11         : $4 = a$1 < b$1                
// 12         : result$1 = $4                 
// 13         : return 0                      
// 
// 
