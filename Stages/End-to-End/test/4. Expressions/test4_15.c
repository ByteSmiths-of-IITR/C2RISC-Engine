#include <stdio.h>

int increment(int *x)
{
    (*x)++;
    return *x;
}

int main()
{
    int a = 5, b = 3, c = 0;

    // Complex expression using short-circuiting, increment, ternary, and bitwise
    int result = (a > b && increment(&c)) || ((a ^ b) & ~(c | 1)) ? a + b * c : a - b / (c + 1);

    printf("a = %d, b = %d, c = %d\n", a, b, c);
    printf("result = %d\n", result);

    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// .rodata section : ------------------------------
// @str$18 : c"a = %d, b = %d, c = %d\n\0" 
// @str$20 : c"result = %d\n\0" 
// 
// ----------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : increment                     
// 1          : $0 = *x$1                     
// 2          : $1 = $0 + 1                   
// 3          : *x$1 = $1                     
// 4          : $2 = *x$1                     
// 5          : return $2                     
// 
// 6          : main                          
// 7          : a$2 = 5                       
// 8          : b$2 = 3                       
// 9          : c$2 = 0                       
// 10         : $3 = a$2 > b$2                
// 11         : $4 = &c$2                     
// 12         : param $4                      
// 13         : $5 = call increment, 1        
// 14         : $6 = $3 && $5                 
// 15         : $7 = a$2 ^ b$2                
// 16         : $8 = c$2 | 1                  
// 17         : $9 = ~ $8                     
// 18         : $10 = &$7                     
// 19         : $11 = $6 || $10               
// 20         : ifFalse $11 goto L(25)        
// 21         : $13 = b$2 * c$2               
// 22         : $14 = a$2 + $13               
// 23         : $12 = $14                     
// 24         : goto L(29)                    
// 25         : $15 = c$2 + 1                 
// 26         : $16 = b$2 / $15               
// 27         : $17 = a$2 - $16               
// 28         : $12 = $17                     
// 29         : result$2 = $12                
// 30         : param @str$18                 
// 31         : param a$2                     
// 32         : param b$2                     
// 33         : param c$2                     
// 34         : $19 = call printf, 4          
// 35         : param @str$20                 
// 36         : param result$2                
// 37         : $21 = call printf, 2          
// 38         : return 0                      
// 
