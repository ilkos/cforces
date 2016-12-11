#include <iostream>
#include <vector>
using namespace std;

struct Limit {
  int l, r, value;
};

bool isLimitSatisfied(const Limit limit, const vector<int>& elements) {
	int acc = 0xffffffff;
	for (int i = limit.l; i <= limit.r; ++i) {
		acc &= elements[i];
	}

	return acc == limit.value;
}

bool solve(const vector<Limit>& limits, vector<int>& elements) {
	for (auto limit : limits) {
		for (int i = limit.l; i <= limit.r; ++i) {
			elements[i] |= limit.value;
		}
	}

	// verify validity
	// this is currently n^2 and will timeout
	for (auto limit : limits) {
		if (!isLimitSatisfied(limit, elements)) return false;
	}

	return true;
}

int main() {
	int nElements, nLimits;
	cin >> nElements >> nLimits;

	vector<Limit> limits(nLimits);
	for (int i = 0; i < nLimits; ++i) {
		cin >> limits[i].l >> limits[i].r >> limits[i].value;
		--limits[i].l;
		--limits[i].r;
	}

	vector<int> elements(nElements, 0);
	bool result = solve(limits, elements);
	if (result) {
		cout << "YES" << endl;
		for (int i = 0; i < nElements; ++i) {
			cout << elements[i] << " ";
		}
		cout << endl;
	} else {
		cout << "NO" << endl;
	}
}