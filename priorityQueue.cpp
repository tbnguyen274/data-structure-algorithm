#include <iostream>
using namespace std;

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

int maxHeapMaximum(int a[], int n) {
    if (n <= 0) return -1;
    return a[1];
}

int maxHeapExtractMax(int a[], int& n) {
    int max = maxHeapMaximum(a, n);
    a[1] = a[n];
    n--;
    maxHeapify(a, n, 1);
    return max;
}

/*
Pseudocode:
MAX-HEAP-INCREASE-KEY(A, i, key)
    if key < i.key
        error "new key is smaller than current key"
    x.key = key
    find the index i in array A where object x occurs 
    while i > 1 and A[PARENT(i)].key < A[i].key
        exchange A[i] with A[PARENT(i)]
        i = PARENT(i)
*/
void maxHeapIncreaseKey(int a[], int n, int i, int key) {
    if (key < a[i]) return;
    a[i] = key;
    while (i > 1 && a[parentIndex(a, n, i)] < a[i]) {
        // exchange the key with the parent --> update information
        int temp = a[i];
        a[i] = a[parentIndex(a, n, i)];
        a[parentIndex(a, n, i)] = temp;
        i = parentIndex(a, n, i);
    }
}

/*
Pseudocode:
MAX-HEAP-INSERT (A,x,n)
1 if A.heap-size == n
2   error heap overflow
3 A.heap-size = A.heap-size + 1
4 k = x.key
5 x.key = -INFINITY
6 A[heap.size] = x
7 map x to index heap-size in the array 
8 MAX-HEAP-INCREASE-KEY (A,x,k)
*/
void maxHeapInsert(int a[], int& n, int i, int key) {
    n++;
    a[n] = INT_MIN;
    maxHeapIncreaseKey(a, n, n, key);
}

void print(int a[], int n) {
    for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

}

int main() {
    cout << "Hello, World!" << endl;
    int n = 8;
    int* A = new int[n+1] {0, 2, 4, 5, 7, 1, 8, 3, 6};
    print(A, n);
    buildMaxHeap(A, n);
    print(A, n);
    cout << "Max-heap maximum: " << maxHeapMaximum(A, n) << endl;
    cout << "Max-heap extract max: " << maxHeapExtractMax(A, n) << endl;
    cout << "Max-heap extract max 2: " << maxHeapExtractMax(A, n) << endl;
    print(A, n);
    return 0;
}