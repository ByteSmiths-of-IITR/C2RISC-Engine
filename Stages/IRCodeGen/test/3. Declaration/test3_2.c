// use AST to check for proper type assignment for...
// static and const - NO GCC ERROR

static int a1 = 1;
const int b1 = 2;
static const int c1 = 3;
int d1 = 9;

void func(){
    static int a2 = 1;
    const int b2 = 2;
    static const int c2 = 3;
    int d2 = 9;
    return;
}

int main(){
    static int a3 = 1;
    const int b3 = 2;
    static const int c3 = 3;
    int d3 = 9;

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
// 0          : a1$0 = 1                      
// 1          : b1$0 = 2                      
// 2          : c1$0 = 3                      
// 3          : d1$0 = 9                      
// 
// 4          : func                          
// 5          : a2$1 = 1                      
// 6          : b2$1 = 2                      
// 7          : c2$1 = 3                      
// 8          : d2$1 = 9                      
// 9          : return                        
// 
// 10         : main                          
// 11         : a3$2 = 1                      
// 12         : b3$2 = 2                      
// 13         : c3$2 = 3                      
// 14         : d3$2 = 9                      
// 15         : return 0                      
// 
