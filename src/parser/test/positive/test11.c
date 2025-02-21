#include <stdio.h>

// Function prototypes
int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

// Function pointer typedef
typedef int (*operation)(int, int);

int main()
{
    // Function pointer array
    operation operations[2] = {add, subtract};

    printf("Addition: %d + %d = %d\n", 10, 5, operations[0](10, 5));
    printf("Subtraction: %d - %d = %d\n", 10, 5, operations[1](10, 5));

    // Multi-level function pointer
    operation *ptrToFunc = operations;
    printf("Using pointer to function pointer for addition: %d + %d = %d\n", 20, 10, (*ptrToFunc)(20, 10));

    return 0;
}
