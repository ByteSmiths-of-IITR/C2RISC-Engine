
#include <stdio.h>

int main()
{
    static int a;
    a = 10;
    printf("Hello%d", a);
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
//            : @str$0:   .string    "Hello%d" 
//            : a_s_1:    .zero      4         
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : a_s_1 = 10                    
// 2          : param @str$0                  
// 3          : param a_s_1                   
// 4          : alloca $1, 0                  
// 5          : $1 = call printf, 2           
// 6          : return                        
// 7          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .data      : ------------------------------
//            : @str$0:   .string    "Hello%d" 
//            : a_s_1:    .zero      4         
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : a_s_1 = 10                    
// 2          : param @str$0                  
// 3          : param a_s_1                   
// 4          : alloca $1, 0                  
// 5          : $1 = call printf, 2           
// 6          : return                        
// 7          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
