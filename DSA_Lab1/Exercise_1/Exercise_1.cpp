#include <iostream>
using namespace std;

// Function prototypes
void inputArray(int*& arr, int n);
void printArray(int* arr, int n);
int findMax(int* arr, int n);
int sumArray(int* arr, int n);
void concatArrays(int* a, int na, int* b, int nb, int*& res, int& nres);
void inputNumber(int& n);


int main() {
    int na, nb, nc;

    cout << "Enter the number of elements in array a: ";
	inputNumber(na);

    int* a = new int[na];
    inputArray(a, na);

    cout << "\nEnter the number of elements in array b: ";
	inputNumber(nb);

    int* b = new int[nb];
    inputArray(b, nb);

    int* c = NULL;
    concatArrays(a, na, b, nb, c, nc);
    cout << "\nArray c: ";
    printArray(c, nc);

    int maxC = findMax(c, nc);
    cout << "The maximum value in the array c: " << maxC << endl;

    int sumC = sumArray(c, nc);
    cout << "The sum of elements in the array c: " << sumC;

    // delete pointers
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}

// Input an array from the keyboard with a known size
void inputArray(int*& arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "Enter element " << i << ": ";
        cin >> arr[i];
    }
}

// Print the elements of the array to console
void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Find the maximum value in the array
int findMax(int* arr, int n) {
    if (n < 0) {
        cout << "Invalid size." << endl;
        return -1;
    }
    if (n == 0 || arr == NULL) {
        cout << "The array is empty." << endl;
        return -1;
    }

    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Calculate the sum of the elements in the array
int sumArray(int* arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

// Concatenate two arrays into a new array
void concatArrays(int* a, int na, int* b, int nb, int*& res, int& nres) {
    if (na < 0 || nb < 0) {
        cout << "Invalid sizes." << endl;
        res = NULL;
        nres = 0;
        return;
    }

    if (na == 0 && nb == 0) {
        cout << "Both arrays are empty." << endl;
        res = NULL;
        nres = 0;
        return;
    }

    res = new int[na + nb];
    nres = na + nb;
    for (int i = 0; i < na; i++) {
        res[i] = a[i];
    }
    for (int i = 0; i < nb; i++) {
        res[na + i] = b[i];
    }
}

// Input the number of elements in the array
void inputNumber(int& n) {
	do {
		cin >> n;
		if (n <= 0) {
            cout << "The number of elements must be a positive integer. Please re-enter:";
		}
	} while (n <= 0);
}