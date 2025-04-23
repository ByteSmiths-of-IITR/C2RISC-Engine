#include <stdio.h>

int func()
{
    int a[3] = {1, 2, 3};
    float b;
    int *ptr = &a[0];
    a[1]++;
    // char *str = "Hello";
    printf("%d\n", a[1]);
    // int b = a++;
    return 0;
}

int main()
{
    int arr[4];
    int *p = arr + 1;
    // int x = arr[a];
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 🌴 APTree 🌴 has been generated, can be used for debugging ❤️‍🩹 
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Initializer "$17" is not a scalar
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// .rodata section : ------------------------------
// @str$10 : c"%d\n\0" 
// 
// ----------------------------------------------
// .data section : ------------------------------
// $0 = [ 1,2,3 ] 
// 
// ----------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : func                          
// 1          : allocate 12 bytes to a$1      
// 2          : a$1 = mem_copy $0             
// 3          : allocate 4 bytes to b$1       
// 4          : allocate 8 bytes to ptr$1     
// 5          : $1 = a$1.offset               
// 6          : $2 = 0 * 4                    
// 7          : $3 = $1 + $2                  
// 8          : $4 = $3                       
// 9          : ptr$1 = $4                    
// 10         : $5 = a$1.offset               
// 11         : $6 = 1 * 4                    
// 12         : $7 = $5 + $6                  
// 13         : $8 = *$7                      
// 14         : $9 = $8 + 1                   
// 15         : *$7 = $9                      
// 16         : $11 = a$1.offset              
// 17         : $12 = 1 * 4                   
// 18         : $13 = $11 + $12               
// 19         : param @str$10                 
// 20         : param $13                     
// 21         : $14 = call printf, 2          
// 22         : return 0                      
// 
// 23         : main                          
// 24         : allocate 16 bytes to arr$2    
// 25         : allocate 8 bytes to p$2       
// 26         : $15 = arr$2.offset            
// 27         : $16 = 1 * 4                   
// 28         : $17 = $15 + $16               
// 29         : return 0                      
// 
