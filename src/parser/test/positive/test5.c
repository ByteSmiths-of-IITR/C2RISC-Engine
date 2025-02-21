#include <stdio.h>

// Function declarations
void function1();
void function2(int);
void function3(double, char);
void function4(const char *);
void function5(int, int, int, int, int);
void function6();
void function7(int, int);
void function8(double, double, double);
void function9(char, char, char);
void function10(const char *, int, double);

// Function definitions
void function1()
{
    printf("Function1 called\n");
}

void function2(int x)
{
    printf("Function2 called with %d\n", x);
}

void function3(double d, char c)
{
    printf("Function3 called with %.2f and %c\n", d, c);
}

void function4(const char *str)
{
    printf("Function4 called with %s\n", str);
}

void function5(int a, int b, int c, int d, int e)
{
    printf("Function5 called with %d, %d, %d, %d, %d\n", a, b, c, d, e);
}

void function6()
{
    printf("Function6 called\n");
}

void function7(int x, int y)
{
    printf("Function7 called with %d and %d\n", x, y);
}

void function8(double a, double b, double c)
{
    printf("Function8 called with %.2f, %.2f, %.2f\n", a, b, c);
}

void function9(char a, char b, char c)
{
    printf("Function9 called with %c, %c, %c\n", a, b, c);
}

void function10(const char *str, int x, double d)
{
    printf("Function10 called with %s, %d, %.2f\n", str, x, d);
}

int main()
{
    function1();
    function2(42);
    function3(3.14, 'a');
    function4("Hello, World!");
    function5(1, 2, 3, 4, 5);
    function6();
    function7(10, 20);
    function8(1.23, 4.56, 7.89);
    function9('x', 'y', 'z');
    function10("Test", 123, 4.56);

    return 0;
}
