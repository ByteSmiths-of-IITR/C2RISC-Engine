#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rows = 4, cols = 5;

    // Allocate memory for row pointers
    int **matrix = (int **)calloc(rows, sizeof(int *));
    if (!matrix)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Allocate memory for each row and initialize to zero
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)calloc(cols, sizeof(int)); // Using calloc to initialize elements to 0
        if (!matrix[i])
        {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }

    // Assign values using pointer arithmetic
    printf("Dynamically Allocated 2D Array (using calloc & pointer arithmetic):\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(*(matrix + i) + j) = i * cols + j; // Equivalent to matrix[i][j]
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Free the allocated memory
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
