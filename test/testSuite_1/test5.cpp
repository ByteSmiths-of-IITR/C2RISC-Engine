#include <stdio.h>

#define until(cond) while (!(cond))  // Simulating 'until' using macro

int main() {
    char ch;
    
    printf("Enter a character: ");
    scanf("%c", &ch);  // scanf usage
    
    int count = 0;
    until (count == 3) {  // using macro for until loop
        printf("Char: %c\n", ch);
        count++;
    }

    return 0;
}
