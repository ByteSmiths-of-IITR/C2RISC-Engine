#include <stdio.h>

int main()
{
    // Variable Declarations
    char c = 'A';
    float x = 10.5, y = 2.3;
    double d = 3.14159;
    int *ptr = NULL;
    int arr[3] = {1, 2, 3};

    // Multi-Dimensional Array
    int matrix[2][2] = {{1, 2}, {3, 4}};
    printf("Multi-Dimensional Array:\n");
    printf("  %d %d\n", matrix[0][0], matrix[0][1]);
    

    // Bitwise Operations
    int a = 5, b = 3;
    int and_op = a & b;
    int or_op = a | b;
    int xor_op = a ^ b;
    int left_shift = a << 1;
    int right_shift = b >> 1;
    printf("Bitwise Operations:\n");
    printf("  %d & %d = %d\n", a, b, and_op);
    printf("  %d | %d = %d\n", a, b, or_op);
    printf("  %d ^ %d = %d\n", a, b, xor_op);
    printf("  %d << 1 = %d\n", a, left_shift);
    printf("  %d >> 1 = %d\n\n", b, right_shift);

    // Switch case
    int num = 2;
    switch (num)
    {
    case 1:
        printf("Number is 1\n");
        break;
    case 2:
        printf("Number is 2\n");
        break;
    default:
        printf("Number is unknown\n");
    }

    // Nested Loops: Multiplication Table
    printf("Multiplication Table (1-3):\n");
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            printf("%d x %d = %d\t", i, j, i * j);
        }
        printf("\n");
    }

    // Ternary Operator
    int min = (a < b) ? a : b;
    printf("Minimum of %d and %d is %d\n\n", a, b, min);

    // Function Pointer
    void (*funcPtr)();
    funcPtr = main;
    printf("Function pointer assigned\n\n");

    return 0;
}