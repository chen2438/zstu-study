#include <stdio.h>

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int a[], int low, int high) {
    int pivot = a[low];  // 选择基准
    int i = low, j = high;
    while (i < j) {
        // while (i < j && a[j] >= pivot) j--; // 从右向左找小于等于基准的元素
        while (i < j && a[j] > pivot)
            j--;  // 与基准相等的元素不会移动到基准的左侧
        while (i < j && a[i] <= pivot) i++;
        swap(&a[i], &a[j]);
    }
    swap(&a[low], &a[i]);  // 基准记录到位
    return i;
}

void quickSort(int a[], int low, int high, int n) {
    if (low < high) {
        int pi = partition(a, low, high);
        printArray(a, n);
        quickSort(a, low, pi - 1, n);
        quickSort(a, pi + 1, high, n);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    quickSort(a, 0, n - 1, n);
    printArray(a, n);
    return 0;
}
