// function and variable name collision

int func = 10;

int func()
{ // error: ‘func’ redeclared as different kind of symbol
    // func = 20; // error: lvalue required as left operand of assignment
    int x = 10;
    return x;
}

int main()
{
    int func = 30; // no error
    return 0;
}