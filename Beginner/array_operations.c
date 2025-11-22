#include <stdio.h>

#define MAX 100

int main() {
    int arr[MAX];
    int n, i, choice, pos, val;

    printf("Enter number of elements (max %d): ", MAX);
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Insert element\n");
        printf("2. Delete element\n");
        printf("3. Display array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (n == MAX) {
                    printf("Array is full! Cannot insert.\n");
                    break;
                }
                printf("Enter position (1 to %d): ", n + 1);
                scanf("%d", &pos);
                if (pos < 1 || pos > n + 1) {
                    printf("Invalid position!\n");
                    break;
                }
                printf("Enter value to insert: ");
                scanf("%d", &val);

                for (i = n - 1; i >= pos - 1; i--)
                    arr[i + 1] = arr[i];
                arr[pos - 1] = val;
                n++;
                printf("Element inserted successfully.\n");
                break;

            case 2:
                if (n == 0) {
                    printf("Array is empty! Cannot delete.\n");
                    break;
                }
                printf("Enter position (1 to %d): ", n);
                scanf("%d", &pos);
                if (pos < 1 || pos > n) {
                    printf("Invalid position!\n");
                    break;
                }
                for (i = pos - 1; i < n - 1; i++)
                    arr[i] = arr[i + 1];
                n--;
                printf("Element deleted successfully.\n");
                break;

            case 3:
                if (n == 0)
                    printf("Array is empty!\n");
                else {
                    printf("Array elements: ");
                    for (i = 0; i < n; i++)
                        printf("%d ", arr[i]);
                    printf("\n");
                }
                break;

            case 4:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
