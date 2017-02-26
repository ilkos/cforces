#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Edge {
	int v1, v2;
	int weight;
};

// Subgraph G v1 <-> v2 <-> v3
// Assume minimal subgraphs G1: (v1, v2, e12), G2: (v2, v3, e23)
// In which case d = (v1 + v2 + v3) / (e12 + e23)
// d1 = (v1 + v2) / e12, d2 = (v2 + v3) / e23
// proof by contradiction, assume G is the optimal choice
// => d > d1 && d > d2
// => e12v3 > e23v1 + e23v2 && e23v1 > e12v2 + e12v3
// => e12v3 - e23v1 > e23v2 > 0 && e12v3 - e23v1 < -e12v2 < 0
// So optimal is two nodes
double calculate(const vector<int>& vertices, const vector<Edge>& edges) {
	double optimal = 0.0;

	for (Edge edge : edges) {
		double calc =
		    (vertices[edge.v1] + vertices[edge.v2]) / (double)edge.weight;
		optimal = max(optimal, calc);
	}
	return optimal;
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<int> vertices(n);
	vector<Edge> edges(m);

	for (int i = 0; i < n; ++i) {
		cin >> vertices[i];
	}

	for (int i = 0; i < m; ++i) {
		cin >> edges[i].v1 >> edges[i].v2 >> edges[i].weight;
		edges[i].v1--;
		edges[i].v2--;
	}

	double maxDensity = calculate(vertices, edges);
	cout << setprecision(12) << fixed << maxDensity << endl;
}