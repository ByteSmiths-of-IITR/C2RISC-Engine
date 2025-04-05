/*
logical_and_expression
    : inclusive_or_expression
    | logical_and_expression AND_OP inclusive_or_expression
    ;

logical_or_expression
    : logical_and_expression
    | logical_or_expression OR_OP logical_and_expression
    ;
*/
int main() {
    int a = 1, b = 0;
    int result = a && b;
    int result2 = a || b;
    
    // NO ERROR
    result = a && a; 
    result = a || 3.5; 

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
// 1          : a$1 = 1                       
// 2          : b$1 = 0                       
// 3          : $0 = a$1 && b$1               
// 4          : result$1 = $0                 
// 5          : $1 = a$1 || b$1               
// 6          : result2$1 = $1                
// 7          : $2 = a$1 && a$1               
// 8          : result$1 = $2                 
// 9          : a$1 = (double)a$1             
// 10         : $3 = a$1 || 3.500000          
// 11         : result$1 = $3                 
// 12         : return 0                      
// 
// 
