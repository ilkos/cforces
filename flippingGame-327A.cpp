#include <iostream>
#include <vector>

using namespace std;

// we want to flip and get max number of ones
// therefore we must find and flip the subsequence with the max number of 0s
// max contiguous subarray where 0 -> 1 and 1 -> -1
int solve(vector<int>& values) {
	int best = 0;
	int bestLo = 0;
	int bestHi = 0;

	int currLo = 0, curr = 0;	
	for (int i = currLo; i < values.size(); ++i) {
		curr += (values[i] == 0 ? 1 : -1);
		if (curr > best) {
			bestLo = currLo;
			bestHi = i;
			best = curr;
		}
		if (curr < 0) {
			curr = 0;
			currLo = i + 1;
		}
	}

	for (int i = bestLo; i <= bestHi; ++i) {
		values[i] = 1 - values[i];
	}

	int result = 0;
	for (int i = 0; i < values.size(); ++i) {
		result += values[i];
	}

	return result;
}

int main() {
	int n;
	cin >> n;

	vector<int> values(n);
	for (int i = 0; i < n; ++i) {
		cin >> values[i];
	}

	cout << solve(values) << endl;
}