// test case for simple recursive function call
// Output: Fibonacci of 6 is 8

#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    int n = 6; // Change this value to test with different inputs
    int result = fibonacci(n);
    // printf("Fibonacci of %d is %d\n", n, result);
    return 0;
}