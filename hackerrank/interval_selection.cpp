#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

struct Interval {
	int start, end;
};

vector<vector<int>> memo;

int selectDominant(const vector<Interval>& intervals, const int idx, const int dominantIdx) {
	if (dominantIdx >= intervals.size()) {
		return idx;
	}

	if (intervals[idx].end > intervals[dominantIdx].end) {
		return idx;
	} else {
		return dominantIdx;
	}
}

int findIndexAfter(const vector<Interval>& intervals, const int sIdx, const int rangeEnd) {
	// quick way out
	if (intervals[sIdx].start > rangeEnd) {
		return sIdx;
	}

	// binary search
	int lo = sIdx;
	int hi = intervals.size() - 1;

	while (lo <= hi) {
		int mid = (lo + hi) >> 1;

		if (intervals[mid].start <= rangeEnd) {
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}

	return lo;
}

// returns the number of intervals we can select from [idx..end)
// assuming another potential dominant interval in the range
int selectIntervals(const vector<Interval>& intervals, const int idx, const int dominantIdx) {
	if (idx >= intervals.size()) {
		return 0;
	}

	if (memo[idx][dominantIdx] >= 0) {
		return memo[idx][dominantIdx];
	}

	// for each interval we can either include or not
	const Interval& current = intervals[idx];
	
	// include it and skip doubles
	// If no dominant, nothing to skip
	int skipUntilRange = min(intervals[idx].end,
		dominantIdx < intervals.size() ? intervals[dominantIdx].end : 0);
	
	int nextIdx = findIndexAfter(intervals, idx + 1, skipUntilRange);
	
	int result = 1 + selectIntervals(intervals, nextIdx, selectDominant(intervals, idx, dominantIdx));

	// do not include it
	result = max(result, selectIntervals(intervals, idx + 1, dominantIdx));

	return memo[idx][dominantIdx] = result;
}

int main() {
	int nCases;
	cin >> nCases;
	while (nCases-- > 0) {
		int n;
		cin >> n;

		vector<Interval> intervals(n);
		for (int i = 0; i < n; ++i) {
			cin >> intervals[i].start >> intervals[i].end;
		}

		sort(intervals.begin(), intervals.end(), [] (const Interval& lhs, const Interval& rhs) {
			return lhs.start < rhs.start;
		});

		memo = vector<vector<int>>(n, vector<int>(n + 1, -1));
		cout << selectIntervals(intervals, 0, intervals.size()) << endl;
	}
}