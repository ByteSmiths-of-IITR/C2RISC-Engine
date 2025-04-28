// test case for union access and performing operations on it
// Output: 
// data.i: 10
// data.f: 220.500000
// data.c: A
#include <stdio.h>

union Data {
    int i;
    float f;
    char c;
};

int main() {
    union Data data;        // Declare a union variable
    data.i = 10;           // Assign an integer value to the union
    // printf("data.i: %d\n", data.i); // Access the integer value

    data.f = 220.5;        // Assign a float value to the union
    // printf("data.f: %f\n", data.f); // Access the float value

    data.c = 'A';         // Assign a char value to the union
    // printf("data.c: %c\n", data.c); // Access the char value

    return 0;
}