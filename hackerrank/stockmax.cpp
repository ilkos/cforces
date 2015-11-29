#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int64_t maxProfit(const vector<int>& stockprices) {
	if (stockprices.size() < 2) {
		return 0;
	}

	// need a way to find the next right peak
	// scan right to left keeping peaks
	// peaks[i] contains the index of the greatest peak in [i..end)
	vector<int> peaks(stockprices.size());
	peaks[peaks.size() - 1] = peaks.size() - 1;
	for (int i = stockprices.size() - 2; i >= 0; --i) {
		if (stockprices[i] >= stockprices[peaks[i + 1]]) {
			peaks[i] = i;
		} else {
			peaks[i] = peaks[i + 1];
		}
	}

	int64_t profit = 0;
	int64_t owned = 0;
	for (int i = 0; i < stockprices.size(); ++i) {
		if (peaks[i] == i) {
			profit += owned * stockprices[i];
			owned = 0;
		} else { // will peak in the future
			profit -= stockprices[i];
			++owned;
		}
	}

	return profit;
}

int main() {
	int nCases;
	cin >> nCases;
	while (nCases-- > 0) {
		int n;
		cin >> n;
		vector<int> stockprices(n);
		for (int i = 0; i < n; ++i) {
			cin >> stockprices[i];
		}

		cout << maxProfit(stockprices) << endl;
	}
    return 0;
}
