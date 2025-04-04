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

// ----------------------------------- SEMANTIC LOG -----------------------------------
// Error: Inc or Dec expression "$2" is not a pointer or variable type
// ----------------------------------- END OF LOG -----------------------------------
//  
// CodeLineNo : Three Address Code            
// ---------- : -------------------------------
// 0          : main                          
// 1          : $0 = arr$1.offset             
// 2          : $1 = 1 * 20                   
// 3          : $2 = $0 + $1                  
