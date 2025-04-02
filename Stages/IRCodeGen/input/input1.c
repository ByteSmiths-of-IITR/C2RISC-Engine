#include <stdio.h>

struct A{
    int a;
};

int func(int a){
    return a;
}

#define LorR(x) printf("%p\n", &(x));

#define MorNM_Lvalue(x) x++;

int main(){
    int a=2,b=5;
    int c = 9;
    int *ptr = &a;

    // LorR(a += b);
    a = b, c;

    // c += a += b;


    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);
}