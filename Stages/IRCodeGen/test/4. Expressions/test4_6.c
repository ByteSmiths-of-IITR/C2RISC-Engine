/*
additive_expression
    : multiplicative_expression
    | additive_expression PLUS multiplicative_expression
    | additive_expression MINUS multiplicative_expression
    ;
*/

int main() {
    int a = 10; 
    float b = 5.6f;

    float result = a + b;
    
    result = a - b;

    // Negative Cases
    // char *str = "Hello";
    double str = 3.14;
    result = a + str; // error: initialization of 'int' from 'char *' makes integer from pointer without a cast
    
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
// 2          : b$1 = 5.600000                
// 3          : a$1 = (float)a$1              
// 4          : $0 = a$1 + b$1                
// 5          : result$1 = $0                 
// 6          : a$1 = (float)a$1              
// 7          : $1 = a$1 - b$1                
// 8          : result$1 = $1                 
// 9          : str$1 = 3.140000              
// 10         : a$1 = (double)a$1             
// 11         : $2 = a$1 + str$1              
// 12         : result$1 = $2                 
// 13         : return 0                      
// 
// 
