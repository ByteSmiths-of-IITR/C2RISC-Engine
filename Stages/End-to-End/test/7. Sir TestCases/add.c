
#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int a = -5, b = 10;
    int result = add(a, b);
    printVar(result);
    return 0;
}