#include <iostream>
#include <vector>
#include <map>
using namespace std;

int solve(const map<int, int>& badges) {
	int result = 0;
	int carry = 0;
	for (auto it = badges.begin(); it != badges.end(); ++it) {
		int totalExtra = it->second + carry - 1;
		if (totalExtra) {
			auto nextIt = it; ++nextIt;
			if (nextIt == badges.end()) { // last element
				result += totalExtra * (totalExtra + 1) / 2;
				carry = 0;
			} else {
				int dist = nextIt->first - it->first;
				int elementsAllocated = min(dist - 1, totalExtra);

				result += elementsAllocated * (elementsAllocated + 1) / 2;
				result += (totalExtra - elementsAllocated) * dist;

				carry = totalExtra - dist + 1;
				if (carry < 0) carry = 0;
			}
		}
	}

	return result;
}

int main() {
	int n;
	cin >> n;

	map<int, int> badges = map<int, int>();
	for (int i = 0; i < n; ++i) {
		int val;
		cin >> val;
		badges[val]++;
	}

	cout << solve(badges) << endl;
}