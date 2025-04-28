// Test case : Expression evaluation
// Output : Result: 15.640000
#include <stdio.h>

int main()
{
    int a = 5;
    int b = 10;
    int c = (a + b) * 2;
    int d = (a << 1) + (b >> 1);

    printVar(c);
    printVar(d);
    return 0;
}