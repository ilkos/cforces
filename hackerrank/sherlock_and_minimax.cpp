#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Solution {
	Solution() : miniMax(0), miniMaxSelected(-1) {}
	int miniMax;
	int miniMaxSelected;

	void evalCandidate(const int candidateDiff, const int candidateSelected) {
		if (candidateDiff > miniMax ||
				(candidateDiff == miniMax && candidateSelected < miniMaxSelected)) {
			miniMax = candidateDiff;
			miniMaxSelected = candidateSelected;
		}
	}
};

int findMinDiff(const vector<int>& array, const int num) {
	int minDiff = numeric_limits<int>::max();
	for (int i = 0; i < array.size(); ++i) {
		minDiff = min(minDiff, abs(array[i] - num));
	}
	return minDiff;
}

// up to 100 elements in array, but iterating p -> q infeasible
int solve(const vector<int>& array, const int p, const int q) {
	Solution solution;
	solution.evalCandidate(findMinDiff(array, p), p);
	solution.evalCandidate(findMinDiff(array, q), q);

	// array is sorted
	// select middle of gaps between elements
	for (int i = 0; i < array.size() - 1; ++i) {
		int mid = array[i] + (array[i + 1] - array[i]) / 2;
		if (mid < p || mid > q) continue;
		solution.evalCandidate(mid - array[i], mid);
	}

	return solution.miniMaxSelected;
}

int main() {
	int n;
	cin >> n;
	vector<int> array(n);
	for (int i = 0; i < n; ++i) {
		cin >> array[i];
	}
	int p, q;
	cin >> p >> q;

	sort(array.begin(), array.end());
	cout << solve(array, p, q) << endl;
    return 0;
}
