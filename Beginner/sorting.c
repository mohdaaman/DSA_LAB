#include <stdio.h>
#include <stdlib.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* ---------------------- BUBBLE SORT ---------------------- */
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

/* ---------------------- INSERTION SORT ---------------------- */
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/* ---------------------- QUICK SORT ---------------------- */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1), j;
    for (j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* ---------------------- MERGE SORT ---------------------- */
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

/* ---------------------- HEAP SORT ---------------------- */
void heapify(int arr[], int n, int i) {
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

/* ---------------------- UTILITY FUNCTIONS ---------------------- */
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

/* ---------------------- MAIN FUNCTION ---------------------- */
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n], temp[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int choice;
    while (1) {
        printf("\n--- Sorting Menu ---\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Quick Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Heap Sort\n");
        printf("6. Time Complexity Comparison\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        copyArray(arr, temp, n);

        switch (choice) {
            case 1:
                bubbleSort(temp, n);
                printf("Sorted Array (Bubble Sort): ");
                printArray(temp, n);
                break;
            case 2:
                insertionSort(temp, n);
                printf("Sorted Array (Insertion Sort): ");
                printArray(temp, n);
                break;
            case 3:
                quickSort(temp, 0, n - 1);
                printf("Sorted Array (Quick Sort): ");
                printArray(temp, n);
                break;
            case 4:
                mergeSort(temp, 0, n - 1);
                printf("Sorted Array (Merge Sort): ");
                printArray(temp, n);
                break;
            case 5:
                heapSort(temp, n);
                printf("Sorted Array (Heap Sort): ");
                printArray(temp, n);
                break;
            case 6:
                printf("\n--- Time Complexity Comparison ---\n");
                printf("Algorithm\tBest Case\tAverage Case\tWorst Case\n");
                printf("------------------------------------------------------\n");
                printf("Bubble Sort\tO(n)\t\tO(n^2)\t\tO(n^2)\n");
                printf("Insertion Sort\tO(n)\t\tO(n^2)\t\tO(n^2)\n");
                printf("Quick Sort\tO(n log n)\tO(n log n)\tO(n^2)\n");
                printf("Merge Sort\tO(n log n)\tO(n log n)\tO(n log n)\n");
                printf("Heap Sort\tO(n log n)\tO(n log n)\tO(n log n)\n");
                break;
            case 7:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
