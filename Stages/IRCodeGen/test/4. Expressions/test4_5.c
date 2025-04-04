/*
multiplicative_expression
    : cast_expression
    | multiplicative_expression STAR cast_expression
    | multiplicative_expression DIVIDE cast_expression
    | multiplicative_expression MOD cast_expression
    ;
*/
int main() {
    int a = 10, b = 5;

    int result = a * b;
    
    result = a / b;
    
    result = a % b;

    // Negative Cases
    result = a % 3.5; // error: invalid operands to binary % (have ‘int’ and ‘double’)
    
    return 0;
}