#include <stdio.h>

int main() {
    int 9variable = 10;  // ❌ Lexical Error: Identifiers cannot start with a digit
    char ch = 'abc';     // ❌ Lexical Error: Character constant can have only one character

    printf("Value: %d\n", 9variable);
    return 0;
}
