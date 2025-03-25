#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Total arguments passed: %d\n", argc);

    // Using while loop to print arguments
    int i = 0;
    while (i < argc)
    {
        printf("Arg %d: %s\n", i, argv[i]);
        i++;
    }

    // Using for loop to print arguments
    for (int i = 0; i < argc; i++)
    {
        printf("Arg %d: %s\n", i, argv[i]);
    }

    // Checking if at least one argument is passed
    if (argc > 1)
    {
        printf("First argument (excluding program name): %s\n", argv[1]);
    }
    else
    {
        printf("No additional arguments provided.\n");
    }

    // Using pointer arithmetic to access arguments
    char **ptr = argv;
    printf("Pointer access: %s\n", *(ptr + 0));

    return 0;
}
