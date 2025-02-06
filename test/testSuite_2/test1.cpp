#include <stdio.h>

int main() {
    int a = 10, b = 5, c;
    int arr[3] = {1, 2, 3};
    int *ptr = &a;
    static int x = 5;
    
    // ❌ Syntax Error: Wrong use of arithmetic/logical operators
    c = a b + * ptr;  
    
    // ❌ Syntax Error: Incorrect for-loop syntax (initialization missing)
    for (i < 3; i++;;)
        printf("Arr[%d] = %d\n", i, arr[i]);
    
    // ❌ Syntax Error: Misplaced ternary operator
    if (x ? b : a) 
    printf("This condition is confusing\n");

    // ❌ Syntax Error: Incorrect goto label
    goto 100;  // Labels should be identifiers, not numbers

    return 0;
}
