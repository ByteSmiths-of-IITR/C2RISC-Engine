// Testing Multiple Declarations

int foo(int, int);

int foo(int a, int b) {
    return a + b;
}

int main(){
    int a = 10;
    int b = 20;
    int c = foo(a, b);
    // printf("Sum: %d\n", c);
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
// 0          : foo                           
// 1          : $0 = a$1 + b$1                
// 2          : return $0                     
// 3          : main                          
// 4          : a$2 = 10                      
// 5          : b$2 = 20                      
// 6          : param a$2                     
// 7          : param b$2                     
// 8          : $1 = call foo, 2              
// 9          : c$2 = $1                      
// 10         : return 0                      
// 
