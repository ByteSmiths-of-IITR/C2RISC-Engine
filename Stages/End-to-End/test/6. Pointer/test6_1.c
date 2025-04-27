// a simple test case to check if the pointer (and multi-lvl ptr) is working
// OUTPUT : Value: 42 42

#include <stdio.h>

int main() {
    int value = 42;
    int *ptr = &value; // pointer to value
    int **ptr2 = &ptr; // pointer to pointer to value

    printf("Value: %d %d\n", *ptr, **ptr2); // dereferencing the pointer
    return 0;
}