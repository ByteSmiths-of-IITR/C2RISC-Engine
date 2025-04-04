/*
postfix_expression
    : primary_expression
    | postfix_expression LSQUARE expression RSQUARE
    | postfix_expression LPAREN RPAREN
    | postfix_expression LPAREN argument_expression_list RPAREN
    | postfix_expression DOT IDENTIFIER
    | postfix_expression PTR_OP IDENTIFIER
    | postfix_expression INC_OP
    | postfix_expression DEC_OP
    ;
*/

struct Test { int x; } t;

int arr[10];

int *ptr;

int main() {
    a[0]; 
    func(); 
    func(a, b); // error: ‘b’ undeclared (first use in this function)

    t.x;
    ptr->x; //  error: request for member ‘x’ in something not a structure or union

    a++; 
    a--; 

    // Negative Cases
    arr();  // error: called object ‘arr’ is not a function or function pointer
    t->x;  // error: invalid type argument of ‘->’ (have ‘struct Test’)
    
    return 0;
}