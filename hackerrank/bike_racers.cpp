#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <cassert>
using namespace std;

struct Point {
	int64_t x, y;
};

struct Edge {

	Edge() {}
	Edge(int dst, int capacity) : _dst(dst), _capacity(capacity), _flow(0) {}

	int dst() const {
		return _dst;
	}

	int remaining() const {
		assert(_capacity - _flow >= 0);
		return _capacity - _flow;
	}

	void addFlow(int val) {
		_flow += val;
	}

private:
	int _dst, _capacity, _flow;
};

struct Graph {

	Graph(int sz) : edges(vector<vector<Edge>>(sz)) {}

	void addEdge(int src, int dst, int weight) {
		assert(src >= 0 && src < edges.size());
		assert(dst >= 0 && dst < edges.size());
		edges[src].push_back(Edge(dst, weight));
		edges[dst].push_back(Edge(src, 0)); // 0-weight back-edge
	}

	const vector<Edge>& getEdges(int node) const {
		return edges[node];
	}

	Edge& findEdge(int src, int dst) {
		for (Edge& edge: edges[src]) {
			if (edge.dst() == dst) {
				return edge;
			}
		}

		throw new exception();
	}

	int size() const {
		return edges.size();
	}

private:
	vector<vector<Edge>> edges;
};

struct GraphAssignment {
	const int numBikers;
	const int numBikes;

	GraphAssignment(const int numBikers, const int numBikes) :
		numBikers(numBikers), numBikes(numBikes) {}

	int source() const {
		return numBikers + numBikes;
	}

	int sink() const {
		return source() + 1;
	}

	int biker(int bikerIdx) {
		return bikerIdx;
	}

	int bike(int bikeIdx) {
		return numBikers + bikeIdx;
	}
};

int getFlow(const Graph& g, const int source, const int sink, vector<int>& parent) {
	fill(parent.begin(), parent.end(), -1);

	queue<pair<int, int>> q;
	q.push(make_pair(source, numeric_limits<int>::max()));
	parent[source] = source;

	while (!q.empty()) {
		int current, flow;
		tie(current, flow) = q.front(); q.pop();

		for (Edge e: g.getEdges(current)) {
			if (parent[e.dst()] >= 0) continue;
			if (e.remaining() <= 0) continue;

			parent[e.dst()] = current;
			if (e.dst() == sink) {
				return min(flow, e.remaining());
			}

			q.push(make_pair(e.dst(), min(flow, e.remaining())));
		}
	}

	// could not reach sink
	return 0;
}

void augmentPaths(Graph& g, const int source, const int sink, const vector<int>& parent, const int flow) {
	int current = sink;

	while (parent[current] != current) {
		Edge& fwdEdge = g.findEdge(parent[current], current);
		fwdEdge.addFlow(flow);

		Edge& bckEdge = g.findEdge(current, parent[current]);
		bckEdge.addFlow(-flow);

		current = parent[current];
	}

	if (current != source) {
		throw exception();
	}
}

int computeMaxFlow(Graph& g, const int source, const int sink) {
	vector<int> parent(g.size());

	int totalFlow = 0;
	while (true) {
		int pathFlow = getFlow(g, source, sink, parent);
		if (pathFlow <= 0) {
			break;
		}

		totalFlow += pathFlow;
		augmentPaths(g, source, sink, parent, pathFlow);
	}

	return totalFlow;
}

int64_t dist(const Point lhs, const Point rhs) {
	return (int64_t) (lhs.x - rhs.x) * (lhs.x - rhs.x) + (int64_t) (lhs.y - rhs.y) * (lhs.y - rhs.y);
}

bool isPossible(const vector<Point>& bikers, const vector<Point>& bikes, const int k, const int64_t maxDist) {
	Graph g(bikers.size() + bikes.size() + 2);
	GraphAssignment vertexes = GraphAssignment(bikers.size(), bikes.size());

	for (int i = 0; i < bikers.size(); ++i) {
		g.addEdge(vertexes.source(), vertexes.biker(i), 1);
	}

	for (int i = 0; i < bikes.size(); ++i) {
		g.addEdge(vertexes.bike(i), vertexes.sink(), 1);
	}

	for (int i = 0; i < bikers.size(); ++i) {
		for (int j = 0; j < bikes.size(); ++j) {
			if (dist(bikers[i], bikes[j]) <= maxDist) {
				g.addEdge(vertexes.biker(i), vertexes.bike(j), 1);
			}
		}
	}
	int maxFlow = computeMaxFlow(g, vertexes.source(), vertexes.sink());
	return maxFlow >= k;
}

int64_t findTime(const vector<Point>& bikers, const vector<Point>& bikes, const int k) {
	// assignment problem
	// assign k bikers to bikes so as to minimise the maximum distance between a biker and a bike

	// the assignment problem can tell us if there is a valid matching, we can binary search for the time
	int64_t lo = 0;
	int64_t hi = numeric_limits<int>::max();

	while (lo <= hi) {
		int64_t mid = lo + (hi - lo) / 2;

		if (isPossible(bikers, bikes, k, mid)) {
			if (!mid || !isPossible(bikers, bikes, k, mid - 1)) {
				return mid;
			} else {
				hi = mid - 1;
			}
		} else {
			lo = mid + 1;
		}
	}

	throw exception();
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<Point> bikers(n);
	for (int i = 0; i < n; ++i) {
		cin >> bikers[i].x >> bikers[i].y;
	}

	vector<Point> bikes(m);
	for (int i = 0; i < m; ++i) {
		cin >> bikes[i].x >> bikes[i].y;
	}

	int64_t sqdist = findTime(bikers, bikes, k);
	cout << sqdist << endl;
    return 0;
}
