// function and variable name collision

#include <stdio.h>
int main(){
    int a = 0;
    {
        for (int i = 0; i < 10;i++){
            i++;
            int a = 0;
            i++;
        }
    }
}

//=========================== C2RISC-Engine ==========================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 🔺 APTree generated as DOT file: build/annotated_ast_graph.dot can be visualized using Graphviz
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : main                          
// 1          : a$1 = 0                       
// 2          : i$3 = 0                       
// 3          : $0 = i$3 < 10                 
// 4          : if $0 goto L(6)               
// 5          : goto L(14)                    
// 6          : $1 = i$3                      
// 7          : i$3 = i$3 + 1                 
// 8          : a$3 = 0                       
// 9          : $2 = i$3                      
// 10         : i$3 = i$3 + 1                 
// 11         : $3 = i$3                      
// 12         : i$3 = i$3 + 1                 
// 13         : goto L(3)                     
// 
// 
