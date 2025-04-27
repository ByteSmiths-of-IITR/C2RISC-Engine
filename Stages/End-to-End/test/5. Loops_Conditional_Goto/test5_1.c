// test case for simple if and if else and if else if ladder
// Output : c is the greatest

#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30;
    if (a > b) {
        printf("a is greater than b\n");
    } else if (b > c) {
        printf("b is greater than c\n");
    } else {
        printf("c is the greatest\n");
    }
    return 0;
}