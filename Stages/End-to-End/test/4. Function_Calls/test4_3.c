// test case for nested function calls
// Output: Result is 12
#include <stdio.h>

int bar(int a) {
    return a + 1;
}
int foo(int b) {
    return bar(b) * 2;
}
int main() {
    int result = foo(5); // Change this value to test with different inputs
    printf("Result is %d\n", result);
    return 0;
}