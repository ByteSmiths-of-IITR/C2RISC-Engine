// test case for simple switch case
// Output : Case 0
#include <stdio.h>

int main() {
    int i = 0;
    int a = 0;
    switch (i) {
        case 0:
            a = 1;
            break;
        case 1:
            a = 2;
            break;
        default:
            a = 3;
            break;
    }
    return 0;
}