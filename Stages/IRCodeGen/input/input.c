// #include <stdio.h>
// enum Color
// {
//     RED,
//     GREEN,
//     BLUE
// };

// int function(int a, int b)
// {
//     return a + b;
// }

// #define LorR(x) printf("%p\n", &(x));

// #define MorNM_Lvalue(x) \
//     x = x;              \
//     x++;

struct A
{
    int a;
    int b;
};

int function(int a,int arr[], struct A b)
{
    return a + arr[0] + b.a;
}

int main(){

    int a = 9;
    int arr[] = {1, 2, 3, 4, 5};
    struct A b;
    b.a = 10;

    int res = function(a, arr, b);
}