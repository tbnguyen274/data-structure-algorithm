#include <iostream>
#include <vector>

using namespace std;

// insertion sort in ascending order
void insertionSortAscending(vector<int>& a) {
	int n = (int) a.size();
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

// insertion sort in descending order
void insertionSortDescending(vector<int>& a) {
	int n = (int) a.size();
	for (int i = 1; i < n; i++) {
		int saved = a[i];
		int j = i;
		while (j > 0 && saved > a[j - 1]) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = saved;
	}
}

void printArray(vector<int> a) {
	int n = (int) a.size();
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int main() {
	
	// input
	int n;
	cin >> n;

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	vector<int> even, odd;
	for (int i = 0; i < n; i++) {
		if (a[i] % 2 == 0) {
			even.push_back(a[i]);
		}
		else {
			odd.push_back(a[i]);
		}
	}

	insertionSortAscending(even);
	insertionSortDescending(odd);

	int evenIndex = 0, oddIndex = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] % 2 == 0) {
			a[i] = even[evenIndex++];
		}
		else {
			a[i] = odd[oddIndex++];
		}
	}

	cout << endl;
	printArray(a);

	// delete vectors
	a.clear();
	even.clear();
	odd.clear();

	return 0;
}