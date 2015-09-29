#include <iostream>
#include <vector>

using namespace std;

int getPosModulo(int num, int m) {
	num %= m;
	return num >= 0 ? num : num + m;
}

bool solve(const vector<int>& nums, const int m) {
	// needs linear time algorithm
	// let dp[i][j] denote if using i ints from nums, we can achieve a sum j (where j = sum % m)
	auto dp = vector<vector<bool>>(nums.size() + 1, vector<bool>(m + 1, false));
	dp[0][0] = true;

	for (int i = 0; i < nums.size(); ++i) {
		for (int j = 0; j <= m; ++j) {
			dp[i + 1][j] = dp[i][getPosModulo(j - nums[i], m)] | dp[i][j];
		}
	}

	return dp[nums.size()][m];
}

int main() {
	int n, m;
	cin >> n >> m;
	if (n > m) {
		cout << "YES" << endl;
		return 0;
	}

	auto nums = vector<int>(n);
	for (int i = 0; i < n; ++i) {
		cin >> nums[i];
	}

	bool isPossible = solve(nums, m);
	cout << (isPossible ? "YES" : "NO") << endl;
}