
// test case for simple if and if else and if else if ladder
// Output : c is the greatest

#include <stdio.h>

int factorial(int n)
{
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

int main()
{
    int k = factorial(3);
}
//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | Machine Independent Optimization 👍 |  🔖 IRCode Gen
// 😊 Thanku for using our "C2RISC-Engine" (Till IR Phase) 
// 
// ----------------------------------------------------------------------------------------------------
// 
// 
//  ---- IR Code Before Machine Independent Optimization ---- 
// .text      : ------------------------------
// 0          : factorial: Func ENTER         
// 1          : alloca n$1, 4                 
// 2          : alloca $0, 4                  
// 3          : $0 = n$1 == 0                 
// 4          : if $0 goto L(6)               
// 5          : goto L(8)                     
// 6          : return 1                      
// 7          : goto L(16)                    
// 8          : alloca $1, 4                  
// 9          : $1 = n$1 - 1                  
// 10         : param $1                      
// 11         : alloca $2, 4                  
// 12         : $2 = call factorial, 1        
// 13         : alloca $3, 4                  
// 14         : $3 = n$1 * $2                 
// 15         : return $3                     
// 16         : factorial ret(4): EXIT        
// 
// 17         : main: Func ENTER              
// 18         : alloca k$2, 4                 
// 19         : param 3                       
// 20         : alloca $4, 4                  
// 21         : $4 = call factorial, 1        
// 22         : k$2 = $4                      
// 23         : return                        
// 24         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .text      : ------------------------------
// 0          : factorial: Func ENTER         
// 1          : alloca n$1, 4                 
// 2          : alloca $0, 4                  
// 3          : $0 = n$1 == 0                 
// 4          : if $0 goto L(6)               
// 5          : goto L(8)                     
// 6          : return 1                      
// 7          : goto L(16)                    
// 8          : alloca $1, 4                  
// 9          : $1 = n$1 - 1                  
// 10         : param $1                      
// 11         : alloca $2, 4                  
// 12         : $2 = call factorial, 1        
// 13         : alloca $3, 4                  
// 14         : $3 = n$1 * $2                 
// 15         : return $3                     
// 16         : factorial ret(4): EXIT        
// 
// 17         : main: Func ENTER              
// 18         : alloca k$2, 4                 
// 19         : param 3                       
// 20         : alloca $4, 4                  
// 21         : $4 = call factorial, 1        
// 22         : k$2 = $4                      
// 23         : return                        
// 24         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
