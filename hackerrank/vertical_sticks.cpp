#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

int findLowerIndex(const vector<int>& array, const int value) {
	int lo = 0;
	int hi = array.size();

	int result = -1;
	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;

		if (array[mid] >= value) {
			hi = mid - 1;
		} else {
			result = mid;
			lo = mid + 1;
		}
	}
	return result;
}

double single_expected(const int nTotal, const int nSmaller) {
	const int nGreater = nTotal - nSmaller;
	return (double) (nTotal + 1) / (double) (nGreater + 1);
}

// the overall expected value is the summary of the expected values
// of each stick
double find_expected(const vector<int> sticks) {
	double total_expected = 0.0;

	for (int i = 0; i < sticks.size(); ++i) {
		// find how many are smaller and not inhibiting the ray
		int lIdx = findLowerIndex(sticks, sticks[i]);
		if (lIdx >= 0) { // there exist lIdx + 1 smaller elements
			total_expected += single_expected(sticks.size(), lIdx + 1);
		} else { // element is smallest
			total_expected += 1.0;
		}
	}
	return total_expected;
}

int main() {
	int nCases;
	cin >> nCases;
	while (--nCases >= 0) {
		int n;
		cin >> n;

		vector<int> sticks(n);
		for (int i = 0; i < n; ++i) {
			cin >> sticks[i];
		}

		sort(sticks.begin(), sticks.end());
		cout << fixed << setprecision(2) << find_expected(sticks) << endl;
	}
    return 0;
}
