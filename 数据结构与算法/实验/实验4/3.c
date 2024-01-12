#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void quickSort(int arr[], int left, int right);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    bubbleSort(arr, n);
    // insertionSort(arr, n);
    // quickSort(arr, 0, n - 1);
    // mergeSort(arr, 0, n - 1);

    for (int i = 0; i < n - 1; i++) printf("%d ", arr[i]);
    printf("%d", arr[n - 1]);
    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) swap(&arr[j], &arr[j + 1]);
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            // 大于key的元素右移，为key的插入腾出空间
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;  // 插入key
    }
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

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);  // 分割、归并左边
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];  // 左、右的有序数组
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    i = 0, j = 0, k = l;
    while (i < n1 && j < n2)  // 选择两个数组中较小的元素放入原数组
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    while (i < n1) arr[k++] = L[i++];  // 复制剩余元素
    while (j < n2) arr[k++] = R[j++];
}
