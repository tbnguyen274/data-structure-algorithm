#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <iomanip>

using namespace std;


void printMatrix(vector<vector<int>> a) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[i].size(); j++) {
			cout << setw(2) << a[i][j] << "  ";
		}
		cout << endl;
	}
}

vector<int> traverseMatrix(vector<vector<int>> a) {
	vector<int> res;
	int rows = (int) a.size();
	int cols = (int) a[0].size();
	int top = 0, bottom = rows - 1, left = 0, right = cols - 1;

	while (top <= bottom && left <= right) {
		
		for (int i = left; i <= right; i++) {
			res.push_back(a[top][i]);
		}
		top++;

		for (int i = top; i <= bottom; i++) {
			res.push_back(a[i][right]);
		}
		right--;

		if (top <= bottom) {
			for (int i = right; i >= left; i--) {
				res.push_back(a[bottom][i]);
			}
			bottom--;
		}

		if (left <= right) {
			for (int i = bottom; i >= top; i--) {
				res.push_back(a[i][left]);
			}	
			left++;
		}
	}

	return res;
}


void insertionSort(vector<int>& a) {
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

void sortSpiralMatrix(vector<vector<int>>& a) {
	vector<int> res = traverseMatrix(a);
	insertionSort(res);

	int rows = (int) a.size();
	int cols = (int) a[0].size();
	int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
	int index = 0;

	while (top <= bottom && left <= right) {

		for (int i = left; i <= right; i++) {
			a[top][i] = res[index++];
		}
		top++;

		for (int i = top; i <= bottom; i++) {
			a[i][right] = res[index++];
		}
		right--;

		if (top <= bottom) {
			for (int i = right; i >= left; i--) {
				a[bottom][i] = res[index++];
			}
			bottom--;
		}

		if (left <= right) {
			for (int i = bottom; i >= top; i--) {
				a[i][left] = res[index++];
			}
			left++;
		}
	}
}


int main() {
	srand((unsigned int)(time(NULL)));
	int n = 3 + rand() % 8;
	int m = 3 + rand() % 8;

	// generate a random matrix
	vector<vector<int>> a(n, vector<int>(m));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] = rand() % 100;
		}
	}

	cout << "Original matrix:" << endl;
	printMatrix(a);
	cout << endl;

	// sort the matrix in spiral order
	sortSpiralMatrix(a);

	cout << "Sorted matrix in spiral order:" << endl;
	printMatrix(a);

	// delete matrix
	for (int i = 0; i < n; i++) {
		a[i].clear();
	}
	a.clear();

	return 0;
}