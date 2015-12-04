#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> memo;
int findMax(const vector<int>& bList, const int idx, const bool prevMax) {
	if (idx >= bList.size()) {
		return 0;
	}

	if (memo[idx][prevMax] >= 0) {
		return memo[idx][prevMax];
	}

	const int prevValue = prevMax ? bList[idx - 1] : 1;

	int best = 0;
	// either select smallest possible value
	best = abs(1 - prevValue) + findMax(bList, idx + 1, false);

	// or greatest
	best = max(best, abs(bList[idx] - prevValue) + findMax(bList, idx + 1, true));
	return memo[idx][prevMax] = best;
}

int main() {
	int nCases;
	cin >> nCases;
	while (--nCases >= 0) {
		int n;
		cin >> n;
		vector<int> bList(n);
		for (int i = 0; i < n; ++i) {
			cin >> bList[i];
		}

		memo = vector<vector<int>>(n, vector<int>(2, -1));
		cout << max(findMax(bList, 1, false), findMax(bList, 1, true)) << endl;
	}
    return 0;
}
