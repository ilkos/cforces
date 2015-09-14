#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Graph {
public:
	Graph(size_t nVertices) :
		_edges(vector<vector<int>>(nVertices)),
		_degrees(vector<int>(nVertices, 0)) {}

	void addEdge(uint32_t from, uint32_t to, bool isDirected = false) {
		_edges[from].push_back(to);
		_degrees[from]++;

		if (!isDirected) {
			_edges[to].push_back(from);
			_degrees[to]++;
		}
	}

	const vector<int>& getEdges(uint32_t vertex) const {
		return _edges[vertex];
	}

	int getDegree(uint32_t vertex) const {
		return _degrees[vertex];
	}

	size_t size() const {
		return _edges.size();
	}

private:
	vector<vector<int>> _edges;
	vector<int> _degrees;
};

int solvePivot(const Graph& g, const uint32_t src, vector<bool>& isVisited) {
	fill(isVisited.begin(), isVisited.end(), false);
	isVisited[src] = true;
	queue<pair<int, int>> q;
	q.push(make_pair(src, 0));

	int result = -1;
	while (!q.empty()) {
		const pair<int, int> curr = q.front(); q.pop();

		const auto& edges = g.getEdges(curr.first);
		for (int tgt: edges) {
			if (src == tgt) continue;
			
			if (isVisited[tgt]) { // found!
				int sum = g.getDegree(src) + g.getDegree(curr.first) + g.getDegree(tgt);
				if (result == -1) result = sum;
				result = min(result, sum);
				continue;
			}

			if (curr.second >= 1) continue;

			q.push(make_pair(tgt, curr.second + 1));
			isVisited[tgt] = true;
		}
	}

	return result;
}

int solve(const Graph& g) {
	int result = -1;
	vector<bool> isVisited = vector<bool>(g.size());
	for (uint32_t node = 0; node < g.size(); ++node) {
		int nodeResult = solvePivot(g, node, isVisited);

		if (nodeResult > 0) {
			if (result == -1) result = nodeResult;
			result = min(result, nodeResult);
		}
	}

	return result == -1 ? -1 : result - 6;
}

int main() {
	int n, m;
	cin >> n >> m;

	Graph g = Graph(n);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		a--; b--;

		g.addEdge(a, b);
	}

	cout << solve(g) << endl;
}