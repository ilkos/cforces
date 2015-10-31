#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void solve(const vector<uint64_t>& graph, uint64_t& sum,
           int idx = 0, uint64_t running = 0, int nComponents = 0) {
    
    if (idx >= graph.size()) {
        // 64 - nodes that are somehow connected + number of components
        sum += 64 - __builtin_popcountll(running) + nComponents;
        return;
    }
    
    // either select
    const int population = __builtin_popcountll(graph[idx]);
    if (population <= 1) {
        // does not affect the result
        solve(graph, sum, idx + 1, running, nComponents);
    } else {
        // merge
        if (running & graph[idx]) {
            // part of the same component, do not increment component count
            solve(graph, sum, idx + 1, running | graph[idx], nComponents);
        } else {
            solve(graph, sum, idx + 1, running | graph[idx], nComponents + 1);
        }
        
    }
    
    // or do not select
    solve(graph, sum, idx + 1, running, nComponents);
}

int main() {
    int n;
    cin >> n;
    vector<uint64_t> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    
    uint64_t sum = 0;
    solve(v, sum);
    
    cout << sum << endl;
    return 0;
}
