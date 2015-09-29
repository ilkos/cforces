#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

bool solve(vector<pair<int, int>>& pqList) {
	sort(pqList.begin(), pqList.end(),
		[] (const pair<int, int>& lhs, const pair<int, int>& rhs) {
			return lhs.first > rhs.first;
		});

	// elements are ordered by descending price
	int lowestQuality = numeric_limits<int>::max();
	for (const auto& p: pqList) {
		if (p.second > lowestQuality) {
			return true;
		}

		lowestQuality = min(lowestQuality, p.second);
	}

	return false;
}

int main() {
	int n;
	cin >> n;

	vector<pair<int, int>> pqList(n);
	for (int i = 0; i < n; ++i) {
		cin >> pqList[i].first >> pqList[i].second;
	}

	bool exists = solve(pqList);
	cout << (exists ? "Happy Alex" : "Poor Alex") << endl;
}