#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int linearSearch(int* a, int n, int target) {
	for (int i = 0; i < n; i++) {
		if (a[i] == target) return i;
	}
	return -1;
}

int linearSearchWithSentinel(int* a, int n, int target) {
	int last = a[n - 1];
	a[n - 1] = target;	// Set sentinel
	int i = 0;
	while (a[i] != target) i++;
	a[n - 1] = last;
	if (i < n - 1 || a[n - 1] == target) return i;		// Target found
	return -1;
}


int binarySearch(int* a, int n, int target) {
	int left = 0;
	int right = n - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (target > a[mid]) {
			left = mid + 1;
		}
		else if (target < a[mid]) {
			right = mid - 1;
		}
		else return mid;
	}

	return -1;
}

bool readFile(char* file, int*& a, int& n) {
	FILE* fp = fopen(file, "r");
	if (fp == NULL) {
		cout << "Cannot open file " << file << endl;
		return false;
	}
	fscanf(fp, "%d\n", &n);
	a = new int[n];
	for (int i = 0; i < n; i++) {
		fscanf(fp, "%d", &a[i]);
	}
	fclose(fp);
	return true;
}

bool writeFile(char* file, int res) {
	FILE* fp = fopen(file, "w");
	if (fp == NULL) {
		cout << "Cannot open file " << file << endl;
		return false;
	}
	fprintf(fp, "%d", res);
	fclose(fp);
	return true;
}

int main(int argc, char* argv[]) {
	if (argc != 5) {
		cout << "Usage: Exercise_1.exe <algorithm> <x> <input.txt> <output.txt>" << endl;
		return 1;
	}

	// Parse command line arguments
	int algorithm = stoi(argv[1]);
	int target = stoi(argv[2]);
	char* inputFile = argv[3];
	char* outputFile = argv[4];

	int* a;
	int n;
	if (!readFile(inputFile, a, n)) {
		return 1;
	}

	int res = -1;
	if (algorithm == 1) {
		res = linearSearch(a, n, target);
	}
	else if (algorithm == 2) {
		res = linearSearchWithSentinel(a, n, target);
	}
	else if (algorithm == 3) {
		res = binarySearch(a, n, target);
	}
	else {
		cout << "Invalid algorithm" << endl;
		return 1;
	}
	
	if (!writeFile(outputFile, res)) {
		return 1;
	}

	cout << "Search completed. Check " << outputFile << " for result." << endl;
	
	delete[] a;
	return 0;
}