#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int solve(const int n, vector<int>& puzzles) {
	sort(puzzles.begin(), puzzles.end());

	int minDist = numeric_limits<int>::max();
	for (int i = 0; i + n - 1 < puzzles.size(); ++i) {
		minDist = min(minDist, puzzles[i + n - 1] - puzzles[i]);
	}
	return minDist;
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<int> sizes = vector<int>(m);
	for (int i = 0; i < m; ++i) {
		cin >> sizes[i];
	}

	cout << solve(n, sizes) << endl;
}