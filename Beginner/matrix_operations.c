#include <stdio.h>

#define MAX 10

void readMatrix(int mat[MAX][MAX], int r, int c) {
    int i, j;
    printf("Enter elements of %d x %d matrix:\n", r, c);
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            scanf("%d", &mat[i][j]);
}

void printMatrix(int mat[MAX][MAX], int r, int c) {
    int i, j;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++)
            printf("%d\t", mat[i][j]);
        printf("\n");
    }
}

void addMatrix(int a[MAX][MAX], int b[MAX][MAX], int r, int c) {
    int i, j, sum[MAX][MAX];
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            sum[i][j] = a[i][j] + b[i][j];

    printf("Result of Addition:\n");
    printMatrix(sum, r, c);
}

void subtractMatrix(int a[MAX][MAX], int b[MAX][MAX], int r, int c) {
    int i, j, diff[MAX][MAX];
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            diff[i][j] = a[i][j] - b[i][j];

    printf("Result of Subtraction:\n");
    printMatrix(diff, r, c);
}

void multiplyMatrix(int a[MAX][MAX], int b[MAX][MAX], int r1, int c1, int r2, int c2) {
    if (c1 != r2) {
        printf("Matrix multiplication not possible (columns of A != rows of B)\n");
        return;
    }

    int i, j, k, product[MAX][MAX];
    for (i = 0; i < r1; i++)
        for (j = 0; j < c2; j++) {
            product[i][j] = 0;
            for (k = 0; k < c1; k++)
                product[i][j] += a[i][k] * b[k][j];
        }

    printf("Result of Multiplication:\n");
    printMatrix(product, r1, c2);
}

void transposeMatrix(int mat[MAX][MAX], int r, int c) {
    int i, j, trans[MAX][MAX];
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            trans[j][i] = mat[i][j];

    printf("Transpose of Matrix:\n");
    printMatrix(trans, c, r);
}

int main() {
    int a[MAX][MAX], b[MAX][MAX];
    int r1, c1, r2, c2, choice;

    printf("Enter rows and columns of first matrix: ");
    scanf("%d%d", &r1, &c1);
    readMatrix(a, r1, c1);

    printf("Enter rows and columns of second matrix: ");
    scanf("%d%d", &r2, &c2);
    readMatrix(b, r2, c2);

    while (1) {
        printf("\n--- Matrix Operations Menu ---\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Transpose of first matrix\n");
        printf("5. Transpose of second matrix\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (r1 == r2 && c1 == c2)
                    addMatrix(a, b, r1, c1);
                else
                    printf("Addition not possible (dimensions must be same)\n");
                break;

            case 2:
                if (r1 == r2 && c1 == c2)
                    subtractMatrix(a, b, r1, c1);
                else
                    printf("Subtraction not possible (dimensions must be same)\n");
                break;

            case 3:
                multiplyMatrix(a, b, r1, c1, r2, c2);
                break;

            case 4:
                transposeMatrix(a, r1, c1);
                break;

            case 5:
                transposeMatrix(b, r2, c2);
                break;

            case 6:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
