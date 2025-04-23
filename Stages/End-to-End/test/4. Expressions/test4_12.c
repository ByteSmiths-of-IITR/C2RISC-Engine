/*conditional_expression
    : logical_or_expression
    | logical_or_expression QUESTION expression COLON conditional_expression
    ;
*/
int main() {
    int a = 10, b = 20;
    int result = (a > b) ? a : b;
    char* f;
    // Negative Cases
    result = (a > b) ? f : a; // Error: assignment to ‘int’ from ‘char *’ makes integer from pointer without a cast

    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Conditional expression requires compatible types, but found "char *" and "int"
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : a$1 = 10                      
// 2          : b$1 = 20                      
// 3          : $0 = a$1 > b$1                
// 4          : ifFalse $0 goto L(7)          
// 5          : $1 = a$1                      
// 6          : goto L(8)                     
// 7          : $1 = b$1                      
// 8          : result$1 = $1                 
// 9          : $2 = a$1 > b$1                
// 10         : ifFalse $2 goto L(13)         
// 11         : $3 = f$1                      
// 12         : goto L(14)                    
// 13         : $3 = a$1                      
// 14         : return 0                      
// 
