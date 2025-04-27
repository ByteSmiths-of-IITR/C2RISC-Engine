// a complex test case to test multi level arrays and pointers combined
// OUTPUT : Value: 1 2

#include <stdio.h>

int main() {
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}}; // 2D array initialization
    int (*ptr)[3] = arr; // pointer to array of 3 integers

    printf("Value: %d %d\n", (*ptr)[0], (*ptr)[1]); // dereferencing the pointer to access array elements
    return 0;
}