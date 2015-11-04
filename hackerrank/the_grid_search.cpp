#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

bool matches(const vector<string>& grid, const vector<string>& pattern, int row, int col) {
	for (int i = 1; i < pattern.size(); ++i) {
		if (grid[row + i].substr(col, pattern[i].size()) != pattern[i]) {
			return false;
		}
	}

	return true;
}

bool findIt(const vector<string>& grid, const vector<string>& pattern) {
	for (int i = 0; i < grid.size() - pattern.size() + 1; ++i) {
		size_t foundPos = 0;
		while (foundPos < grid[i].size()) {
			foundPos = grid[i].find(pattern[0], foundPos);

			if (foundPos == string::npos) break;
			if (matches(grid, pattern, i, foundPos)) {
				return true;
			}
			++foundPos;
		}
	}

	return false;
}

int main() {
	int nCases;
	cin >> nCases;
	while (nCases-- > 0) {
		int r, c;
		cin >> r >> c;
		vector<string> grid(r);
		for (int i = 0; i < r; ++i) {
			cin >> grid[i];
		}

		cin >> r >> c;
		vector<string> pattern(r);
		for (int i = 0; i < r; ++i) {
			cin >> pattern[i];
		}

		bool found = findIt(grid, pattern);
		cout << (found ? "YES" : "NO") << endl;
	}
    return 0;
}
