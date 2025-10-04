#include <iostream>
#include <vector>

using namespace std;

struct Pair {
	int start;
	int end;
};

void swap(Pair& a, Pair& b) {
	Pair temp = a;
	a = b;
	b = temp;
}

void sortIntervals(vector<Pair>& intervals) {
	int n = (int) intervals.size();

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			// Sort ascending based on start --> time in order
			if (intervals[i].start > intervals[j].start) {
				swap(intervals[i], intervals[j]);
			}
		}
	}
}


int main() {
	int n;
	cin >> n;

	vector<Pair> intervals(n);

	for (int i = 0; i < n; i++) {
		Pair p;
		cin >> p.start >> p.end;
		intervals[i] = p;
	}

	sortIntervals(intervals);

	vector<Pair> merged;
	merged.push_back(intervals[0]);

	for (int i = 1; i < n; i++) {
		if (merged.back().end < intervals[i].start) {
			merged.push_back(intervals[i]);
		}
		else {
			if (intervals[i].end > merged.back().end) {
				merged.back().end = intervals[i].end;
			}
		}
	}

	// Output
	cout << endl;
	for (int i = 0; i < merged.size(); i++) {
		cout << merged[i].start << " " << merged[i].end << endl;
	}

	return 0;
}