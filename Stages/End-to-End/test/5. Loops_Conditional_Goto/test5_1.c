// test case for simple if and if else and if else if ladder
// Output : c is the greatest

#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30;
    if (a > b) {
        a = 3;
    } else if (b > c) {
        b = 2;
    } else {
        c = 1;
    }
    return 0;
}