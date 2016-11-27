#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

void solve(vector<int>& towers, const int k) {
	// at each step move a cube from highest -> lowest
	int minInstability = numeric_limits<int>::max();
	vector<pair<int, int>> steps;
	while (true) {
		vector<int>::iterator minElement = min_element(towers.begin(), towers.end());
		vector<int>::iterator maxElement = max_element(towers.begin(), towers.end());
		int instability = *maxElement - *minElement;
		if (instability > minInstability) {
			// we could result in the same instability (e.g. two pairs of duplicates)
			// but never more
			throw exception();
		}
		minInstability = instability;

		if (steps.size() == k
			|| *minElement == *maxElement
			|| *minElement == *maxElement - 1) {
			break;
		}

		++(*minElement);
		--(*maxElement);
		steps.push_back(
			make_pair(maxElement - towers.begin(), minElement - towers.begin()));
	}

	cout << minInstability << " " << steps.size() << endl;
	for (int i = 0; i < steps.size(); ++i) {
		cout << steps[i].first + 1 << " " << steps[i].second + 1 << endl;
	}
}

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> towers(n);
	for (int i = 0; i < n; ++i) {
		cin >> towers[i];
	}

	solve(towers, k);
}