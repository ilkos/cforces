#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

vector<int> findLcs(const vector<int>& lhs, const vector<int>& rhs) {
	// let dp[i][j] denote the LCS of strings lhs[0..i), rhs[0..j)
	vector<vector<int>> dp(lhs.size() + 1, vector<int>(rhs.size() + 1));

	for (int i = 1; i <= lhs.size(); ++i) {
		for (int j = 1; j <= rhs.size(); ++j) {
			if (lhs[i - 1] == rhs[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			} else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	vector<int> result;
	int x = lhs.size();
	int y = rhs.size();
	while (x > 0 && y > 0) {
		if (lhs[x - 1] == rhs[y - 1]) {
			result.push_back(lhs[x - 1]);
			--x; --y;
		} else {
			if (dp[x][y] == dp[x - 1][y]) {
				--x;
			} else {
				--y;
			}
		}
	}

	reverse(result.begin(), result.end());
	return result;
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> seq1(n);
	vector<int> seq2(m);

	for (int i = 0; i < n; ++i) {
		cin >> seq1[i];
	}

	for (int i = 0; i < m; ++i) {
		cin >> seq2[i];
	}

	vector<int> lcs = findLcs(seq1, seq2);
	for (int i = 0; i < lcs.size(); ++i) {
		if (i) cout << ' ';
		cout << lcs[i];
	}
	cout << endl;
    return 0;
}
