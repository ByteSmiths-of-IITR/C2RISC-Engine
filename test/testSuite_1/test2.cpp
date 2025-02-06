#include <stdio.h>

int main() {
    int i, arr[5] = {1, 2, 3, 4, 5};
    
    for (i = 0; i < 5; i++)
        printf("%d ", arr[i]);  // for loop
    
    i = 0;
    while (i < 3) {  // while loop
        printf("W%d ", i);
        i++;
    }

    i = 0;
    do {  // do-while loop
        printf("D%d ", i);
        i++;
    } while (i < 2);

    goto end;  // goto usage

end:
    printf("\nEnd of test case 2\n");

    return 0;
}
