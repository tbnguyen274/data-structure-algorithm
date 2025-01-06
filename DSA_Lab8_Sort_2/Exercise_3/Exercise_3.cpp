#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

string doubleToString(double x) {
	stringstream ss;
	ss << fixed << setprecision(2) << x;
	return ss.str();
}

// truncated to two decimal positions right of the point
double rounded(double x) {
	return round(x * 100.0) / 100.0;
}

struct Candidate {
	string name;
	double score1 = 0, score2 = 0;
	vector<int> options;
	double average = 0;

	string toString() {
		return name + " " + doubleToString(average);
	}

	void trimName() {
		name = name.substr(1, name.size() - 2);
	}
};

struct Pair {
	int first, second;
};


double calculateAverage(double score1, double score2) {
	return (score1 + score2) / 2.0;
}


bool compareCandidates(const Candidate& c1, const Candidate& c2) {
	if (c1.average != c2.average) {
		return c1.average < c2.average;
	}
	if (c1.score1 != c2.score1) {
		return c1.score1 < c2.score1;
	}
	return c1.score2 < c2.score2;
}


void swap(Candidate& c1, Candidate& c2) {
	Candidate temp = c1;
	c1 = c2;
	c2 = temp;
}


void sortCandidates(vector<Candidate>& candidates) {
	for (int i = 0; i < candidates.size() - 1; i++) {
		for (int j = i + 1; j < candidates.size(); j++) {
			if (compareCandidates(candidates[i], candidates[j])) {
				swap(candidates[i], candidates[j]);
			}
		}
	}
}

int main() {

	string fileName = "Exercise_3.txt";
	ifstream file(fileName);
	if (!file) {
		cerr << "File not found." << endl;
		return -1;
	}

	int m;	// number of options
	file >> m;

	vector<Pair> options(m);
	for (int i = 0; i < m; i++) {
		file >> options[i].first >> options[i].second;
	}

	vector<Candidate> candidates;
	string line;

	// separate by ,
	while(getline(file, line)) {
		if (line.empty()) {
			continue;
		}

		Candidate candidate;
		stringstream ss(line);

		getline(ss, candidate.name, ',');
		candidate.trimName();

		ss >> candidate.score1;
		candidate.score1 = rounded(candidate.score1);

		ss.ignore(1);	// ignore ,
		ss >> candidate.score2;
		candidate.score2 = rounded(candidate.score2);

		candidate.average = calculateAverage(candidate.score1, candidate.score2);
		candidate.average = rounded(candidate.average);

		for (int i = 0; i < m; i++) {
			int option;
			ss.ignore(1);
			ss >> option;
			candidate.options.push_back(option);
		}

		candidates.push_back(candidate);
	}

	file.close();

	// sort candidates
	sortCandidates(candidates);

	vector<vector<Candidate>> successfulCandidates(m);
	vector<Candidate> unsuccessfulCandidates;

	for (int i = 0; i < candidates.size(); i++) {
		Candidate candidate = candidates[i];
		bool isSuccessful = false;

		for (int j = 0; j < candidate.options.size(); j++) {
			int option = candidate.options[j] - 1;

			if (successfulCandidates[option].size() < options[option].second) {
				successfulCandidates[option].push_back(candidate);
				isSuccessful = true;
				break;
			}
			
			//  If equality persists, increase the number of available positions from a certain option
			else if (candidate.average == successfulCandidates[option].back().average &&
				candidate.score1 == successfulCandidates[option].back().score1 &&
				candidate.score2 == successfulCandidates[option].back().score2)
			{
				options[option].second++;
				successfulCandidates[option].push_back(candidate);
				isSuccessful = true;
				break;
			}
						
		}
		
		if (!isSuccessful) {
			unsuccessfulCandidates.push_back(candidate);
		}
	}

	ofstream outFile("output.txt");
	if (!outFile) {
		cerr << "File not found." << endl;
		return -1;
	}

	for (int i = 0; i < m; i++) {
		outFile << "Successful candidates for option " << i + 1 << ":\n";
		for (int j = 0; j < successfulCandidates[i].size(); j++) {
			outFile << j + 1 << ". " << successfulCandidates[i][j].toString() << endl;
		}
		outFile << endl;
	}

	outFile << "Unsuccessful candidates:\n";
	for (int i = 0; i < unsuccessfulCandidates.size(); i++) {
		outFile << i + 1 << ". " << unsuccessfulCandidates[i].toString();
		if (i != unsuccessfulCandidates.size() - 1) {
			outFile << endl;
		}
	}

	outFile.close();

	cout << "The results are saved in output.txt.\n\n";

	// write to console
	for (int i = 0; i < m; i++) {
		cout << "Successful candidates for option " << i + 1 << ":\n";
		for (int j = 0; j < successfulCandidates[i].size(); j++) {
			cout << j + 1 << ". " << successfulCandidates[i][j].toString() << endl;
		}
		cout << endl;
	}

	cout << "Unsuccessful candidates:\n";
	for (int i = 0; i < unsuccessfulCandidates.size(); i++) {
		cout << i + 1 << ". " << unsuccessfulCandidates[i].toString();
		if (i != unsuccessfulCandidates.size() - 1) {
			cout << endl;
		}
	}

	// delete memory
	options.clear();
	candidates.clear();

	for (int i = 0; i < m; i++) {
		successfulCandidates[i].clear();
	}

	successfulCandidates.clear();
	unsuccessfulCandidates.clear();

	return 0;
}