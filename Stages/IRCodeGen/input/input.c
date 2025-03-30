#include <stdio.h>
enum Color{
    RED,
    GREEN = 5,
    BLUE
};

static int function(int a, int b){
    return a + b;
}

int main() {
    enum Color c;
    c = RED;
    printf("%d\n", c);
    c = GREEN;
    printf("%d\n", c);
    c = BLUE;
    printf("%d\n", c);
    return 0;
}