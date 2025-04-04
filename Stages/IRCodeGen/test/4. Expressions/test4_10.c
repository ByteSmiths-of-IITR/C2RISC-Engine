/*
logical_and_expression
    : inclusive_or_expression
    | logical_and_expression AND_OP inclusive_or_expression
    ;

logical_or_expression
    : logical_and_expression
    | logical_or_expression OR_OP logical_and_expression
    ;
*/
int main() {
    int a = 1, b = 0;
    int result = a && b;
    int result2 = a || b;
    
    // NO ERROR
    result = a && "hello"; 
    result = a || 3.5; 

    return 0;
}