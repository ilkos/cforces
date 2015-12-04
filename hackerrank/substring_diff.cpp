#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> getPrefixDiff(const string& p, const string& q) {
	const int n = p.size();
	vector<vector<int>> prefixDiff(n, vector<int>(n));
	for (int j = 0; j < n; ++j) {
		prefixDiff[j][0] = p[0] == q[j] ? 0 : 1;
		for (int i = 1; i + j < n; ++i) {
			prefixDiff[j][i] = prefixDiff[j][i - 1] + (p[i] == q[i + j] ? 0 : 1);
		}
	}

	return prefixDiff;
}

bool existsSolution(const vector<vector<int>>& prefixDiffPQ, const vector<vector<int>> prefixDiffQP,
					const int S, const int L) {
	if (!L) {
		return true;
	}

	for (int i = 0; i < prefixDiffPQ.size(); ++i) {
		for (int j = 0; i + j + L < prefixDiffPQ.size(); ++j) { // string [j..j + L], [i + j..i + j + L]
			if (prefixDiffPQ[i][j + L] - (j > 0 ? prefixDiffPQ[i][j - 1] : 0) <= S) {
				return true;
			}
		}
	}

	for (int i = 0; i < prefixDiffQP.size(); ++i) {
		for (int j = 0; i + j + L < prefixDiffQP.size(); ++j) {
			if (prefixDiffQP[i][j + L] - (j > 0 ? prefixDiffQP[i][j - 1] : 0) <= S) {
				return true;
			}
		}
	}

	return false;
}

int solve(const int s, const string& p, const string& q) {
	// store prefix sums of differences between p, q
	int n = p.size();

	// prefixDiff[i][j] is the prefix sum of the difference of p[0..i], q[j..i+j]
	vector<vector<int>> prefixDiffPQ = getPrefixDiff(p, q);
	vector<vector<int>> prefixDiffQP = getPrefixDiff(q, p);

	int lo = 0;
	int hi = n;
	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		if (existsSolution(prefixDiffPQ, prefixDiffQP, s, mid)) {
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}

	return lo;
}

int main() {
	int nCases;
	cin >> nCases;

	while (--nCases >= 0) {
		int s;
		string p, q;
		cin >> s >> p >> q;

		cout << solve(s, p, q) << endl;
	}
    return 0;
}
