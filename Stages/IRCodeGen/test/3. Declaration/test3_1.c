// // NO ERROR

// int a;
// int* p, pp;

// void func(){
//     int x;
//     int* ptr, pptr;
// }

// int main(){
//     int x;
//     int* ptr, pptr;

//     return 0;
// }

#include <stdio.h>
int main(){
    int x=0;
    for(int y=0;x<10;x++){
        printf("%d %d\n",x, y);
    }

    x=0;
    switch(x){
        printf("this code never executed\t");
        printf("%d\n", x++);
        case 0:
            printf("x is 0\n");
            break;
        case 1:
            printf("x is 1\n");
            break;
        default:
            printf("x is not 0 or 1\n");
    }
}