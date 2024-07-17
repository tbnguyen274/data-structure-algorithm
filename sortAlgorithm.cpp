#include <iostream>
using namespace std;

void print(int* a, int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

// p = left, q = mid, r = right
void merge(int*& A, int p, int q, int r) {
    int nL = q - p + 1; // length of A[p:q]
    int nR = r - q;     // length of A[q+1:r]

    int* L = new int[nL];
    int* R = new int[nR];

    // copy A[p:q] into L[0:nL-1]
    for (int i = 0; i < nL; i++) {
        L[i] = A[p+i];
    };
    // copy A[q+1:r] into R[0:nR-1]
    for (int i = 0; i < nR; i++) {
        R[i] = A[q+i+1];
    }

    int i = 0, j = 0, k = p;
    // As long as each of the arrays L and R contains an unmerged element, 
    // copy the smallest unmerged element back into A[p:r]
    while (i < nL && j < nR) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining unmerged elements back into A
    while (i < nL) {
        A[k] = L[i];
        i++;
        k++;
    }
    while (j < nR) {
        A[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

// merge sort
// Time complexity: O(nlogn)
void mergeSort(int* A, int p, int r) {
    if (p >= r) 
        return;
    int q = (p + r) / 2;
    mergeSort(A, p, q);
    mergeSort(A, q+1, r);
    merge(A, p, q, r);
}

// insertion sort
// Time complexity: O(n^2)
void insertionSort(int* a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && key < a[j]) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

// bubble sort
// Time complexity: O(n^2)
void bubbleSort(int* a, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (a[j] > a[j+1]) {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

// heap sort
// array representing heap starts at index 1, index 0 is ignored
// Time complexity: O(nlogn)
int leftChildIndex(int a[], int n, int i) {
    if (2*i <= n) {
        return 2*i;
    }
    return -1;
}

int rightChildIndex(int a[], int n, int i) {
    if (2*i+1 <= n) {
        return 2*i+1;
    }
    return -1;
}

int parentIndex(int a[], int n, int i) {
    if (i > 1 && i <= n) {
        return i/2;
    }
    return -1;
}

// max-heapify
// Time complexity: O(logn)
void maxHeapify(int a[], int n, int i) {
    int l = leftChildIndex(a, n, i);
    int r = rightChildIndex(a, n, i);
    int largest = i;
    if (l != -1 && a[l] > a[largest]) {
        largest = l;
    }
    if (r != -1 && a[r] > a[largest]) {
        largest = r;
    }
    if (largest != i) {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        maxHeapify(a, n, largest);
    }
}

// build max heap
// Time complexity: O(n)
void buildMaxHeap(int a[], int n) {
    for (int i = n/2; i >= 1; i--) {
        maxHeapify(a, n, i);
    }
}

// heap sort
// Time complexity: O(nlogn)
void heapSort(int a[], int n) {
    buildMaxHeap(a, n);
    for (int i = n; i >= 2; i--) {
        int temp = a[1];
        a[1] = a[i];
        a[i] = temp;
        maxHeapify(a, i-1, 1);
    }
}

// counting sort
// Time complexity: O(n+k)
int* countingSort(int a[], int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    int* count = new int[max+1] {0};
    for (int i = 0; i < n; i++) {
        count[a[i]]++;
    }
    // count[i] now contains the number of elements equal to i
    for (int i = 1; i <= max; i++) {
        count[i] += count[i-1];
    }
    // count[i] now contains the number of elements less than or equal to i
    int* output = new int[n];
    for (int i = n-1; i >= 0; i--) {
        output[count[a[i]]-1] = a[i];
        count[a[i]]--;
    }
    delete[] count;
    return output;
}

int main() {
    int n = 8;
    int* A = new int[n+1] {2, 4, 5, 7, 1, 8, 3, 6};
    print(A, n);
    //mergeSort(A, 0, n-1);
    //insertionSort(A, n);
    //bubbleSort(A, n);
    //heapSort(A, n);
    int* output = countingSort(A, n);
    print(output, n);

    return 0;
}