/*
cast_expression
    : unary_expression
    | LPAREN type_name RPAREN cast_expression
    ;
*/
int main() {
    float f = 3.14;
    int a = (int) f;

    // Negative Cases
    int b = (void) f; // error: void value not ignored as it ought to be

    return 0;
}