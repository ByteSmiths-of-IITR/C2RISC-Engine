#include <stdio.h>

int main() {
    int i;
    static int count = 0;  // static variable retains its value between calls
    
    // Loop with break and continue
    for (i = 0; i < 10; i++) {
        if (i == 2) {
            count++;
            continue;  // Skip when i is 2
        }
        if (i == 5) {
            break;     // Exit the loop when i is 5
        }
        printf("i = %d\n", i);
    }
    // Using goto for a simple loop
    int j = 0;
start:
    if (j < 3) {
        printf("Goto loop iteration: %d\n", j);
        j++;
        goto start;
    }
    
    printf("Static count value: %d\n", count);
    return 0;
}
