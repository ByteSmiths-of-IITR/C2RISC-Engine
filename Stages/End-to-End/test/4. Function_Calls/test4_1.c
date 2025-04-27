// test case for simple function call
// Output: Result: 15

#include <stdio.h>

int foo(int a, int b)
{
    return a + b;
}

int main()
{
    int a = 5;
    int b = 10;
    int c = foo(a, b);
    printf("Result: %d\n", c);
    return 0;
}