#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int dfs(const vector<int>& values, const vector<vector<int>>& edges, vector<int>& parent, vector<int>& weight,
		const int current, const int prev) {
	if (parent[current] >= 0) {
		return 0;
	}
	parent[current] = prev;
	weight[current] = values[current];

	for (int tgt: edges[current]) {
		weight[current] += dfs(values, edges, parent, weight, tgt, current);
	}

	return weight[current];
}

int findMinDiff(const vector<int>& values, const vector<vector<int>>& edges) {
	// construct the spanning tree with DFS, and weigh the node subtrees
	vector<int> parent(values.size(), -1);
	vector<int> weight(values.size(), -1);
	dfs(values, edges, parent, weight, 0, 0);

	int minDiff = numeric_limits<int>::max();
	for (int i = 0; i < values.size(); ++i) {
		// let's remove the edge between vertex i and parent[i]
		minDiff = min(minDiff, abs(weight[0] - weight[i] - weight[i]));
	}
	return minDiff;
}

int main() {
	int n;
	cin >> n;

	vector<int> values(n);
	for (int i = 0; i < n; ++i) {
		cin >> values[i];
	}

	vector<vector<int>> edges(n);
	for (int i = 0; i < n - 1; ++i) {
		int v1, v2;
		cin >> v1 >> v2;
		--v1; --v2; // to 0index
		edges[v1].push_back(v2);
		edges[v2].push_back(v1);
	}

	cout << findMinDiff(values, edges) << endl;
    return 0;
}
