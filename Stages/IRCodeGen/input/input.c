
struct A {
    int a;
    int b;
    float c;
};

int main(){
    int arr[4][7][5];
    arr[2][4][0]++;
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 🔺 APTree generated as DOT file: build/annotated_ast_graph.dot can be visualized using Graphviz
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : main                          
// 1          : $0 = arr$1.offset             
// 2          : $1 = 2 * 140                  
// 3          : $2 = $0 + $1                  
// 4          : $3 = 4 * 20                   
// 5          : $4 = $2 + $3                  
// 6          : $5 = 0 * 4                    
// 7          : $6 = $4 + $5                  
// 8          : $7 = *$6                      
// 9          : $8 = $7 + 1                   
// 10         : *$6 = $8                      
// 11         : return 0                      
// 
// 
