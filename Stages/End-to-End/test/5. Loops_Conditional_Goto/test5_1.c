// test case for simple if and if else and if else if ladder
// Output : c is the greatest

#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30;
    if (a > b) {
        a = b;
    } else if (b > c) {
        b = c;
    } else {
        c = a;
    }
    return 0;
}