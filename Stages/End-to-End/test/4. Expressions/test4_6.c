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
    char *str = "Hello";
    // double str = 3.14;
    result =  str-a;
    
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : For Operator "=" assignment expression's operand "result$1" or "$4" is not compatible
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// .rodata section : ------------------------------
// @str$2 : c"Hello\0" 
// 
// ----------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : a$1 = 10                      
// 2          : b$1 = 5.600000                
// 3          : a$1 = (float)a$1              
// 4          : $0 = a$1 + b$1                
// 5          : result$1 = $0                 
// 6          : a$1 = (float)a$1              
// 7          : $1 = a$1 - b$1                
// 8          : result$1 = $1                 
// 9          : str$1 = @str$2                
// 10         : $3 = a$1 * 1                  
// 11         : $4 = str$1 - $3               
// 12         : return 0                      
// 
