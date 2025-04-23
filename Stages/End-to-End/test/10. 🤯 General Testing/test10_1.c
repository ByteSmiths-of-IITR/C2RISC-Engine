
#include <stdio.h>
int main()
{
    int i = 1, a = 1;
    switch (i)
    {
        // printf("ANVIT");
        int a = 1;
        switch (i)
        {
        case 0:
            // printf("C C i = 0\n");
            int ed = 1;
            break;
            int ad = 1;
        }
        int adfe = 0;
    case 1:
        // printf("C i = 1\n");
        adfe = 1;
        switch (i)
        {
        case 1:
            // printf("C C i = 1\n");
            break;
        }
        break;
    case 2:
        // printf("C i = 2\n");
        break;
    default:
        // printf("C i = default\n");
        break;
    }

    // printf("a = %d\n", a);
    // // printf("ed = %d\n", ed);
    // printf("i = %d\n", i);

    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : i$1 = 1                       
// 2          : a$1 = 1                       
// 3          : goto L(21)                    
// 4          : a$2 = 1                       
// 5          : goto L(10)                    
// 6          : ed$3 = 1                      
// 7          : goto L(11)                    
// 8          : ad$3 = 1                      
// 9          : goto L(11)                    
// 10         : if i$1 == 0 goto L(6)         
// 11         : adfe$2 = 0                    
// 12         : adfe$2 = 1                    
// 13         : goto L(16)                    
// 14         : goto L(17)                    
// 15         : goto L(17)                    
// 16         : if i$1 == 1 goto L(14)        
// 17         : goto L(24)                    
// 18         : goto L(24)                    
// 19         : goto L(24)                    
// 20         : goto L(24)                    
// 21         : if i$1 == 1 goto L(12)        
// 22         : if i$1 == 2 goto L(18)        
// 23         : goto L(19)                    
// 24         : return 0                      
// 
