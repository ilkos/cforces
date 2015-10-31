#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge {
    Edge() {}
    Edge(int src, int dst, int weight) : src(src), dst(dst), weight(weight) {}
    int src, dst, weight;
};

struct UnionFind {
    vector<int> pointers;
    
    UnionFind(int numNodes) : pointers(vector<int>(numNodes)) {
        for (int i = 0; i < numNodes; ++i) {
            pointers[i] = i;
        }
    }
    
    bool isDisjoint(int u, int v) const {
        return find(u).first != find(v).first;
    }
    
    void addEdge(int u, int v) {
        if (!isDisjoint(u, v)) {
            cout << "Not disjoint" << endl;
            throw exception();
        }
        
        pair<int, int> uRank = find(u);
        pair<int, int> vRank = find(v);
        
        if (uRank.second < vRank.second) {
            pointers[uRank.first] = vRank.first;
        } else {
            pointers[vRank.first] = uRank.first;
        }
    }
    
    pair<int, int> find(int u) const {
        int rank = 0;
        
        while (pointers[u] != u) {
            u = pointers[u];
            ++rank;
        }
        
        return make_pair(u, rank);
    }
};

int kruskalSpanningTree(const int numNodes, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [] (const Edge lhs, const Edge rhs) {
        if (lhs.weight != rhs.weight) {
            return lhs.weight < rhs.weight;
        }
        
        return lhs.src + lhs.weight + lhs.dst < rhs.src + rhs.weight + rhs.dst;
    });
    
    int sum = 0;
    UnionFind unionFind(numNodes);
    for (int i = 0; i < edges.size(); ++i) {
        if (unionFind.isDisjoint(edges[i].src, edges[i].dst)) {
            unionFind.addEdge(edges[i].src, edges[i].dst);
            sum += edges[i].weight;
        }
    }
    
    return sum;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        int src, dst, weight;
        cin >> src >> dst >> weight;
        src--; dst--;
        edges[i] = Edge(src, dst, weight);
    }
    
    cout << kruskalSpanningTree(n, edges) << endl;
    return 0;
}
