#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

// HEAP SORT
void heapify(vector<int>& a, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && a[l] > a[largest]) {
		largest = l;
	}
	if (r < n && a[r] > a[largest]) {
		largest = r;
	}

	// If largest is not root
	if (largest != i) {
		swap(a[i], a[largest]);
		heapify(a, n, largest);		// Recursively heapify the affected sub-tree
	}
}

void heapSort(vector<int>& a) {
	int n = (int) a.size();

	// Build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(a, n, i);
	}
	for (int i = n - 1; i > 0; i--) {
		swap(a[0], a[i]);		// Move current root to end
		heapify(a, i, 0);		// call max heapify on the reduced heap
	}
}


// QUICK SORT
int partition(vector<int>& a, int low, int high) {
	int pivot = a[high];	// pivot
	int i = low - 1;		// Index of smaller element

	for (int j = low; j <= high - 1; j++) {
		if (a[j] <= pivot) {
			i++;
			swap(a[i], a[j]);
		}
	}

	// move pivot element to its correct position: all elements smaller than pivot are on the left,
	// all elements greater than pivot are on the right
	swap(a[i + 1], a[high]);	

	return i + 1;
}

void quickSort(vector<int>& a, int low, int high) {
	if (low < high) {
		// pi is partitioning index, a[p] is now at right place
		int pi = partition(a, low, high);
		// Recursively sort elements smaller than partition and greater than partition
		quickSort(a, low, pi - 1);
		quickSort(a, pi + 1, high);
	}
}

void printArray(vector<int> a, int n) {
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
	int n = 100000;
	vector<int> a1(n), a2(n);

	for (int i = 0; i < n; i++) {
		a1[i] = a2[i] = randomElement(0, n);
	}

	// MEASURE TIME
	clock_t start, end;

	// HEAP SORT
	start = clock();
	heapSort(a1);
	end = clock();
	double duration_1 = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Heap Sort Time: " << duration_1 << " seconds" << endl;

	// QUICK SORT
	start = clock();
	quickSort(a2, 0, n - 1);
	end = clock();
	double duration_2 = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Quick Sort Time: " << duration_2 << " seconds" << endl;


	// COMPARE DURATIONS
	
	// FASTEST ALGORITHM
	cout << "The fastest algorithm: ";
	if (duration_1 < duration_2) {
		cout << "Heap Sort";
	}
	else cout << "Quick Sort";
	cout << endl;

	// SLOWEST ALGORITHM
	cout << "The slowest algorithm: ";
	if (duration_1 > duration_2) {
		cout << "Heap Sort";
	}
	else cout << "Quick Sort";
	cout << endl;


	// delete arrays
	a1.clear();
	a2.clear();

	return 0;
}