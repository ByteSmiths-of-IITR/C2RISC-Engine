
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
    printVar(a);
    printVar(b);
    printVar(c);
    return 0;
}