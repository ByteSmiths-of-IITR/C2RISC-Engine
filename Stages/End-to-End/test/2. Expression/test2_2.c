//Test case : Expression evaluation
//Output : Result: 15
#include <stdio.h>

enum Color {
    RED,
    GREEN,
    BLUE
};

int main() {
    int a = 5;
    int b = 10;
    enum Color c = GREEN;
    a =a + b;
    a = a / c;
    // printf("Result: %d\n", a);
    return 0;
}