#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Graph {
    vector<vector<int>> edges;
    Graph(int nNodes) : edges(vector<vector<int>>(nNodes)) {}
    
    void addEdge(int src, int dst) {
        edges[src].push_back(dst);
        edges[dst].push_back(src);
    }
    
    const vector<int>& getEdges(int node) const {
        return edges[node];
    }
    
    int size() const {
        return edges.size();
    }
};

void solve(const Graph& g, const int spos) {
    vector<int> distances = vector<int>(g.size(), -1);
    distances[spos] = 0;
    
    queue<int> q;
    q.push(spos);
    
    while (!q.empty()) {
        int current = q.front(); q.pop();
        
        for (int tgt: g.getEdges(current)) {
            if (distances[tgt] < 0) {
                distances[tgt] = distances[current] + 6;
                q.push(tgt);
            }
        }
    }
    
    for (int i = 0; i < distances.size(); ++i) {
        if (i == spos) continue;
        cout << distances[i] << " ";
    }
    cout << endl;
}

int main() {
    int nCases;
    cin >> nCases;
    while (nCases-- > 0) {
        int nNodes, nEdges;
        cin >> nNodes >> nEdges;
        
        Graph g(nNodes);
        for (int i = 0; i < nEdges; ++i) {
            int src, dst;
            cin >> src >> dst;
            --src; --dst;
            g.addEdge(src, dst);
        }
        
        int spos;
        cin >> spos;
        --spos;
        
        solve(g, spos);
    }
    return 0;
}
