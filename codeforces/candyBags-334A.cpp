#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;

	// n ranges of numbers, where n is even
	// each two ranges can neutralise each other leading to same overall sums
	vector<vector<int>> bags(n, vector<int>(n));
	int cnt = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			bags[i][j] = cnt++;
		}
		if (i % 2 == 0) reverse(bags[i].begin(), bags[i].end());
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << bags[j][i] << ' ';
		}
		cout << endl;
	}
}
