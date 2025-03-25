#include <stdio.h>

struct Point {
    int x, y;
};

void printPoint(struct Point p) {
    printf("Point: %d, %d\n", p.x, p.y);
}

int main() {
    int a = 10, *ptr = &a;  // Pointer usage
    struct Point p1 = {5, 10};

    printf("Value at pointer: %d\n", *ptr);
    
    printPoint(p1);  // Function call with structure argument

    return 0;
}
