#include <stdio.h>

int main() {
    int num = 42;
    int *p = &num;       // single-level pointer
    int **pp = &p;       // double pointer
    int ***ppp = &pp;    // triple pointer
    
    printf("num = %d\n", num);
    printf("Value using *p = %d\n", *p);
    printf("Value using **pp = %d\n", **pp);
    printf("Value using ***ppp = %d\n", ***ppp);
    
    return 0;
}
