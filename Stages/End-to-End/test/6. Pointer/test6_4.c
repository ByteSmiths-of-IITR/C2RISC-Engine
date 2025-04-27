// deferencing a three level pointer in 3D array
// OUTPUT : Value: 1 1 1

#include <stdio.h>

int main() {
    int arr[2][3][4] = {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}, {{13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22, 23, 24}}}; // 3D array initialization
    int (*ptr)[3][4] = arr; // pointer to array of 3 arrays of 4 integers

    printf("Value: %d %d %d\n", (*ptr)[0][0], (**ptr)[0], (***ptr)); // dereferencing the pointer to access array elements
    return 0;
}