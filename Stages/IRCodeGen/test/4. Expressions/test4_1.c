/*
primary_expression
    : IDENTIFIER
    | CONSTANT
    | STRING_LITERAL
    | LPAREN expression RPAREN
    ;
*/

int main() {
    int a = 10;

    const int b = 20;
    
    "Hello World";
    
    (a + b);

    // Negative Cases
    10++;  // error: lvalue required as increment operand
    "Hello"--;  // error: lvalue required as decrement operand
    
    return 0;
}
