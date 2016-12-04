#include <iostream>
#include <vector>
using namespace std;

// Returns distinct number of ways you can write nLines with a quota of nBugs
int solve(const vector<int>& bugsPerLine,
	const int modulo,
	const int nLines,
	const int nBugs) {
	// dp[i][j] denotes the number of ways that you can write i lines with *exactly* j bugs
	vector<vector<int>> dp(nLines + 1, vector<int>(nBugs + 1, 0));
	dp[0][0] = 1;

	for (int pBugs : bugsPerLine) { // introduce programmer with pBugs
		for (int i = 1; i <= nLines; ++i) {
			for (int j = pBugs; j <= nBugs; ++j) {
				dp[i][j] += dp[i - 1][j - pBugs];
				dp[i][j] %= modulo;
			}
		}
	}

	int acc = 0;
	for (int i = 0; i <= nBugs; ++i) {
		acc += dp[nLines][i];
		acc %= modulo;
	}
	return acc;
}

int main() {
	int nProgrammers, nLines, nBugs, modulo;
	cin >> nProgrammers >> nLines >> nBugs >> modulo;

	vector<int> bugsPerLine(nProgrammers);
	for (int i = 0; i < nProgrammers; ++i) {
		cin >> bugsPerLine[i];
	}

	cout << solve(bugsPerLine, modulo, nLines, nBugs) << endl;
}