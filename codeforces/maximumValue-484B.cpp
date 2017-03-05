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

  int result = 0;
  for (int i = 0; i < nums.size(); ++i) { // O(n)
    // the mod sequence of nums[i] mod nums[i] + 1 .. nums[i] + n
    // is 1 .. n and loops at 2 * nums[i]
    // In nums, binary search for the maximum value between
    // nums[i] + 1 .. 2 * nums[i] - 1
    for (int k = 2; k * nums[i] <= 2 * M; ++k) {
      int num = searchLeBetweenIdx(i + 1, nums.size() - 1, k * nums[i] - 1, nums);
      result = max(result, num % nums[i]);
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