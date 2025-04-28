// test case for expression evaluation in a function 
// Output: Result is -3
#include <stdio.h>

int bar(int a) {
    int b = a * 2;
    int c = b + 3;

    return b-c;
}

int main() {
    int result = bar(5); // Change this value to test with different inputs
    // printf("Result is %d\n", result);
    return 0;
}