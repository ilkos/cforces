#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> coins;
vector<vector<int64_t>> dp;

uint64_t solve(int n, int lastCoinIdx = 0) {
    if (!n) {
        return 1;
    } else if (n < 0) {
        return 0;
    }

    if (dp[n][lastCoinIdx] >= 0) {
        return dp[n][lastCoinIdx];
    }

    uint64_t result = 0;

    for (int i = lastCoinIdx; i < coins.size(); ++i) {
        result += solve(n - coins[i], i);
    }

    return dp[n][lastCoinIdx] = result;
}

int main() {
    int n, m;
    cin >> n >> m;
    coins = vector<int>(m);
    for (int i = 0; i < m; ++i) {
        cin >> coins[i];
    }
    
    dp = vector<vector<int64_t>>(n + 1, vector<int64_t>(coins.size(), -1));
    cout << solve(n) << endl;
    return 0;
}
