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

void mergeSort(int*& A, int p, int r) {
    if (p >= r) 
        return;
    int q = (p + r) / 2;
    mergeSort(A, p, q);
    mergeSort(A, q+1, r);
    merge(A, p, q, r);
}

int main() {
    int* A = new int[8] {2, 4, 5, 7, 1, 0, 3, 6};
    int n = 8;
    print(A, n);
    mergeSort(A, 0, n-1);
    print(A, n);

    return 0;
}