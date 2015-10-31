#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Edge {
    Edge(int tgt, int weight) : tgt(tgt), weight(weight) {}
    int tgt;
    int weight;
    
    bool operator> (const Edge other) const {
        return weight > other.weight;
    }
};

int minimumSpanningTree(const vector<vector<Edge>>& graph, const int spos) {
    vector<bool> isVisited(graph.size());
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push(Edge(spos, 0));
    
    int sum = 0;
    while (!pq.empty()) {
        Edge bestEdge = pq.top();
        pq.pop();
        
        if (isVisited[bestEdge.tgt]) continue;
        isVisited[bestEdge.tgt] = true;
        sum += bestEdge.weight;
        
        // add new edges
        const int pos = bestEdge.tgt;
        for (int i = 0; i < graph[pos].size(); ++i) {
            if (isVisited[graph[pos][i].tgt]) continue;
            pq.push(graph[pos][i]);
        }
    }
    
    return sum;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> edges(n);
    for (int i = 0; i < m; ++i) {
        int src, dst, weight;
        cin >> src >> dst >> weight;
        --src; --dst;
        edges[src].push_back(Edge(dst, weight));
        edges[dst].push_back(Edge(src, weight));
    }
    
    int spos;
    cin >> spos; --spos;
    cout << minimumSpanningTree(edges, spos) << endl;
    return 0;
}
