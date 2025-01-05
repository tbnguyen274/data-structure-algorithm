#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAX 1024


// Functions prototype
bool readMatrix(const char* filename, int**& matrix, int& rows, int& cols);
void printMatrix(const char* filename, int** matrix, int rows, int cols);
bool multiplyMatrices(int** a, int aRows, int aCols,
	int** b, int bRows, int bCols,
	int**& res, int& resRows, int& resCols);
void printMatrixToConsole(int** matrix, int rows, int cols);


int main() {
	int aRows, aCols;
	int** a = NULL;
	if (readMatrix("matrix_a.txt", a, aRows, aCols)) {
		cout << "Matrix a:" << endl;
		printMatrixToConsole(a, aRows, aCols);
	}
	else {
		cout << "Failed to read matrix a!" << endl;
	}

	int bRows, bCols;
	int** b = NULL;
	if (readMatrix("matrix_b.txt", b, bRows, bCols)) {
		cout << "Matrix b:" << endl;
		printMatrixToConsole(b, bRows, bCols);
	}
	else {
		cout << "Failed to read matrix b!" << endl;
	}

	int cRows, cCols;
	int** c = NULL;
	if (multiplyMatrices(a, aRows, aCols, b, bRows, bCols, c, cRows, cCols)) {
		cout << "The multiplication is successful!" << endl;
		cout << "Matrix c:" << endl;
		printMatrixToConsole(c, cRows, cCols);

		// Print the resulting matrix c to the file matrix_c.txt
		printMatrix("matrix_c.txt", c, cRows, cCols);
	}
	else {
		cout << "Failed to multiply matrices!" << endl;
	}
	return 0;
}


/*
Read Matrix from File: Write a function to read a matrix from a file.
Return false if the file cannot be opened or the file structure is invalid. Else, return true
Each row of the matrix on a separate line and elements separated by spaces. For example:
1 2 3
4 5 6
*/
bool readMatrix(const char* filename, int**& matrix, int& rows, int& cols) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		cout << "Failed to open file!" << endl;
		return false;
	}

	rows = 0;
	cols = 0;
	int tempCols = 0;
	char line[MAX];

	// Get rows and cols
	while (fgets(line, sizeof(line), fp)) {
		rows++;
		tempCols = 0;
		char* token = strtok(line, " ");
		while (token) {
			tempCols++;
			token = strtok(NULL, " ");
		}

		if (cols == 0) {
			// cols = tempCols = 0: first row is blank
			if (tempCols == 0) {
				cout << "First row is blank!" << endl;
				fclose(fp);
				return false;
			}
			// get cols
			cols = tempCols;
		}
		else if (tempCols != cols) {
			cout << "Invalid file structure!" << endl;
			fclose(fp);
			return false;
		}
	}

	if (rows == 0) {
		cout << "Empty file!" << endl;
		fclose(fp);
		return false;
	}

	// Read matrix
	rewind(fp);
	matrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
		for (int j = 0; j < cols; j++) {
			fscanf(fp, "%d", &matrix[i][j]);
		}
	}

	fclose(fp);
	return true;
}

/*
Print Matrix to File: Write a function to print a matrix to a file.
Each row of the matrix on a separate line and elements separated by spaces. For example:
1 2 3
4 5 6
*/
void printMatrix(const char* filename, int** matrix, int rows, int cols) {
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		cout << "Cannot open file!" << endl;
		return;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fprintf(fp, "%d", matrix[i][j]);
			if (j < cols - 1) {
				fprintf(fp, " ");
			}
		}
		if (i < rows - 1) {
			fprintf(fp, "\n");
		}
	}

	fclose(fp);
}

/*
Matrix Multiplication: Write a function to multiply two matrices.
Return a boolean value indicating whether the multiplication is successful or not.
*/
bool multiplyMatrices(int** a, int aRows, int aCols,
	int** b, int bRows, int bCols,
	int**& res, int& resRows, int& resCols)
{
	if (aRows == 0 || aCols == 0 || bRows == 0 || bCols == 0) {
		cout << "Invalid matrix size!" << endl;
		return false;
	}

	if (aCols != bRows) {
		cout << "Invalid matrix size for multiplication!" << endl;
		return false;
	}

	resRows = aRows;
	resCols = bCols;
	res = new int* [resRows];

	for (int i = 0; i < resRows; i++) {
		res[i] = new int[resCols];
		for (int j = 0; j < resCols; j++) {
			res[i][j] = 0;
			for (int k = 0; k < aCols; k++) {
				res[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	return true;
}

// Print matrix to console
void printMatrixToConsole(int** matrix, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}