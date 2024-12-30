#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>

using namespace std;

void swap (int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// O(n^2) sort
void selectionSort(vector<int>& a);
void insertionSort(vector<int>& a);
void interchangeSort(vector<int>& a);

// O(nlogn) sort
void heapify(vector<int>& a, int n, int i);
void heapSort(vector<int>& a);

void merge(vector<int>& a, int left, int mid, int right);
void mergeSort(vector<int>& a, int left, int right);

void partition(vector<int>& a, int low, int high);
void quickSort(vector<int>& a, int low, int high);

// O(n) sort
void countingSort(vector<int>& a);

int main() {
    srand((unsigned int) time(NULL));\
    int n = 5 + rand() % 6;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 30;
    }

    cout << "Before sorting:\n";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    // selectionSort(a);
    // insertionSort(a);
    // heapSort(a);
    mergeSort(a, 0, n - 1);

    cout << "After sorting:\n";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }

    cout << endl;
}

// O(n^2) sort
void selectionSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        if (min != i) swap(a[min], a[i]);
    }
}

void insertionSort(vector<int>& a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int saved = a[i];
        int j = i;
        while (j > 0 && saved < a[j - 1]) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = saved;
    }
}

void interchangeSort(vector<int>& a);

// O(nlogn) sort
void heapify(vector<int>& a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest]) {
        largest = left;
    }
    if (right < n && a[right] > a[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<int>& a) {
    int n = a.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

void merge(vector<int>& a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) {
        L[i] = a[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = a[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            a[k++] = L[i++];
        }
        else {
            a[k++] = R[j++];
        }
    }

    while (i < n1) {
        a[k++] = L[i++];
    }

    while (j < n2) {
        a[k++] = R[j++];
    }
}

void mergeSort(vector<int>& a, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

void partition(vector<int>& a, int low, int high);
void quickSort(vector<int>& a, int low, int high);

// O(n) sort
void countingSort(vector<int>& a);