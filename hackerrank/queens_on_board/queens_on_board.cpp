#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const static int MOD = 1000000007;

bool isAvailable(const vector<string>& board, int row, int col) {
	if (board[row][col] != '.') {
		return false;
	}

	// only scan left as we construct left to right
	for (int hpos = col; hpos >= 0; --hpos) {
		if (board[row][hpos] == 'Q') {
			return false;
		} else if (board[row][hpos] == '#') {
			break;
		}
	}

	// only scan upwards as we construct top to bottom
	for (int vpos = row; vpos >= 0; --vpos) {
		if (board[vpos][col] == 'Q') {
			return false;
		} else if (board[vpos][col] == '#') {
			break;
		}
	}

	// scan diag
	for (int vpos = row, hpos = col; vpos >= 0 && hpos >= 0; --vpos, --hpos) {
		if (board[vpos][hpos] == 'Q') {
			return false;
		} else if (board[vpos][hpos] == '#') {
			break;
		}
	}

	for (int vpos = row, hpos = col; vpos >= 0 && hpos < board[vpos].size(); --vpos, ++hpos) {
		if (board[vpos][hpos] == 'Q') {
			return false;
		} else if (board[vpos][hpos] == '#') {
			break;
		}
	}

	return true;
}

// evaluating all possible positionings is infeasible
// meaning we have to express options as a combination of previous decisions
// Since M <= 5, it also means each positioned queen can only have an influence
// of up to 4 rows suceeding it (diagonally)
// If we can express threats from previous rows on the current (and essentially next) row as 3 bitmasks
// (vertical, diagonal left, diagonal right), then we can calculate count based on previously fetched results
// dp[row][mask1][mask2][mask3]
int64_t countAvailableFromRow(vector<string>& board, int row, int col) {

	for (int i = row; i < board.size(); ++i) {
		for (int j = col; j < board[0].size(); ++j) {
			if (isAvailable(board, i, j)) {
				// do
				board[i][j] = 'Q';
				int64_t with = countAvailableFromRow(board, i, j + 1);
				board[i][j] = '.';

				int64_t without = countAvailableFromRow(board, i, j + 1);
				return (with + without) % MOD;
			}
		}
		col = 0;
	}

	return 1;
}

int main() {
	int nCases;
	cin >> nCases;

	while (nCases-- > 0) {
		int n, m;
		cin >> n >> m;

		vector<string> board(n);
		for (int i = 0; i < n; ++i) {
			cin >> board[i];
		}

		cout << countAvailableFromRow(board, 0, 0) - 1 << endl;
	}
    return 0;
}
