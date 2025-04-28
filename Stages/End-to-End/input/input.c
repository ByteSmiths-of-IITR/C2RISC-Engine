
// test case for simple if and if else and if else if ladder
// Output : c is the greatest

#include <stdio.h>

int main()
{
    int a;
    int *p = &a;
    int **pp = &p;
    **pp = 10;
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
// 0          : main: Func ENTER              
// 1          : alloca a$1, 4                 
// 2          : alloca p$1, 4                 
// 3          : alloca $0, 4                  
// 4          : $0 = &a$1                     
// 5          : p$1 = $0                      
// 6          : alloca pp$1, 4                
// 7          : alloca $1, 4                  
// 8          : $1 = &p$1                     
// 9          : pp$1 = $1                     
// 10         : (4)*pp$1 = 10                 
// 11         : return                        
// 12         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca a$1, 4                 
// 2          : alloca p$1, 4                 
// 3          : alloca $0, 4                  
// 4          : $0 = &a$1                     
// 5          : p$1 = $0                      
// 6          : alloca pp$1, 4                
// 7          : alloca $1, 4                  
// 8          : $1 = &p$1                     
// 9          : pp$1 = $1                     
// 10         : (4)*pp$1 = 10                 
// 11         : return                        
// 12         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
