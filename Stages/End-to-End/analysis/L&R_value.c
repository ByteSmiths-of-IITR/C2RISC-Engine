#include <stdio.h>

#define LorR(x) printf("%p\n", &(x));

#define MorNM_Lvalue(x) x++;
// #define MorNM_Lvalue(x) x = 10; // Another way to check if Lvalue is modifiable or not

int main(){
    
    // To check if something is Lvalue or Rvalue
    // put it on the left side of an assignment

    // To check if Lvalue is modifiable or not
    // dereference it and see if you can get a address out of it

}