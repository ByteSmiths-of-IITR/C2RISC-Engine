/*
relational_expression
    : shift_expression
    | relational_expression LESSER_OP shift_expression
    | relational_expression GREATER_OP shift_expression
    | relational_expression LE_OP shift_expression
    | relational_expression GE_OP shift_expression
    ;
*/
int main() {
    int a = 10, b = 20;
    
    int result = a < b;
    result = a > b;
    result = a <= b;
    result = a >= b;
    
    // Negative Cases
    result = a < "hello"; // Error: comparison between pointer and integer
    return 0;
}
