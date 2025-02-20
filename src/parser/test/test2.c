#include <stdio.h>

int main() {
    int intArr[5] = {10, 20, 30, 40, 50};
    char charArr[] = "Hello";
    
    int choice;
    printf("Enter a number (1: Print int array, 2: Print char array): ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1: {
            int *p = intArr;  // pointer to integer array
            printf("Integer Array: ");
            for (int i = 0; i < 5; i++) {
                printf("%d ", *(p + i));
            }
            printf("\n");
            break;
        }
        case 2: {
            char *p = charArr;  // pointer to char array
            printf("Character Array: ");
            while (*p != '\0') {
                printf("%c", *p);
                p++;
            }
            printf("\n");
            break;
        }
        default:
            printf("Invalid choice\n");
    }
    return 0;
}
