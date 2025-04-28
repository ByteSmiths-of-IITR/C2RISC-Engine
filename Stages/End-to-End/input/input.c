
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
// 1          : alloca arr$1, 12              
// 2          : alloca $0, 4                  
// 3          : $0 = arr$1.offset             
// 4          : alloca $1, 4                  
// 5          : $1 = 0 * 4                    
// 6          : alloca $2, 4                  
// 7          : $2 = $0 + $1                  
// 8          : (4)*$2 = 10                   
// 9          : alloca $3, 4                  
// 10         : $3 = arr$1.offset             
// 11         : alloca $4, 4                  
// 12         : $4 = 1 * 4                    
// 13         : alloca $5, 4                  
// 14         : $5 = $3 + $4                  
// 15         : (4)*$5 = 20                   
// 16         : alloca $6, 4                  
// 17         : $6 = arr$1.offset             
// 18         : alloca $7, 4                  
// 19         : $7 = 2 * 4                    
// 20         : alloca $8, 4                  
// 21         : $8 = $6 + $7                  
// 22         : (4)*$8 = 30                   
// 23         : return                        
// 24         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca arr$1, 12              
// 2          : alloca $0, 4                  
// 3          : $0 = arr$1.offset             
// 4          : alloca $1, 4                  
// 5          : $1 = 0                        
// 6          : alloca $2, 4                  
// 7          : $2 = $0 + $1                  
// 8          : (4)*$2 = 10                   
// 9          : alloca $3, 4                  
// 10         : $3 = arr$1.offset             
// 11         : alloca $4, 4                  
// 12         : $4 = 4                        
// 13         : alloca $5, 4                  
// 14         : $5 = $3 + $4                  
// 15         : (4)*$5 = 20                   
// 16         : alloca $6, 4                  
// 17         : $6 = arr$1.offset             
// 18         : alloca $7, 4                  
// 19         : $7 = 8                        
// 20         : alloca $8, 4                  
// 21         : $8 = $6 + $7                  
// 22         : (4)*$8 = 30                   
// 23         : return                        
// 24         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
