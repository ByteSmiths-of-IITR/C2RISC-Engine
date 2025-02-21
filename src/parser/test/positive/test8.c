#include <stdio.h>

int main()
{
    // 2D Array: 4 rows x 3 columns
    int matrix[4][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}};

    printf("2D Array:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // 3D Array: 3 blocks x 2 rows x 2 columns
    int tensor[3][2][2] = {
        {{1, 2},
         {3, 4}},
        {{5, 6},
         {7, 8}},
        {{9, 10},
         {11, 12}}};

    printf("\n3D Array:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                printf("%d ", tensor[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}
