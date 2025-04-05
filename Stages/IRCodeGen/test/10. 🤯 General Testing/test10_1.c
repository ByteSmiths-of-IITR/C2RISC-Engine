
#include <stdio.h>
int main()
{
    int i = 1, a = 1;
    switch (i)
    {
        printf("ANVIT");
        switch (i)
        {
        case 0:
            printf("C C i = 0\n");
            break;
        }
        int adfe;
    case 1:
        printf("C i = 1\n");
        adfe = 1;
        switch (i)
        {
        case 1:
            printf("C C i = 1\n");
            break;
        }
        break;
    case 2:
        printf("C i = 2\n");
        break;
    default:
        printf("C i = default\n");
        break;
    }

    printf("a = %d\n", a);
    // printf("ed = %d\n", ed);
    printf("i = %d\n", i);

    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Identifier "printf" not 🫠 found in the current scope
// SEMANTIC ERROR ‼️ : Identifier "printf" not 🫠 found in the current scope
// SEMANTIC ERROR ‼️ : Identifier "printf" not 🫠 found in the current scope
// SEMANTIC ERROR ‼️ : Identifier "printf" not 🫠 found in the current scope
// SEMANTIC ERROR ‼️ : Identifier "printf" not 🫠 found in the current scope
// SEMANTIC ERROR ‼️ : Identifier "printf" not 🫠 found in the current scope
// SEMANTIC ERROR ‼️ : Identifier "printf" not 🫠 found in the current scope
// SEMANTIC ERROR ‼️ : Identifier "printf" not 🫠 found in the current scope
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : main                          
// 1          : i$1 = 1                       
// 2          : a$1 = 1                       
// 3          : goto L(17)                    
// 4          : goto L(7)                     
// 5          : goto L(8)                     
// 6          : goto L(8)                     
// 7          : if i$1 == 0 goto L(5)         
// 8          : adfe$2 = 1                    
// 9          : goto L(12)                    
// 10         : goto L(13)                    
// 11         : goto L(13)                    
// 12         : if i$1 == 1 goto L(10)        
// 13         : goto L(20)                    
// 14         : goto L(20)                    
// 15         : goto L(20)                    
// 16         : goto L(20)                    
// 17         : if i$1 == 1 goto L(8)         
// 18         : if i$1 == 2 goto L(14)        
// 19         : goto L(15)                    
// 
