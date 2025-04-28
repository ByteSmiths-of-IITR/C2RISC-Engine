// simple test case to check the working of function pointer
// OUTPUT : Result: 15 

#include <stdio.h>

int add(int a, int b) { return a + b; } // function definition
int (*funcPtr)(int, int); // function pointer declaration

int main() {
    funcPtr = add; // function pointer assignment
    int result = funcPtr(5, 10); // function pointer call
    // printf("Result: %d\n", result); // print the result
    return 0;
}