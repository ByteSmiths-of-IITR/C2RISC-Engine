
#include <stdio.h>

int main()
{
    int arr[2][3];
    int (*ptr)[3];
    ptr = arr; // pointer to array of 3 integers

    // printf("Value: %d %d\n", (*ptr)[0], (*ptr)[1]); // dereferencing the pointer to access array elements
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// 🌴 APTree 🌴 has been generated, can be used for debugging ❤️‍🩹 
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | Machine Independent Optimization 👍 |  🔖 IRCode Gen
// 😊 Thanku for using our "C2RISC-Engine" (Till IR Phase) 
// 
// ----------------------------------------------------------------------------------------------------
// 
// 
//  ---- IR Code Before Machine Independent Optimization ---- 
// .text      : ------------------------------
// 0          : main: Func with 0 args        
// 1          : alloca arr$1, 24              
// 2          : alloca ptr$1, 4               
// 3          : ptr$1 = arr$1                 
// 4          : return 0                      
// 5          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .text      : ------------------------------
// 0          : main: Func with 0 args        
// 1          : alloca arr$1, 24              
// 2          : alloca ptr$1, 4               
// 3          : ptr$1 = arr$1                 
// 4          : return 0                      
// 5          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
