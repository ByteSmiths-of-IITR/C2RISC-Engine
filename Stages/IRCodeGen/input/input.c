// Online C compiler to run C program online
#include <stdio.h>
struct A
{
    int a;
};
struct B
{
    int a;
};

int main()
{
    // Write C code here
    int p = (2 < 1) ? 4.5 : 2.5;
    short a = 2;
    struct A st, gt;
    struct B s;

    // s = st;

    int *ptr;
    char *pu;
    // ++p=1;
    int k = sizeof((2 < 1) ? 'c' : a);
    int j = sizeof((2 < 1) ? st : gt);
    int x = sizeof((2 < 1) ? st : s);
    int u = sizeof((2 < 1) ? pu : ptr);

    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 🔺 APTree generated as DOT file: build/annotated_ast_graph.dot can be visualized using Graphviz
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Conditional expression requires compatible types, but found "struct A S0" and "struct B S0"
// SEMANTIC ERROR ‼️ : Conditional expression requires compatible types, but found "char *" and "int *"
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : main                          
// 1          : $0 = 2 < 1                    
// 2          : ifFalse $0 goto L(5)          
// 3          : $1 = 4.500000                 
// 4          : goto L(6)                     
// 5          : $1 = 2.500000                 
// 6          : $2 = (int)$1                  
// 7          : p$1 = $2                      
// 8          : $3 = (short)2                 
// 9          : a$1 = $3                      
// 10         : $4 = 2 < 1                    
// 11         : ifFalse $4 goto L(14)         
// 12         : $5 = c                        
// 13         : goto L(15)                    
// 14         : $5 = a$1                      
// 15         : $5 = (int)$5                  
// 16         : $6 = (int)4                   
// 17         : k$1 = $6                      
// 18         : $7 = 2 < 1                    
// 19         : ifFalse $7 goto L(23)         
// 20         : $9 = st$1.offset              
// 21         : $8 = $9                       
// 22         : goto L(25)                    
// 23         : $10 = gt$1.offset             
// 24         : $8 = $10                      
// 25         : $11 = (int)4                  
// 26         : j$1 = $11                     
// 27         : $12 = 2 < 1                   
// 28         : ifFalse $12 goto L(32)        
// 29         : $14 = st$1.offset             
// 30         : $13 = $14                     
// 31         : goto L(34)                    
// 32         : $15 = s$1.offset              
// 33         : $13 = $15                     
// 34         : $16 = 2 < 1                   
// 35         : ifFalse $16 goto L(38)        
// 36         : $17 = pu$1                    
// 37         : goto L(39)                    
// 38         : $17 = ptr$1                   
// 39         : return 0                      
// 
// 
