#include <stdio.h>

sum int(int a, int b)
{ // ❌ `int` should come before function name
    return a + b;
}

int main()
{
    int result = sum(5, 10);
    printf("Sum: %d\n", result);
    return 0;
}
