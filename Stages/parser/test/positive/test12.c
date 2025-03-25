#include <stdio.h>

int main()
{
    int val = 100;
    int *ptr1 = &val;    // Single-level pointer
    int **ptr2 = &ptr1;  // Double pointer
    int ***ptr3 = &ptr2; // Triple pointer

    // Modifying value through pointers
    **ptr2 = 200;
    ***ptr3 = 300;

    printf("val = %d\n", val);
    printf("Value using *ptr1 = %d\n", *ptr1);
    printf("Value using **ptr2 = %d\n", **ptr2);
    printf("Value using ***ptr3 = %d\n", ***ptr3);

    // Array of pointers
    int a = 10, b = 20, c = 30;
    int *arr[] = {&a, &b, &c};
    printf("Array of pointers: %d, %d, %d\n", *arr[0], *arr[1], *arr[2]);

    // Pointer arithmetic
    int nums[] = {1, 2, 3, 4, 5};
    int *p = nums;
    printf("Pointer arithmetic: %d, %d\n", *(p + 1), *(p + 3));

    return 0;
}
