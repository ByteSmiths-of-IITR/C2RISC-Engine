
#include <stdio.h>

int main()
{
    static int a;
    a = 10;
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
//            : a_s_1:    .zero      4         
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : a_s_1 = 10                    
// 2          : return                        
// 3          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .data      : ------------------------------
//            : a_s_1:    .zero      4         
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : a_s_1 = 10                    
// 2          : return                        
// 3          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
