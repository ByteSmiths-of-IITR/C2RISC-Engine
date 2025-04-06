int main() {
    int a = 10;

    float b = 20f;
    
    // "Hello World";
    
    (a + b);

    // Negative Cases
    // 10++;  // error: lvalue required as increment operand
    // "Hello"--;  // error: lvalue required as decrement operand
    
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
// 1          : a$1 = 10                      
// 2          : b$1 = 20.000000               
// 3          : a$1 = (float)a$1              
// 4          : $0 = a$1 + b$1                
// 5          : return 0                      
// 
