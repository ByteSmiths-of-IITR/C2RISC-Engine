#include <stdio.h>

int main()
{
    float floatArr[4] = {1.1, 2.2, 3.3, 4.4};
    char word[] = "World";

    int option;
    printf("Enter a number (1: Print float array, 2: Print string in reverse): ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
    {
        float *p = floatArr; // Pointer to float array
        printf("Float Array: ");
        for (int i = 0; i < 4; i++)
        {
            printf("%.1f ", *(p + i));
        }
        printf("\n");
        break;
    }
    case 2:
    {
        char *p = word; // Pointer to character array
        int len = 0;
        while (word[len] != '\0')
        {
            len++;
        }
        printf("Reversed String: ");
        for (int i = len - 1; i >= 0; i--)
        {
            printf("%c", *(p + i));
        }
        printf("\n");
        break;
    }
    default:
        printf("Invalid option\n");
    }
    return 0;
}
