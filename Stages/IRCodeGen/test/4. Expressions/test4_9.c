/*
equality_expression
    : relational_expression
    | equality_expression EQ_OP relational_expression
    | equality_expression NE_OP relational_expression
    ;
*/
int main() {
    int a = 10, b = 20;
    int result = (a == b);
    result = (a != b);
    
    // Negative Cases
    result = a == "test"; // Error: comparison between pointer and integer
    return 0;
}