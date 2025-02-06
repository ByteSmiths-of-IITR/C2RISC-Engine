#include <stdio.h>

typedef int myInt;

static myInt x = 10;

int main() {
    myInt a = 5, b = 10, c;
    c = a + b * x / 2 - (a && b || !x);  // Arithmetic & Logical Operators
    
    if (c > 20)
        printf("Large\n");
    else
        printf("Small\n");

    return 0;
}
