
// test case for simple if and if else and if else if ladder
// Output : c is the greatest

#include <stdio.h>

int main()
{
    int a = 7;
    int *p = &a;
    *p = 10;
    printVar(a);
    int b = a;
    printVar(b);
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
// .data      : ------------------------------
//            : str_0:    .string    "Hello World"
// .text      : ------------------------------
// 0          : main: Func with 0 args        
// 1          : param str_0                   
// 2          : alloca $0, 0                  
// 3          : $0 = call printString, 1      
// 4          : return 0                      
// 5          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .data      : ------------------------------
//            : str_0:    .string    "Hello World"
// .text      : ------------------------------
// 0          : main: Func with 0 args        
// 1          : param str_0                   
// 2          : alloca $0, 0                  
// 3          : $0 = call printString, 1      
// 4          : return 0                      
// 5          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
