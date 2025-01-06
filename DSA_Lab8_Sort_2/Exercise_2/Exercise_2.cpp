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

// MERGE SORT
void merge(vector<int>& a, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	vector<int> L(n1), R(n2);
	for (int i = 0; i < n1; i++) {
		L[i] = a[left + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = a[mid + 1 + j];
	}

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			a[k] = L[i];
			i++;
		}
		else {
			a[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		a[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		a[k] = R[j];
		j++;
		k++;
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

// COUNTING SORT O(n + k)
void countingSort(vector<int>& a, int n) {
	int max = a[0];

	for (int i = 1; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}

	vector<int> count(max + 1, 0);
	vector<int> output(n);

	for (int i = 0; i < n; i++) {
		count[a[i]]++;
	}

	for (int i = 1; i <= max; i++) {
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; i--) {
		output[count[a[i]] - 1] = a[i];
		count[a[i]]--;
	}

	for (int i = 0; i < n; i++) {
		a[i] = output[i];
	}
}
		

// RADIX SORT
void radixSort(vector<int>& a, int n) {
	int max = a[0];

	for (int i = 1; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}

	int exp = 1;

	while (max / exp > 0) {
		vector<int> output(n);
		vector<int> count(10, 0);

		for (int i = 0; i < n; i++) {
			count[(a[i] / exp) % 10]++;
		}

		for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}

		for (int i = n - 1; i >= 0; i--) {
			output[count[(a[i] / exp) % 10] - 1] = a[i];
			count[(a[i] / exp) % 10]--;
		}

		for (int i = 0; i < n; i++) {
			a[i] = output[i];
		}

		exp *= 10;
	}
}

int randomElement(int a, int b) {
	return a + rand() % (b - a + 1);
}

void printArray(vector<int> a, int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}


int main() {

	// generate random arrays
	srand((unsigned int)time(NULL));
	int n = 100000;
	vector<int> a1(n), a2(n), a3(n);

	for (int i = 0; i < n; i++) {
		a1[i] = a2[i] = a3[i] = randomElement(0, n);
	}

	// MEASURE TIME
	clock_t start, end;

	// MERGE SORT
	start = clock();
	mergeSort(a1, 0, n - 1);
	end = clock();
	double duration_1 = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Merge Sort Time: " << duration_1 << " seconds" << endl;

	// COUNTING SORT
	start = clock();
	countingSort(a2, n);
	end = clock();
	double duration_2 = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Counting Sort Time: " << duration_2 << " seconds" << endl;

	// RADIX SORT
	start = clock();
	radixSort(a3, n);
	end = clock();
	double duration_3 = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Radix Sort Time: " << duration_3 << " seconds" << endl;


	// COMPARE DURATIONS

	// FASTEST ALGORITHM
	cout << "The fastest algorithm: ";
	if (duration_1 < duration_2 && duration_1 < duration_3) {
		cout << "Merge Sort";
	}
	else if (duration_2 < duration_1 && duration_2 < duration_3) {
		cout << "Counting Sort";
	}
	else cout << "Radix Sort";
	cout << endl;

	// SLOWEST ALGORITHM
	cout << "The slowest algorithm: ";
	if (duration_1 > duration_2 && duration_1 > duration_3) {
		cout << "Merge Sort";
	}
	else if (duration_2 > duration_1 && duration_2 > duration_3) {
		cout << "Counting Sort";
	}
	else cout << "Radix Sort";
	cout << endl;


	// delete arrays
	a1.clear();
	a2.clear();
	a3.clear();

	return 0;
}