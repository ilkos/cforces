#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int countNodes(const vector<vector<int>>& edges, vector<int>& numNodes, int src, int parent) {
    int result = 1;
    for (int tgt: edges[src]) {
        if (tgt == parent) {
            continue;
        }
        
        result += countNodes(edges, numNodes, tgt, src);
    }
    
    return numNodes[src] = result;
}

// greedily remove edges
void traverse(const vector<vector<int>>& edges, const vector<int>& numNodes, int src, int parent, int& result) {
    for (int tgt: edges[src]) {
        if (tgt == parent) continue;
        
        if (numNodes[tgt] % 2 == 0) { // they can live
            ++result;
        }
        
        traverse(edges, numNodes, tgt, src, result);
    }
}

int solve(const vector<vector<int>>& edges) {
    // start from node 0 and construct spanning tree
    // keep track of number of nodes in subtree
    
    vector<int> numNodes(edges.size(), -1);
    countNodes(edges, numNodes, 0, -1);
    
    int result = 0;
    traverse(edges, numNodes, 0, -1, result);
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> edges(n);
    for (int i = 0; i < m; ++i) {
        int src, dst;
        cin >> src >> dst;
        --src;--dst;
        edges[src].push_back(dst);
        edges[dst].push_back(src);
    }
    
    cout << solve(edges) << endl;
    return 0;
}
