#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

// prefix sum implementation using BIT tree
struct RangeQuery {
	vector<int64_t> array;
	const int mid;
	RangeQuery(int range) : array(range), mid(range >> 1) {
	}

	int64_t countInterval(int lo, int hi) const {
		int64_t result = getValue(hi) - getValue(lo - 1);
		return result;
	}

	void addValue(int index, int val) {
		index += mid;
		while (index < array.size()) {
			array[index] += val;
			index += (index & -index);
		}
	}

	int64_t getValue(int index) const {
		index += mid;
		int64_t result = 0;
		while (index > 0) {
			result += array[index];
			index -= (index & -index);
		}
		return result;
	}	
};

int64_t dfs(const vector<vector<int>>& graph, RangeQuery& rq, const int root, const int t) {
	int64_t result = rq.countInterval(root - t, root + t);

	// add ourselves to the BIT tree
	rq.addValue(root, 1);

	for (int tgt: graph[root]) {
		result += dfs(graph, rq, tgt, t);
	}

	// remove ourselves
	rq.addValue(root, -1);

	return result;
}

int indexOf(const vector<bool>& v, const bool val) {
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] == val) return i;
	}

	assert(false);
}

int main() {
	int n, t;
	cin >> n >> t;

	vector<vector<int>> graph(n);
	vector<bool> hasParent(n);
	for (int i = 0; i < n - 1; ++i) {
		int parent, child;
		cin >> parent >> child;
		--parent; --child;
		graph[parent].push_back(child);
		hasParent[child] = true;
	}

	int root = indexOf(hasParent, false);

	RangeQuery rq(400004);
	int64_t result = dfs(graph, rq, root, t);
	cout << result << endl;
    return 0;
}
