#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// + to everyone else is equivalent to - to self
int findMinMovesToTarget(const vector<int>& choc, const int tgt) {
	int counter = 0;

	for (const int num: choc) {
		int diff = num - tgt;
		counter += diff / 5;
		diff = diff % 5;
		counter += diff / 2;
		diff = diff % 2;
		counter += diff;
	}
	
	return counter;
}

int findMinOps(const vector<int>& choc) {
	int minChoc = numeric_limits<int>::max();
	for (int n: choc) minChoc = min(minChoc, n);

	int best = numeric_limits<int>::max();
	for (int target = minChoc; target >= 0; target--) {
		best = min(best, findMinMovesToTarget(choc, target));
	}
	return best;
}

int main() {
	int nCases;
	cin >> nCases;

	while (nCases-- > 0) {
		int n;
		cin >> n;
		vector<int> choc(n);
		for (int i = 0; i < n; ++i) cin >> choc[i];

		cout << findMinOps(choc) << endl;
	}
    return 0;
}
