// use AST to check for proper type assignment for...
// Pointers - NO GCC ERROR

int* p1, p2;
int **pp1;


void func(){
    int x;
    int* ptr1, ptr2;
    int **pptr1;
}

int main(){
    int x;
    int* ptr1, ptr2;
    int **pptr1;

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
// 0          : func                          
// 1          : main                          
// 2          : return 0                      
// 
