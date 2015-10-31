#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int quick_pow10(int n)
{
    static int pow10[10] = {
        1, 10, 100, 1000, 10000, 
        100000, 1000000, 10000000, 100000000, 1000000000
    };

    return pow10[n]; 
}

struct Parents {
	const static int MAXSZ = 100001;
	vector<vector<int>> parents;

	Parents(const int pow10) {
		if (pow10 < 1) {
			throw exception();
		}
		parents = vector<vector<int>>(pow10, vector<int>(MAXSZ, -1));
	}

	void addInit(int node, int parent) {
		parents[0][node] = parent;
	}

	void calc() {
		// calc each next power
		int p = 10;
		for (int i = 1; i < parents.size(); ++i, p *= 10) {
			for (int node = 0; node < MAXSZ; ++node) {
				parents[i][node] = getParent(parents[0][node], p - 1, i - 1);
			}
		}
	}

	void addLeaf(const int node, const int parent) {
		parents[0][node] = parent;

		int ancestor = 10;
		for (int i = 1; i < parents.size(); ++i) {
			parents[i][node] = getParent(parent, ancestor - 1);
			ancestor *= 10;
		}
	}

	void remove(const int node) {
		for (int i = 0; i < parents.size(); ++i) {
			parents[i][node] = -1;
		}
	}

	int getParent(const int node, const int k) const {
		return getParent(node, k, parents.size() - 1);
	}

	// active is the inclusive index of 10pow that is ready to go
	int getParent(int node, int k, int active) const {
		int p = quick_pow10(active);
		
		while (node > 0 && k > 0) {
			while (p > k) {
				--active;
				p = quick_pow10(active);
			}

			if (k >= p) {
				node = parents[active][node];
				k -= p;
			}
		}

		if (node <= 0) {
			return 0;
		}
		if (!k) return node;

		cout << "Unexpected" << endl;
		throw exception();
	}
};

int main() {
	int nCases;
	cin >> nCases;

	while (nCases-- > 0) {
		int p;
		cin >> p;

		Parents parents(5);

		for (int i = 0; i < p; ++i) {
			int x, y;
			cin >> x >> y;
			parents.addInit(x, y);
		}

		parents.calc();

		int q;
		cin >> q;
		for (int i = 0; i < q; ++i) {
			int cmd;
			cin >> cmd;

			if (cmd == 0) {
				int y, x;
				cin >> y >> x;
				parents.addLeaf(x, y);
			} else if (cmd == 1) {
				int x;
				cin >> x;
				parents.remove(x);
			} else {
				int x, k;
				cin >> x >> k;
				cout << parents.getParent(x, k) << endl;
			}
		}
	}
    return 0;
}
