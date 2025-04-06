#include <stdio.h>
#include <stdarg.h>

void printInts(int count, ...)
{
    va_list args;
    va_start(args, count); // initialize with the last fixed argument

    for (int i = 0; i < count; ++i)
    {
        int val = va_arg(args, int); // fetch next argument
        printf("%d ", val);
    }

    va_end(args); // clean up
    // printf("\n");
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 🌴 APTree 🌴 has been generated, can be used for debugging ❤️‍🩹 
// 
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// .rodata section : ------------------------------
// @str$3 : c"%d \00" 
// 
// ----------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : printInts                     
// 1          : param args$1                  
// 2          : param count$1                 
// 3          : $0 = call va_start, 2         
// 4          : $1 = i$2 < count$1            
// 5          : if $1 goto L(7)               
// 6          : goto L(15)                    
// 7          : param args$1                  
// 8          : param int                     
// 9          : $2 = call va_arg, 2           
// 10         : param @str$3                  
// 11         : param val$3                   
// 12         : $4 = call printf, 2           
// 13         : $5 = i$2 + 1                  
// 14         : goto L(4)                     
// 15         : param args$1                  
// 16         : $6 = call va_end, 1           
// 
