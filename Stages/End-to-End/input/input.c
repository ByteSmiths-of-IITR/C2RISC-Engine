
#include <stdio.h>

int main()
{
    static int a;
    a = 10;
    printf("Hello");
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | Machine Independent Optimization 👍 |  🔖 IRCode Gen
// 😊 Thanku for using our "C2RISC-Engine" (Till IR Phase) 
// 
// ----------------------------------------------------------------------------------------------------
// 
// 
//  ---- IR Code Before Machine Independent Optimization ---- 
// .data      : ------------------------------
//            : a_s_1:    .zero      4         
//            : str_0:    .string    "Hello"   
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : a_s_1 = 10                    
// 2          : param str_0                   
// 3          : alloca $0, 0                  
// 4          : $0 = call printf, 1           
// 5          : return                        
// 6          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .data      : ------------------------------
//            : a_s_1:    .zero      4         
//            : str_0:    .string    "Hello"   
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : a_s_1 = 10                    
// 2          : param str_0                   
// 3          : alloca $0, 0                  
// 4          : $0 = call printf, 1           
// 5          : return                        
// 6          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
