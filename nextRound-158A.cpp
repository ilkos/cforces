#include <iostream>
#include <vector>

using namespace std;

int solve(const vector<int>& results, int k) {
	while (k + 1 < results.size() && results[k + 1] == results[k]) ++k;

	while (k >= 0 && results[k] == 0) --k;

	return k + 1;
}

int main() {
	int n, k;
	cin >> n >> k;

	vector<int> results = vector<int>(n);
	for (int i = 0; i < n; ++i) {
		cin >> results[i];
	}

	cout << solve(results, k - 1) << endl;
}