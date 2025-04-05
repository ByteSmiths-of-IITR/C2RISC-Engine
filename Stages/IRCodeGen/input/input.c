// function and variable name collision

#include <stdio.h>
int main(){
    int i = 0;
    {
        for (int i = 0; i < 10;i++){
            while(1){
                if(1) i++;
                i--;
                continue;
            }
            continue;
        }
    }
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
// 1          : i$1 = 0                       
// 2          : i$3 = 0                       
// 3          : $0 = i$3 < 10                 
// 4          : if $0 goto L(6)               
// 5          : goto L(20)                    
// 6          : if 1 goto L(8)                
// 7          : goto L(16)                    
// 8          : if 1 goto L(10)               
// 9          : goto L(12)                    
// 10         : $1 = i$3                      
// 11         : i$3 = i$3 + 1                 
// 12         : $2 = i$3                      
// 13         : i$3 = i$3 - 1                 
// 14         : goto L(6)                     
// 15         : goto L(6)                     
// 16         : goto L(3)                     
// 17         : $3 = i$3                      
// 18         : i$3 = i$3 + 1                 
// 19         : goto L(3)                     
// 
