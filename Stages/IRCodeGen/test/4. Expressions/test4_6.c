/*
additive_expression
    : multiplicative_expression
    | additive_expression PLUS multiplicative_expression
    | additive_expression MINUS multiplicative_expression
    ;
*/

int main() {
    int a = 10; 
    float b = 5.6;

    int result = a + b;
    
    result = a - b;

    // Negative Cases
    result = a + "hello"; // error: initialization of 'int' from 'char *' makes integer from pointer without a cast
    
    return 0;
}