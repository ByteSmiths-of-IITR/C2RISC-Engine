#include <stdio.h> // Preprocessor directive

// */
// Keywords
int main() {
    auto int a = ;           // auto keyword
    static int b = 20;         // static keyword
    register int c = 30;       // register keyword
    const int CONSTANT = 100;  // const keyword
    volatile int d = 40;       // volatile keyword
    char ch = 'A';             // char data type
    float pi = 3.14;           // float data type
    double largePi = 3.14159;  // double data type

    // Control flow keywords
    if (a < b) {
        while (a < b) {
            a++;
            break;
        }
    } else {
        for (int i = 0; i < 5; i++) {
            continue;
        }
    }

    // Logical and relational operators
    if (a == 10 && b != 0 || c < 100) {
        a = b + c - d * 2 / 4 % 3; // Arithmetic operators
    }

    // Bitwise operators
    int bitwise = a & b | c ^ d;
    bitwise = ~bitwise << 1 >> 2;

    // Assignment operators
    a += 1;
    b -= 2;
    c *= 3;
    d /= 4;
    a %= 5;
    b &= 6;
    c |= 7;
    d ^= 8;
    a <<= 1;
    b >>= 1;

    // Special characters and constants
    printf("Hello, World!\n");
    char str[] = "String literal";
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = &a;

    // Function call
    printNumbers(a, b, c);

    // Return statement
    return 0;
}

// A user-defined function
void printNumbers(int x, int y, int z) {
    printf("x: %d, y: %d, z: %d\n", x, y, z);
}