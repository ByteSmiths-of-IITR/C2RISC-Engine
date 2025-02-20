#include <stdio.h>

int main() {
    // Arithmetic operators
    int a = 15, b = 4;
    int p=10,q,r;
    int **z[5][6][7];
    int sum = a + b;
    int diff = a - b;
    int prod = a * b;
    int div = a / b;
    int mod = a % b;
    printf("Arithmetic:\n");
    printf("  %d + %d = %d\n", a, b, sum);
    printf("  %d - %d = %d\n", a, b, diff);
    printf("  %d * %d = %d\n", a, b, prod);
    printf("  %d / %d = %d\n", a, b, div);
    printf("  %d %% %d = %d\n\n", a, b, mod);
    // Logical operators with if-else
    if (a > 10 && b < 10) {
        printf("Condition met: a > 10 && b < 10\n\n");
    } else {
        printf("Condition not met\n\n");
    }

    // For loop: compute factorial of 5
    int fact = 1;
    for (int i = 1; i <= 5; i++) {
        fact *= i;
    }
    printf("Factorial of 5 is %d\n\n", fact);
    
    // While loop: sum numbers from 1 to 5
    int i = 1, total = 0;
    while (i <= 5) {
        total += i;
        i++;
    }
    printf("Sum from 1 to 5 is %d\n\n", total);
    
    // Do-while loop: countdown from 3 to 1
    int count = 3;
    do {
        printf("Countdown: %d\n", count);
        count--;
    } while (count > 0);
    return 0;
}
