#include <stdio.h>

// typedef int boolean;
#define false 0
#define true 1

int main() {
    int num;
    // "Until" loop: repeat until a positive number is entered.
    do {
        printf("Enter a positive number: ");
        scanf("%d", &num);
    } while (num <= 0);  // Loop continues until num > 0
    
    printf("You entered %d\n", num);
    return 0;
}
