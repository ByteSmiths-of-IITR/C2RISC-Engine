/*conditional_expression
    : logical_or_expression
    | logical_or_expression QUESTION expression COLON conditional_expression
    ;
*/
int main() {
    int a = 10, b = 20;
    int result = (a > b) ? a : b;
    
    // Negative Cases
    result = (a > b) ? "test" : a; // Error: assignment to ‘int’ from ‘char *’ makes integer from pointer without a cast

    return 0;
}