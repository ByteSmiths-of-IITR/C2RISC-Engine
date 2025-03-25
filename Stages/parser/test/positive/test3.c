#include <stdio.h>

#define FALSE 0
#define TRUE 1

int main()
{
    int num;
    int isValid = FALSE; // Using a boolean-like variable

    // Loop until a number between 1 and 100 is entered
    do
    {
        printf("Enter a number between 1 and 100: ");
        scanf("%d", &num);
        if (num >= 1 && num <= 100)
        {
            isValid = TRUE;
        }
        else
        {
            printf("Invalid input. Try again.\n");
        }
    } while (!isValid);

    printf("Valid number entered: %d\n", num);
    return 0;
}
