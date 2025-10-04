#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Time complexity: O(logn)
int binarySearch(vector<int> a, int size, int target) {
	int left = 0;
	int right = size - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (a[mid] == target) {
			return mid;
		}
		else if (a[mid] < target) {
			left = mid + 1;
		}
		else right = mid - 1;
	}

	return -1;
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n), b(m);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	for (int i = 0; i < m; i++) {
		cin >> b[i];
	}

	int target;
	cin >> target;

	int first = 0, second = 0;
	bool found = false;
	int smallestProduct = INT_MAX;

	// For loop: O(n) + Binary search: O(logm) ==> O(nlogm)
	for (int i = 0; i < n; i++) {
		int b_value = target - a[i];
		int b_index = binarySearch(b, m, b_value);

		if (b_index != -1) {
			found = true;
			int product = a[i] * b_value;

			if (product < smallestProduct) {
				smallestProduct = product;
				first = a[i];
				second = b_value;
			}
		}
	}

	// Output
	cout << endl;
	if (found) {
		cout << first << " " << second;
	}
	else {
		cout << "No solution";
	}

	return 0;
}