#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>

using namespace std;

void insertionSort(int* a, int n) {
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

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void selectionSort(int* a, int n) {
	int min;
	for (int i = 0; i < n; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[min]) {
				min = j;
			}
		}
		if (min != i) {
			swap(a[min], a[i]);
		}
	}
}

void interchangeSort(int* a, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (a[i] > a[j]) {
				swap(a[i], a[j]);
			}
		}
	}
}

void printArray(int* a, int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int randomElement(int a, int b) {
	return a + rand() % (b - a + 1);
}

int main() {

	// generate random arrays

	srand((unsigned int)time(NULL));
	int n = 10000;
	int* a1 = new int[n];
	int* a2 = new int[n];
	int* a3 = new int[n];

	for (int i = 0; i < n; i++) {
		a1[i] = a2[i] = a3[i] = randomElement(0, n);
	}

	// MEASURE TIME
	clock_t start, end;

	// INSERTION SORT
	start = clock();
	insertionSort(a1, n);
	end = clock();
	double duration_1 = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Insertion Sort Time: " << duration_1 << " seconds" << endl;

	// SELECTION SORT
	start = clock();
	selectionSort(a2, n);
	end = clock();
	double duration_2 = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Selection Sort Time: " << duration_2 << " seconds" << endl;

	// INTERCHANGE SORT
	start = clock();
	interchangeSort(a3, n);
	end = clock();
	double duration_3 = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Interchange Sort Time: " << duration_3 << " seconds" << endl;


	// COMPARE DURATIONS
	// FASTEST ALGORITHM
	cout << "The fastest algorithm: ";
	if (duration_1 < duration_2 && duration_1 < duration_3) {
		cout << "Insertion Sort";
	}
	else if (duration_2 < duration_1 && duration_2 < duration_3) {
		cout << "Selection Sort";
	}
	else cout << "Interchange Sort";
	cout << endl;

	// SLOWEST ALGORITHM
	cout << "The slowest algorithm: ";
	if (duration_1 > duration_2 && duration_1 > duration_3) {
		cout << "Insertion Sort";
	}
	else if (duration_2 > duration_1 && duration_2 > duration_3) {
		cout << "Selection Sort";
	}
	else cout << "Interchange Sort";
	cout << endl;


	// delete arrays
	delete[] a1;
	delete[] a2;
	delete[] a3;

	return 0;
}