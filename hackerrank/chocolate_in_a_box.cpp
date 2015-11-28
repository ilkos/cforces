#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int solve(const int n, const vector<int>& containers) {
	int xorAll = 0;
	for (int num: containers) {
		xorAll ^= num;
	}

	if (!xorAll) {
		return 0;
	}

	// number of ways we can remove from containers so that xorAll becomes 0
	// game of Nim
	int numWays = 0;
	for (int num: containers) {
		int tgt = xorAll ^ num;
		if (tgt < num) ++numWays;
	}
	return numWays;
}

int main() {
	int n;
	cin >> n;
	vector<int> containers(n);
	for (int i = 0; i < n; ++i) {
		cin >> containers[i];
	}

	cout << solve(n, containers) << endl;
    return 0;
}
