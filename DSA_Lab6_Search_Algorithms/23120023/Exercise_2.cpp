#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct WORD {
	string name;
	string definition;
};

// Apply any search algorithm to create dictionary software.
int search(vector<WORD> dictionary, string word) {		// Use binary search
	int left = 0;
	int right = dictionary.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (word > dictionary[mid].name) {
			left = mid + 1;
		}
		else if (word < dictionary[mid].name) {
			right = mid - 1;
		}
		else return mid;
	}
	return -1;
}

string trim(string str) {
	int start = 0;
	while (start < str.length() && str[start] == ' ') {
		start++;
	}
	int end = str.length() - 1;
	while (end >= 0 && str[end] == ' ') {
		end--;
	}
	return str.substr(start, end - start + 1);
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cout << "Usage: Exercise_2.exe <word1> <word2> ... <output.txt>" << endl;
		return 1;
	}

	ifstream inFile("dictionary.txt");
	if (!inFile) {
		cout << "Cannot open dictionary.txt" << endl;
		return 1;
	}

	vector<WORD> dictionary;
	string line;

	while (getline(inFile, line)) {
		int pos = line.find(":");
		if (pos == string::npos) {		// cannot find ':'
			cout << "Invalid dictionary format" << endl;
			return 1;
		}

		WORD word;
		word.name = line.substr(0, pos);
		word.definition = line.substr(pos + 1);

		// remove leading and trailing spaces
		word.name = trim(word.name);
		word.definition = trim(word.definition);

		dictionary.push_back(word);
	}
	inFile.close();

	// start searching
	char* outputFile = argv[argc - 1];
	ofstream outFile(outputFile);
	if (!outFile) {
		cout << "Cannot open " << outputFile << endl;
		return 1;
	}

	for (int i = 1; i < argc - 1; i++) {
		int res = search(dictionary, argv[i]);
		if (res == -1) {
			outFile << argv[i] << ": khong tim thay";
		}
		else {
			outFile << dictionary[res].name << ": " << dictionary[res].definition;
		}
		if (i < argc - 2) outFile << endl;
	}

	cout << "Search completed. Check " << outputFile << " for results." << endl;
	outFile.close();

	// free memory
	dictionary.clear();

	return 0;
}