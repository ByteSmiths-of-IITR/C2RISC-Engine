/*
unary_expression
    : postfix_expression
    | INC_OP unary_expression
    | DEC_OP unary_expression
    | unary_operator cast_expression
    | SIZEOF unary_expression
    | SIZEOF LPAREN type_name RPAREN
    ;
*/

int main() {
    int a = 5;

    ++a;
    --a;
    
    int *p = &a;
    *p;

    sizeof(a);
    sizeof(int);

    // Negative Cases
    sizeof(); // error: expected expression before ‘)’ token
    *10; // error: invalid type argument of unary ‘*’ (have ‘int’)
    
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Function 'main's return type is not void but no return statement found
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : main                          
// 1          : a$1 = 5                       
// 2          : $0 = a$1 + 1                  
// 3          : $1 = a$1 - 1                  
// 4          : $2 = &a$1                     
// 5          : p$1 = $2                      
// 
