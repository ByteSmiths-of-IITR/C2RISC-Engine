#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 3, cols = 4;
    
    // Allocate memory for row pointers
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (!matrix) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (!matrix[i]) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }
    
    // Initialize and print the 2D matrix
    printf("Dynamically Allocated 2D Array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // Free the allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}
