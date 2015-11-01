#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int getClosestSum(const vector<int>& items, const int sum) {
	// let can[i][j] denote whether you can achieve sum j using items [0..i)
	vector<vector<bool>> can(items.size() + 1, vector<bool>(sum + 1));

	// all can[0][j] == false

	// achieve 0 with all combinations
	for (int i = 0; i < items.size() + 1; ++i) {
		can[i][0] = true;
	}

	for (int k = 1; k <= sum; ++k) {
		for (int i = 1; i < items.size() + 1; ++i) { // introduce i - 1
			can[i][k] = can[i - 1][k];

			int numItems = 1; // how many of item[i - 1]
			while (!can[i][k] && k - numItems * items[i - 1] >= 0) {
				can[i][k] = can[i][k] || can[i - 1][k - numItems * items[i - 1]];
				++numItems;
			}
		}
	}

	for (int i = sum; i >= 0; --i) {
		if (can[items.size()][i]) return i;
	}
	return -1;
}

int main() {
    int nCases;
    cin >> nCases;

    while (nCases-- > 0) {
    	int n, k;
    	cin >> n >> k;
    	vector<int> items(n);
    	for (int i = 0; i < n; ++i) {
    		cin >> items[i];
    	}

    	cout << getClosestSum(items, k) << endl;
    }
    return 0;
}
