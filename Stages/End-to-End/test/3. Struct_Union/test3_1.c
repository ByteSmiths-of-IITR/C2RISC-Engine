// Test Case: struct object access and print 
//Output:
// 1 2.000000
// 3 4.000000

#include <stdio.h>

struct  A
{
    int a;
    float b;
};
struct  B
{
    int a;
    float b;
};

int main()
{
    struct A a;
    struct B b;
    a.a = 1;
    a.b = 2.0f;
    b.a = 3;
    b.b = 4.0f;
    // printf("%d %f\n", a.a, a.b);
    // printf("%d %f\n", b.a, b.b);
    return 0;
}
