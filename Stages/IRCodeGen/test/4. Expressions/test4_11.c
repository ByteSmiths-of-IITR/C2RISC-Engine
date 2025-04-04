/*
assignment_operator
    : ASSIGN
    | MUL_ASSIGN
    | DIV_ASSIGN
    | MOD_ASSIGN
    | ADD_ASSIGN
    | SUB_ASSIGN
    | LEFT_ASSIGN
    | RIGHT_ASSIGN
    | AND_ASSIGN
    | XOR_ASSIGN
    | OR_ASSIGN
    ;
*/
int main() {
    int a;
    a = 10;
    a += 5;
    a -= 3;
    a *= 2;
    a /= 2;
    a %= 3;
    a <<= 1;
    a >>= 1;
    a &= 1;
    a ^= 1;
    a |= 1;
    
    // Negative Cases
    a = "hello"; // error: assignment to 'int' from 'char *' makes integer from pointer without a cast
    return 0;
}