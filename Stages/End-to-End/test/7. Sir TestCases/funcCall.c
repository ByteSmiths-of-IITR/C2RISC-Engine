#include <stdio.h>

int func(int a,int b,int c){
    return a + b + c;
}

int main(){
    int ans = func(2, 3, 5);
    printVar(ans);
}