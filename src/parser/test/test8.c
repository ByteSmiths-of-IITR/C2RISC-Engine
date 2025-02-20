#include <stdio.h>

int main() {
    // 2D Array: 3 rows x 4 columns
    int arr2d[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("2D Array:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", arr2d[i][j]);
        }
        printf("\n");
    }
    
    // 3D Array: 2 blocks x 3 rows x 4 columns
    int arr3d[2][3][4] = {
        {
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9, 10, 11, 12}
        },
        {
            {13, 14, 15, 16},
            {17, 18, 19, 20},
            {21, 22, 23, 24}
        }
    };
    
    printf("\n3D Array:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                printf("%d ", arr3d[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    return 0;
}
