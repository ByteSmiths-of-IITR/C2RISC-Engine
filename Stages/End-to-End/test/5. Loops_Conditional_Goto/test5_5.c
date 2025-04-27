// test case for simple switch case
// Output : Case 0
#include <stdio.h>

int main() {
    int i = 0;
    switch (i) {
        case 0:
            printf("Case 0\n");
            break;
        case 1:
            printf("Case 1\n");
            break;
        default:
            printf("Default case\n");
    }
    return 0;
}