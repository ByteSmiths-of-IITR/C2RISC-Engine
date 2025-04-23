#include <stdio.h>

union Data
{
    int i;
    float f;
    char c;
};

int main()
{
    union Data data;

    // Assign integer
    data.i = 42;
    printf("Integer: %d\n", data.i);

    // Assign float (overwrites int)
    data.f = 3.14;
    printf("Float  : %f\n", data.f);
    printf("After float, integer: %d (corrupted)\n", data.i); // memory overwritten

    // Assign char (overwrites float)
    data.c = 'A';
    printf("Char   : %c\n", data.c);
    printf("After char, float: %f (corrupted)\n", data.f); // memory overwritten again

    return 0;
}


//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// .rodata section : ------------------------------
// @str$2 : c"Integer: %d\n\0" 
// @str$9 : c"Float  : %f\n\0" 
// @str$13 : c"After float, integer: %d (corrupted)\n\0" 
// @str$19 : c"Char   : %c\n\0" 
// @str$23 : c"After char, float: %f (corrupted)\n\0" 
// 
// ----------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : $0 = data$1.offset            
// 2          : $1 = $0 + 0                   
// 3          : *$1 = 42                      
// 4          : $3 = data$1.offset            
// 5          : $4 = $3 + 0                   
// 6          : param @str$2                  
// 7          : param $4                      
// 8          : $5 = call printf, 2           
// 9          : $6 = data$1.offset            
// 10         : $7 = $6 + 0                   
// 11         : $8 = (float)$7                
// 12         : *$8 = 3.140000                
// 13         : $10 = data$1.offset           
// 14         : $11 = $10 + 0                 
// 15         : param @str$9                  
// 16         : param $11                     
// 17         : $12 = call printf, 2          
// 18         : $14 = data$1.offset           
// 19         : $15 = $14 + 0                 
// 20         : param @str$13                 
// 21         : param $15                     
// 22         : $16 = call printf, 2          
// 23         : $17 = data$1.offset           
// 24         : $18 = $17 + 0                 
// 25         : *$18 = A                      
// 26         : $20 = data$1.offset           
// 27         : $21 = $20 + 0                 
// 28         : param @str$19                 
// 29         : param $21                     
// 30         : $22 = call printf, 2          
// 31         : $24 = data$1.offset           
// 32         : $25 = $24 + 0                 
// 33         : param @str$23                 
// 34         : param $25                     
// 35         : $26 = call printf, 2          
// 36         : return 0                      
// 
