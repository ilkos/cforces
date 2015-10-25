#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int64_t solve(const vector<int64_t>& values, const int64_t m) {
    vector<int64_t> prefixMod = vector<int64_t>(values.size());

    // modulo prefix sums
    prefixMod[0] = values[0] % m;
    for (int i = 1; i < values.size(); ++i) {
        prefixMod[i] = (prefixMod[i - 1] + values[i]) % m; 
    }
    
    // invert index modulo prefix sums
    map<int64_t, int64_t> prefixes = map<int64_t, int64_t>();
    for (int i = 0; i < prefixMod.size(); ++i) {
        prefixes[prefixMod[i]] = i;
    }
    
    // there are two cases:
    // 1. we use the prefix sum inclusive of all elements (result subarray is a proper prefix)
    // 2. subarray is not a proper prefix, subarray modulo sum is: (prefix[i] - prefix[j] + m) % m, where i > j
    //    in order for this to be maximised (i.e. better than case #1) we want
    //    prefix[j] > prefix[i] while minimising their distance
    int64_t result = 0;
    for (auto it = prefixes.begin(); it != prefixes.end(); ++it) {
        auto it2 = it; // it refers to prefix[i]
        ++it2; // next greater prefix, this is prefix[j]
        
        if (it2 != prefixes.end() && it2->second < it->second) {
            result = max(result, (it->first - it2->first + m) % m);
        }
        
        result = max(result, it->first);
    }
    
    return result;
}

int main() {
    int nCases;
    cin >> nCases;
    while (nCases-- > 0) {
        int64_t n, m;
        cin >> n >> m;
        vector<int64_t> values(n);
        for (int i = 0; i < n; ++i) cin >> values[i];
        
        cout << solve(values, m) << endl;
    }
    return 0;
}
