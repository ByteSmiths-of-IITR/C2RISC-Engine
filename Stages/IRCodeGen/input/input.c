// function and variable name collision

#include <stdio.h>
// typedef int INT;
// struct A
// {
//     int x;
// };

int main(){
    int arr[10][5];
    int f;
    int k = arr[1]++;
}

//=========================== C2RISC-Engine ==========================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// 
// 🚨 Input Program failed in Semantic Analysis Phase 🚨
// 
// ----------------------------------- SEMANTIC LOG -----------------------------------
// Error: Inc or Dec expression "$2" is not a pointer or variable type
// ----------------------------------- END OF LOG -----------------------------------
// 🔺 Annotated Parse Tree generated as DOT file: build/annotated_ast_graph.dot can be visualized using Graphviz
// 
