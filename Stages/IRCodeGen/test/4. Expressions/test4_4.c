/*
cast_expression
    : unary_expression
    | LPAREN type_name RPAREN cast_expression
    ;
*/
int main() {
    float f = 3.14f;
    int a = (int) f;

    // Negative Cases
    int b = (void) f; // error: void value not ignored as it ought to be

    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Initialization Type Mismatch 😔 for 'a' which is 'int' and initialized it with ''
// SEMANTIC ERROR ‼️ : Function 'main's return type is not void but no return statement found
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : main                          
// 1          : f$1 = 3.140000                
// 
