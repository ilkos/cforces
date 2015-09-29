#include <iostream>
#include <vector>
using namespace std;

int64_t solve(const vector<int>& nums, int hi, vector<int64_t>& maxScores) {
	if (hi == 1) {
		return nums[hi];
	}
	if (hi == 0) {
		return 0;
	}

	if (maxScores[hi] >= 0) {
		return maxScores[hi];
	}

	return maxScores[hi] = max(
		(int64_t) nums[hi] * hi + solve(nums, hi - 2, maxScores),
		solve(nums, hi - 1, maxScores));
}

int main() {
	int n;
	cin >> n;

	vector<int> nums = vector<int>(100001);
	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		nums[num]++;
	}

	vector<int64_t> maxScores(100001, -1);
	cout << solve(nums, nums.size() - 1, maxScores) << endl;
}