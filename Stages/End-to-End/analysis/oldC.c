int add(int a, int b) // declaration_specifiers (int), declarator (add(int a, int b))
    int result;       // declaration_list (declaration inside the function before the body)
{
    result = a + b; // compound_statement
    return result;
}

//////////

multiply(a, b) // declarator (multiply(a, b)) - treated as int by default
    int a,
    b; // declaration_list (K&R C style function definition)
{
    return a * b; // compound_statement
}

//////////

divide(a, b) // declarator (divide(a, b)) - treated as int by default
{
    if (b != 0)
        return a / b; // compound_statement
    return 0;         // Error handling
}