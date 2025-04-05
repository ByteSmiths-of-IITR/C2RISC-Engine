/* switch-case */
// NO ERROR

int main() {
    int a = 2;
    const int b = 3, c = 4;

    switch (a) {
        case (b+c):
            a = 10;
            break;
        case 5:
            a++;
            // if(a = 3) {a = 30;}
            break;
        default:
            a = 30;
        // default: // error: multiple default labels in one switch
        //     a = 40;
    }

    // case 3: // error: error: case label not within a switch statement
    //     a = 20;
    //     break;

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
// 1          : a$1 = 2                       
// 2          : b$1 = 3                       
// 3          : c$1 = 4                       
// 4          : goto L(13)                    
// 5          : $0 = 0 + 0                    
// 6          : a$1 = 10                      
// 7          : goto L(16)                    
// 8          : $1 = a$1                      
// 9          : a$1 = a$1 + 1                 
// 10         : goto L(16)                    
// 11         : a$1 = 30                      
// 12         : goto L(16)                    
// 13         : if a$1 == $0 goto L(6)        
// 14         : if a$1 == 5 goto L(8)         
// 15         : goto L(11)                    
// 
