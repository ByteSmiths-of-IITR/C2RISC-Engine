

#include <stdio.h>

int factorial(int n)
{
    if (n <= 0)
        return 0;
    else
        return n * factorial(n - 1);
}

int main()
{
    int a = 5;
    int result = factorial(a);
    printVar(result);
    return 0;
}