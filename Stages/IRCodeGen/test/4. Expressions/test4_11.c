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

enum COLOR {
    RED,
    GREEN,
    BLUE
};
int main() {
    int *a;
    int b;
    enum COLOR c;

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

    b = 10;
    b += 5;
    b -= 3;
    b *= 2;
    b /= 2;
    b %= 3;
    b <<= 1;
    b >>= 1;
    b &= 1;
    b ^= 1;
    b |= 1;

    c = RED;
    c += 1;
    
    // Negative Cases
    a = 'c'; // error: assignment to 'int' from 'char *' makes integer from pointer without a cast
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : For Operator "=" assignment expression's operand "a$1" or "10" is not compatible
// SEMANTIC ERROR ‼️ : For Operator "*=" assignment expression's operand "a$1" or "2" is not a numeric type
// SEMANTIC ERROR ‼️ : For Operator "/=" assignment expression's operand "a$1" or "2" is not a numeric type
// SEMANTIC ERROR ‼️ : For Operator "%=" assignment expression's operand "a$1" or "3" is not a numeric type
// SEMANTIC ERROR ‼️ : For Operator "<<=" assignment expression's operand "a$1" or "1" is not a numeric type
// SEMANTIC ERROR ‼️ : For Operator ">>=" assignment expression's operand "a$1" or "1" is not a numeric type
// SEMANTIC ERROR ‼️ : For Operator "&=" assignment expression's operand "a$1" or "1" is not a numeric type
// SEMANTIC ERROR ‼️ : For Operator "^=" assignment expression's operand "a$1" or "1" is not a numeric type
// SEMANTIC ERROR ‼️ : For Operator "|=" assignment expression's operand "a$1" or "1" is not a numeric type
// SEMANTIC ERROR ‼️ : For Operator "=" assignment expression's operand "a$1" or "c" is not compatible
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : $0 = (int *)5                 
// 2          : a$1 = $0 + 4                  
// 3          : $1 = (int *)3                 
// 4          : a$1 = $1 - 4                  
// 5          : b$1 = 10                      
// 6          : b$1 = 5 + 1                   
// 7          : b$1 = 3 - 1                   
// 8          : b$1 = 2 * 1                   
// 9          : b$1 = 2 / 1                   
// 10         : b$1 = 3 % 1                   
// 11         : b$1 = 1 << 1                  
// 12         : b$1 = 1 >> 1                  
// 13         : b$1 = &1                      
// 14         : b$1 = 1 ^ 1                   
// 15         : b$1 = 1 | 1                   
// 16         : c$1 = 0                       
// 17         : c$1 = 1 + 1                   
// 18         : return 0                      
// 
