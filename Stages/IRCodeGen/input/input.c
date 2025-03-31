// const int arr[] = {1,2};
// const int a = 1;
// int ar[a];

#include <stdio.h>

enum Color
{
    RED,
    GREEN,
    BLUE
};

int main(){
    long long a= 1, b= 2;
    printf("%lu\n", sizeof(int));
    printf("%lu\n", sizeof(RED+RED));
}