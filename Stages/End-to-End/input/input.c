
// test case for simple if and if else and if else if ladder
// Output : c is the greatest

#include <stdio.h>
int main()
{
    int a = 10;
    printVar(a);
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
// 1          : alloca s$1, 12                
// 2          : alloca $0, 4                  
// 3          : $0 = s$1.offset               
// 4          : alloca $1, 4                  
// 5          : $1 = $0 + 0                   
// 6          : (4)*$1 = 10                   
// 7          : alloca $2, 4                  
// 8          : $2 = s$1.offset               
// 9          : alloca $3, 4                  
// 10         : $3 = $2 + 4                   
// 11         : alloca $4, 4                  
// 12         : $4 = (int)a                   
// 13         : (4)*$3 = $4                   
// 14         : alloca $5, 4                  
// 15         : $5 = s$1.offset               
// 16         : alloca $6, 4                  
// 17         : $6 = $5 + 8                   
// 18         : (4)*$6 = 30                   
// 19         : alloca k$1, 4                 
// 20         : alloca $7, 4                  
// 21         : $7 = s$1.offset               
// 22         : alloca $8, 4                  
// 23         : $8 = $7 + 0                   
// 24         : alloca $9, 4                  
// 25         : $9 = (4)*$8                   
// 26         : k$1 = $9                      
// 27         : return                        
// 28         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .text      : ------------------------------
// 0          : main: Func with 0 args        
// 1          : alloca s$1, 12                
// 2          : alloca $0, 4                  
// 3          : $0 = s$1.offset               
// 4          : alloca $1, 4                  
// 5          : $1 = $0                       
// 6          : (4)*$1 = 10                   
// 7          : alloca $2, 4                  
// 8          : $2 = s$1.offset               
// 9          : alloca $3, 4                  
// 10         : $3 = $2 + 4                   
// 11         : alloca $4, 4                  
// 12         : $4 = (int)a                   
// 13         : (4)*$3 = $4                   
// 14         : alloca $5, 4                  
// 15         : $5 = s$1.offset               
// 16         : alloca $6, 4                  
// 17         : $6 = $5 + 8                   
// 18         : (4)*$6 = 30                   
// 19         : alloca k$1, 4                 
// 20         : alloca $7, 4                  
// 21         : $7 = s$1.offset               
// 22         : alloca $8, 4                  
// 23         : $8 = $7                       
// 24         : alloca $9, 4                  
// 25         : $9 = (4)*$8                   
// 26         : k$1 = $9                      
// 27         : return                        
// 28         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
