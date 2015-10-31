#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

static const int INF = 1000000000;
struct Edge {
    Edge(int dst, int weight) : dst(dst), weight(weight) {}
    int dst, weight;
    
    bool operator> (const Edge other) const {
        return weight > other.weight;
    }
};

vector<int> dijkstra(const vector<vector<Edge>>& graph, const int spos) {
    vector<int> shortestPaths(graph.size(), INF);
    vector<bool> isDone(graph.size());
    
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push(Edge(spos, 0));
    
    while (!pq.empty()) { // introduce next edge with smallest overall path
        const Edge current = pq.top(); pq.pop();
        if (isDone[current.dst]) continue;
        
        isDone[current.dst] = true;
        shortestPaths[current.dst] = current.weight;
        
        // does this bring us closer to other nodes
        for (const Edge edge: graph[current.dst]) {
            if (isDone[edge.dst]) continue;
            pq.push(Edge(edge.dst, current.weight + edge.weight));
        }
    }
    
    return shortestPaths;
}

int main() {
    int nCases;
    cin >> nCases;
    while (nCases-- > 0) {
        int n, m;
        cin >> n >> m;
        vector<vector<Edge>> graph(n);
        for (int i = 0; i < m; ++i) {
            int src, dst, weight;
            cin >> src >> dst >> weight;
            --src; -- dst;
            graph[src].push_back(Edge(dst, weight));
            graph[dst].push_back(Edge(src, weight));
        }
        int spos;
        cin >> spos;
        --spos;
        
        vector<int> shortest = dijkstra(graph, spos);
        for (int i = 0; i < shortest.size(); ++i) {
            if (i != spos) {
                if (shortest[i] >= INF) cout << -1 << ' ';
                else cout << shortest[i] << ' ';
            }
        }
        cout << endl;
    }
    
    return 0;
}
