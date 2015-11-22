#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <limits>
using namespace std;

struct Solver {
	const int UNKNOWN = -100000;

	const int n;
	const int m;
	const vector<string> board;
	vector<vector<vector<int>>> memo;

	const char directions[4][3] = {
		{'U', -1, 0},
		{'L', 0, -1},
		{'D', 1, 0},
		{'R', 0, 1}
	};

	Solver(int n, int m, const vector<string>& board) :
		n(n), m(m), board(board) {
	}

	int solve(int k) {
		memo = vector<vector<vector<int>>>(k + 1, vector<vector<int>>(n, vector<int>(m, UNKNOWN)));
		return solvePos(k, 0, 0);
	}

	int solvePos(const int k, const int posx, const int posy) {
		if (k < 0) {
			return -1;
		}

		if (board[posx][posy] == '*') {
			return 0;
		}

		if (memo[k][posx][posy] != UNKNOWN) {
			return memo[k][posx][posy];
		}

		int result = numeric_limits<int>::max();
		for (int i = 0; i < 4; ++i) {
			int newx = posx + directions[i][1];
			int newy = posy + directions[i][2];

			if (newx < 0 || newx >= n || newy < 0 || newy >= m) continue;

			int r = solvePos(k - 1, newx, newy);
			if (r < 0) continue;

			result = min(result, r + (board[posx][posy] == directions[i][0] ? 0 : 1));
		}

		return memo[k][posx][posy] = (result == numeric_limits<int>::max() ? -1 : result);
	}
};

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<string> board(n);
	for (int i = 0; i < n; ++i) {
		cin >> board[i];
	}

	Solver solver(n, m, board);
	cout << solver.solve(k) << endl;
    return 0;
}
