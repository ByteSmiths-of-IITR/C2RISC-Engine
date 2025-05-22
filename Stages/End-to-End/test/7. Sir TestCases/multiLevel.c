
#include <stdio.h>

int main(){
    // --- Multi-level Pointers ---
    int y = 50;
    int *p1 = &y;
    int **p2 = &p1;
    int ***p3 = &p2;
    y++;
    int val = ***p3;
    printVar(val); // should print 50

    // --- Multi-level Array ---
    int arr[2][3];
    arr[2][1] = 10;
    int k = arr[2][1];
    printVar(k); // should print 10
}