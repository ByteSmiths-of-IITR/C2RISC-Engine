/*
equality_expression
    : relational_expression
    | equality_expression EQ_OP relational_expression
    | equality_expression NE_OP relational_expression
    ;
*/
int main() {
    int a = 10, b = 20;
    int result = (a == b);
    result = (a != b);
    
    // Negative Cases
    result = a == 'c'; // Error: comparison between pointer and integer
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
// 3          : $0 = a$1 == b$1               
// 4          : result$1 = $0                 
// 5          : $1 = a$1 != b$1               
// 6          : result$1 = $1                 
// 7          : c = (int)c                    
// 8          : $2 = a$1 == c                 
// 9          : result$1 = $2                 
// 10         : return 0                      
// 
// 
