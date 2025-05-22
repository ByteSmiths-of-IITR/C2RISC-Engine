
#include <stdio.h>

int main()
{
    int arr[5];

    int size = 5;

    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        arr[i] = i + 1;
        sum = sum + arr[i];
    }

    // printVar(sum);
    printf("Sum: %d\n", sum);
    return 0;
}