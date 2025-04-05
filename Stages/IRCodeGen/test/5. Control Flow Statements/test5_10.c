/* goto advanced version */

int main() {
    int i = 0;
    
    loop_start:
    if (i >= 10)
        goto loop_end;
    
    if (i == 5)
        goto break_loop;
    if (i == 3)
        goto continue_loop;
    
    continue_loop:
    i++;
    
    goto loop_start;
    
    break_loop:
    
    loop_end:

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
// 0          : main                          
// 1          : i$1 = 0                       
// 2          : $0 = i$1 >= 10                
// 3          : if $0 goto L(5)               
// 4          : goto L(6)                     
// 5          : goto L(17)                    
// 6          : $1 = i$1 == 5                 
// 7          : if $1 goto L(9)               
// 8          : goto L(10)                    
// 9          : goto L(17)                    
// 10         : $2 = i$1 == 3                 
// 11         : if $2 goto L(13)              
// 12         : goto L(14)                    
// 13         : goto L(14)                    
// 14         : $3 = i$1                      
// 15         : i$1 = i$1 + 1                 
// 16         : goto L(2)                     
// 
