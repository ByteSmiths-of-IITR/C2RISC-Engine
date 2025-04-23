
int main()
{
    int a = 1, b = 3, c = 0, d = 4;
    int done = 1;

    // Simulated UNTIL loop: run until `done == true`
    until(!done)
    {
        // Nested condition updating flag
        if ((a + b + c) % 5 == 0 || (c & 1))
        {
            done = 3;
        }

        // Mutate state further in tricky ways
        a ^= (b << 1); // bitwise XOR with shifted b
        b ^= (a >> 2); // reverse logic
    }

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
// 1          : a$1 = 1                       
// 2          : b$1 = 3                       
// 3          : c$1 = 0                       
// 4          : d$1 = 4                       
// 5          : done$1 = 1                    
// 6          : $0 = ! done$1                 
// 7          : if $0 goto L(9)               
// 8          : goto L(23)                    
// 9          : $1 = a$1 + b$1                
// 10         : $2 = $1 + c$1                 
// 11         : $3 = $2 % 5                   
// 12         : $4 = $3 == 0                  
// 13         : $5 = &c$1                     
// 14         : $6 = $4 || $5                 
// 15         : if $6 goto L(17)              
// 16         : goto L(18)                    
// 17         : done$1 = 3                    
// 18         : $7 = b$1 << 1                 
// 19         : a$1 = $7 ^ 1                  
// 20         : $8 = a$1 >> 2                 
// 21         : b$1 = $8 ^ 1                  
// 22         : goto L(6)                     
// 23         : return 0                      
// 
