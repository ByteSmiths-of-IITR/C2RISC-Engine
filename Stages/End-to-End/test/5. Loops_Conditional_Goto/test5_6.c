// test case for simple goto statement
//Output : 0 1 2 3 4 5 6 7 8 9

#include <stdio.h>

int main() {
    int i = 0;
    loop_start:
        if (i < 10) {
            printf("%d ", i);
            i++;
            goto loop_start; // jump to the start of the loop
        }
    printf("\n");
    return 0;
}