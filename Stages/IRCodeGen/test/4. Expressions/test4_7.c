/*
shift_expression
    : additive_expression
    | shift_expression LEFT_OP additive_expression
    | shift_expression RIGHT_OP additive_expression
    ;
*/
int main() {
    int a = 4;
    int result = a << 1;
    result = a >> 1;
    
    // Negative Cases
    result = a << -1; // Error: left shift count is negative
    return 0;
}
