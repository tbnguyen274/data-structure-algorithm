#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

struct Employee {
	string ID;
	string name;
	int birthYear = 0;

	string toString() {
		return ID + ", " + name + ", " + to_string(birthYear);
	}
};

int correctBirthYear(int birthYear) {
	time_t t = time(nullptr);
	tm* currentTime = localtime(&t);
	int currentYear = 1900 + currentTime->tm_year;

	// correct birth year if it is too large
	if (birthYear > currentYear) {
		int year = birthYear % 100;
		if (year > currentYear % 100) {
			birthYear = 1900 + year;
		}
		else {
			birthYear = 2000 + year;
		}
	}
	return birthYear;
}

bool compare(Employee a, Employee b) {
	if (a.birthYear == b.birthYear) {
		return a.name < b.name;
	}
	return a.birthYear < b.birthYear;
}

void insertionSort(vector<Employee>& a) {
	int n = (int) a.size();
	for (int i = 1; i < n; i++) {
		Employee saved = a[i];
		int j = i;
		while (j > 0 && compare(saved, a[j - 1])) {
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

void selectionSort(vector<Employee>& a) {
	int n = (int) a.size();
	int max;
	for (int i = 0; i < n - 1; i++) {
		max = i;
		for (int j = i + 1; j < n; j++) {
			if (compare(a[j], a[max])) {
				max = j;
			}
		}
		if (max != i) {
			swap(a[max], a[i]);
		}
	}
}

void interchangeSort(vector<Employee>& a) {
	int n = (int) a.size();
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (compare(a[j], a[i])) {
				swap(a[i], a[j]);
			}
		}
	}
}

void printEmployees(vector<Employee> a) {
	int n = (int) a.size();
	for (int i = 0; i < n; i++) {
		cout << a[i].toString() << endl;
	}
	cout << endl;
}

vector<Employee> readEmployees(string filename) {
	ifstream inFile(filename);
	if (!inFile) {
		cerr << "File " << filename << " could not be opened." << endl;
		exit(1);
	}

	vector<Employee> employees;
	string line;
	getline(inFile, line);	// skip the first line

	while (getline(inFile, line)) {
		istringstream stream(line);
		Employee employee;

		getline(stream, employee.ID, ',');
		getline(stream, employee.name, ',');
		stream >> employee.birthYear;
		employee.birthYear = correctBirthYear(employee.birthYear);

		employees.push_back(employee);
	}

	inFile.close();
	return employees;
}

void sortEmployees(vector<Employee>& employees, int choice) {
	switch (choice) {
	case 1:
		insertionSort(employees);
		break;
	case 2:
		selectionSort(employees);
		break;
	case 3:
		interchangeSort(employees);
		break;
	default:
		cout << "Invalid choice" << endl;
	}
}

void writeEmployees(vector<Employee> employees, string filename) {
	ofstream outFile(filename);
	if (!outFile) {
		cerr << "File " << filename << " could not be opened." << endl;
		exit(1);
	}

	outFile << "ID, Name, Birth Year" << endl;
	for (int i = 0; i < employees.size(); i++) {
		outFile << employees[i].toString();
		if (i < employees.size() - 1) {
			outFile << endl;
		}
	}

	outFile.close();
	cout << "Data written to " << filename << endl;
}


int main() {
	
	string input = "employee.txt";
	vector<Employee> employees = readEmployees(input);

	// choose sorting algorithm
	int choice;
	cout << "1. Insertion sort" << endl;
	cout << "2. Selection sort" << endl;
	cout << "3. Interchange sort" << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	cout << endl;

	cout << "Original employees:" << endl;
	printEmployees(employees);

	// sort employees
	sortEmployees(employees, choice);

	cout << "Sorted employees:" << endl;
	printEmployees(employees);

	// Write the sorted data to file sortedemponage.txt
	string output = "sortedemponage.txt";
	writeEmployees(employees, output);

	employees.clear();

	return 0;
}
