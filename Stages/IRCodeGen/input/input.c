int main(){
    int a = 10;
    int *ptr = &a;

    int *k = +ptr;
    // 10 ++;

    printf("%p\n", &(+a));
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 🔺 APTree generated as DOT file: build/annotated_ast_graph.dot can be visualized using Graphviz
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : In Unary expression "ptr$1" is not a numeric type
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : main                          
// 1          : a$1 = 10                      
// 2          : $0 = &a$1                     
// 3          : ptr$1 = $0                    
// 
