#include <stdio.h>

int main() {
    printf("Hello\z World\n");  // ❌ Lexical Error: Invalid escape sequence '\z'
    printf("This is an unterminated string...);  // ❌ Lexical Error: Missing closing quote
    int @value = 50;  // ❌ Lexical Error: '@' is not a valid character in an identifier

    return 0;
}
