#include <stdio.h>

int main() {
    int num = 2;
    int arr[2][2] = {{1, 2}, {3, 4}};  // Multi-dimensional Array

    switch (num) {  // switch case
        case 1:
            printf("One\n");
            break;
        case 2:
            printf("Two\n");
            break;
        default:
            printf("Other\n");
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (arr[i][j] == 3) continue;  // continue usage
            printf("%d ", arr[i][j]);
        }
    }

    return 0;
}
