#include <iostream>
#include <vector>
using namespace std;

int getLength(pair<int, int> indexes) {
  return indexes.second - indexes.first;
}

int getMaximumLength(pair<int, int> indexes, int totalSize) {
  int r = getLength(indexes);
  if (indexes.first > 0 || indexes.second < totalSize) {
    ++r;
  }
  return r;
}

int solve(const vector<int>& nums) {
  // seqs is a list of indexes in the form of [start, end) of strictly
  // increasing sequences
  vector<pair<int, int>> seqs;

  int startIndex = 0;
  for (int i = 0; i < nums.size(); ++i) {
    if (i != 0 && nums[i] <= nums[i - 1]) {
      seqs.push_back(make_pair(startIndex, i));
      startIndex = i;
    }
  }
  seqs.push_back(make_pair(startIndex, nums.size()));

  int maxLength = getMaximumLength(seqs[0], nums.size());
  for (int i = 1; i < seqs.size(); ++i) {
    maxLength = max(maxLength, getMaximumLength(seqs[i], nums.size()));

    // by definition the boundaries are aligned, and since these
    // are not a single group, it means that the first element of rhs
    // is incompatible
    // at this point, either skip the last element of lhs, or the first of rhs

    // skip first rhs element
    int lhsEnd = seqs[i].first - 1;
    int rhsStart = seqs[i].first + 1;
    if (rhsStart < nums.size() && nums[rhsStart] - nums[lhsEnd] > 1) {
      // special case is rhs having length of 1, meaning we are joining with the
      // *next* group
      int nextLen = getLength(seqs[i]) == 1 && i + 1 < seqs.size()
          ? getLength(seqs[i + 1]) + 1
          : getLength(seqs[i]);
      maxLength = max(maxLength, getLength(seqs[i - 1]) + nextLen);
    }

    // skip last lhs element
    --lhsEnd;
    --rhsStart;
    if (lhsEnd >= 0 && nums[rhsStart] - nums[lhsEnd] > 1) {
      maxLength = max(maxLength, getLength(seqs[i - 1]) + getLength(seqs[i]));
    }
  }
  return maxLength;
}

int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }

  cout << solve(nums) << endl;
}