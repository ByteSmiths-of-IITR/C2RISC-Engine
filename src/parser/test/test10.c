#include <stdio.h>

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    return (b != 0) ? a / b : 0;
}

int main() {
    // Function pointer declaration
    int (*funcPtr)(int, int) = multiply;
    printf("Multiplication: %d * %d = %d\n", 6, 7, funcPtr(6,7));

    // Changing the function pointer to point to 'divide'
    funcPtr = divide;
    printf("Division: %d / %d = %d\n", 42, 7, funcPtr(42,7));

    // Multi-level pointer to function pointer
    int (**ptrToFunc)(int, int) = &funcPtr;
    printf("Using multi-level pointer for division: %d / %d = %d\n", 84, 7, (*ptrToFunc)(84,7));
    
    return 0;
}
