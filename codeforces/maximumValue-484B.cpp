#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int searchLeBetweenIdx(int lo, int hi,
    const int leValue, const vector<int>& nums) {
  int maxSeenNum = 0;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (nums[mid] <= leValue) {
      if (nums[mid] > maxSeenNum) {
        maxSeenNum = nums[mid];
      }
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  return maxSeenNum;
}

int solve(vector<int>& nums) {
  sort(nums.begin(), nums.end());
  nums.erase(unique(nums.begin(), nums.end()), nums.end());
  // M is the max value seen
  int M = nums[nums.size() - 1];

  // precompute results for all values
  vector<int> lower_eq(2 * M + 1);
  for (int i = 1; i <= 2 * M; ++i) {
    lower_eq[i] = searchLeBetweenIdx(0, nums.size() - 1, i, nums);
  }

  int result = 0;
  for (int i = 0; i < nums.size(); ++i) { // O(n)
    // the mod sequence of nums[i] mod nums[i] + 1 .. nums[i] + n
    // is 1 .. n and loops at 2 * nums[i]
    // In nums, binary search for the maximum value between
    // nums[i] + 1 .. 2 * nums[i] - 1
    for (int k = 2; k * nums[i] <= 2 * M; ++k) {
      result = max(result, lower_eq[k * nums[i] - 1] % nums[i]);
    }
  }

  return result;
}

int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }

  cout << solve(nums) << endl;
  return 0;
}