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
// 1          : main                          
// 2          : a$2 = 10                      
// 3          : b$2 = 20                      
// 4          : param a$2                     
// 5          : param b$2                     
// 6          : $0 = call foo, 2              
// 7          : c$2 = $0                      
// 
