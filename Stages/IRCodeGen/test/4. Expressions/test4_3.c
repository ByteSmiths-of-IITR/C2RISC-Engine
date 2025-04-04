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