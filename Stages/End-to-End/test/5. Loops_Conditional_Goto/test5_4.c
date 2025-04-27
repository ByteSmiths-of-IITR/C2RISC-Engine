// test case for simple nested loops
// Output : 0 0 0 1 0 2 0 3 0 4 0 6 0 7 0 8 0 9 

#include <stdio.h>

int main() {
    int i = 0;
    while (i < 10) {
        if (i == 5) {
            i++;
            continue; // skip the number 5
        }
        for(int j = 0; j < 2; j++) {
            printf("%d ", i * j); // print the product of i and j
        }
        i++;
    }
    printf("\n");
    return 0;
}