#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> memo;

bool isPossible(const int n, const vector<vector<char>>& grid,
				int topIdx, int bottomIdx) {
	
	while (topIdx < n && grid[0][topIdx]) ++topIdx;
	while (bottomIdx < n && grid[1][bottomIdx]) ++bottomIdx;

	if (topIdx == n && bottomIdx == n) {
		return true;
	} else if (topIdx > n || bottomIdx > n) {
		return false;
	}

	// fill the grid left to right, memoize solutions of top, bottom
	if (memo[topIdx][bottomIdx] >= 0) {
		return memo[topIdx][bottomIdx];
	}

	bool isPoss = false;
	if (topIdx == bottomIdx || topIdx == bottomIdx + 1) {
		isPoss |= isPossible(n, grid, topIdx + 1, bottomIdx + 1);
	}

	if (topIdx + 1 < n && !grid[0][topIdx + 1]) {
		isPoss |= isPossible(n, grid, topIdx + 2, bottomIdx);
	}

	if (bottomIdx + 1 < n && !grid[1][bottomIdx + 1]) {
		isPoss |= isPossible(n, grid, topIdx, bottomIdx + 2);
	}

	return memo[topIdx][bottomIdx] = isPoss;
}

int main() {
	int nCases;
	cin >> nCases;

	while (nCases-- > 0) {
		int n;
		cin >> n;
		vector<vector<char>> grid = vector<vector<char>>(2, vector<char>(n));
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> grid[i][j];
				grid[i][j] = grid[i][j] == '0' ? 0 : 1;
			}
		}

		memo = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));
		bool poss = isPossible(n, grid, 0, 0);
		cout << (poss ? "YES" : "NO") << endl;
	}
    return 0;
}
