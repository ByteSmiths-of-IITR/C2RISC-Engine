/*
assignment_operator
    : ASSIGN
    | MUL_ASSIGN
    | DIV_ASSIGN
    | MOD_ASSIGN
    | ADD_ASSIGN
    | SUB_ASSIGN
    | LEFT_ASSIGN
    | RIGHT_ASSIGN
    | AND_ASSIGN
    | XOR_ASSIGN
    | OR_ASSIGN
    ;
*/
int main() {
    int *a;
    a = 10;
    a += 5;
    a -= 3;
    a *= 2;
    a /= 2;
    a %= 3;
    a <<= 1;
    a >>= 1;
    a &= 1;
    a ^= 1;
    a |= 1;
    
    // Negative Cases
    a = 'c'; // error: assignment to 'int' from 'char *' makes integer from pointer without a cast
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
// 1          : a$1 = 10                      
// 2          : a$1 = 5 + 4                   
// 3          : a$1 = 3 - 4                   
// 4          : a$1 = 2 * 4                   
// 5          : a$1 = 2 / 4                   
// 6          : a$1 = 3 % 4                   
// 7          : a$1 = 1 << 4                  
// 8          : a$1 = 1 >> 4                  
// 9          : a$1 = &1                      
// 10         : a$1 = 1 ^ 4                   
// 11         : a$1 = 1 | 4                   
// 12         : a$1 = c                       
// 13         : return 0                      
// 
// 
