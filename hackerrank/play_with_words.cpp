#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// O(n^2) DP for longest palindromic subsequence
int _longestPalindrome(const string& s, const int lo, const int hi, vector<vector<int>>& memo) {
	if (lo == hi) {
		return 1;
	} else if (lo > hi) {
		return 0;
	}

	if (memo[lo][hi] >= 0) {
		return memo[lo][hi];
	}

	int result = 0;
	if (s[lo] == s[hi]) {
		result = 2 + _longestPalindrome(s, lo + 1, hi - 1, memo);
	} else {
		result = max(_longestPalindrome(s, lo + 1, hi, memo), _longestPalindrome(s, lo, hi - 1, memo));
	}

	return memo[lo][hi] = result;
}

vector<vector<int>> memo;
int longestPalindrome(const string& s, const int lo, const int hi) {
	return _longestPalindrome(s, lo, hi, memo);
}

int main() {
	string s;
	cin >> s;

	memo = vector<vector<int>>(s.size(), vector<int>(s.size(), -1));
	int best = 0;
	for (int i = 0; i < s.size(); ++i) {
		// separator at i
		best = max(best, longestPalindrome(s, 0, i) * longestPalindrome(s, i + 1, s.size() - 1));
	}
	cout << best << endl;
    return 0;
}
