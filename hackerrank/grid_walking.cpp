#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

class Solver {
    const static int MOD = 1000000007;
    const int totalSteps;
    const vector<int> dimensions;

    vector<vector<vector<long>>> dimensionWays;
    vector<vector<long>> nChooseK;
    vector<vector<long>> interleavedWays;

public:
    Solver(const int totalSteps, const vector<int>& dimensions) : totalSteps(totalSteps), dimensions(dimensions) {
        dimensionWays = vector<vector<vector<long>>>(dimensions.size(), vector<vector<long>>(totalSteps + 1));
        for (int i = 0; i < dimensionWays.size(); ++i) {
            for (int j = 0; j < totalSteps + 1; ++j) {
                dimensionWays[i][j] = vector<long>(dimensions[i], -1);
            }
        }

        nChooseK = vector<vector<long>>(totalSteps + 1, vector<long>(totalSteps + 1));
        for (int i = 0; i <= totalSteps; ++i) {
            nChooseK[i][0] = 1;
            nChooseK[i][i] = 1;
        }
        for (int i = 1; i <= totalSteps; ++i) {
            for (int j = 1; j <= totalSteps; ++j) {
                nChooseK[i][j] = (nChooseK[i - 1][j - 1] + nChooseK[i - 1][j]) % MOD;
            }
        }

        interleavedWays = vector<vector<long>>(dimensions.size(), vector<long>(totalSteps + 1, -1));
    }

    long getWaysInDimension(const int pos, const int dimensionIdx, const int m) {
        if (pos < 0 || pos >= dimensions[dimensionIdx]) {
            return 0;
        }

        if (!m) {
            return 1;
        }

        if (dimensionWays[dimensionIdx][m][pos] >= 0) {
            return dimensionWays[dimensionIdx][m][pos];
        }

        int result = getWaysInDimension(pos + 1, dimensionIdx, m - 1) +
                    getWaysInDimension(pos - 1, dimensionIdx, m - 1);
        result %= MOD;

        return dimensionWays[dimensionIdx][m][pos] = result;
    }

    long getInterleavedWaysUsingDimensions(const vector<int>& pos, const int dimensionIdx, const int remainingSteps) {
        // orthoganality of dimensions (there are no constraints moving either direction)
        // for each dimension we assign k steps to it, and interleave these steps with the rest
        // of the dimensions
        if (!remainingSteps) {
            return 1;
        }

        if (dimensionIdx >= dimensions.size()) {
            return 0;
        }

        if (interleavedWays[dimensionIdx][remainingSteps] >= 0) {
            return interleavedWays[dimensionIdx][remainingSteps];
        }

        long result = 0;
        for (int k = 0; k <= remainingSteps; ++k) {
            long waysToMoveInDirections = (getWaysInDimension(pos[dimensionIdx], dimensionIdx, k) *
                    getInterleavedWaysUsingDimensions(pos, dimensionIdx + 1, remainingSteps - k)) % MOD;

            // now multiply with all possible interleavings of this movement with the other ones
            result += (waysToMoveInDirections * nChooseK[remainingSteps][k]) % MOD;

            result %= MOD;
        }

        return interleavedWays[dimensionIdx][remainingSteps] = result;
    }

    long solve(const vector<int>& pos) {
        return getInterleavedWaysUsingDimensions(pos, 0, totalSteps);
    }
};

int main() {
    int nCases;
    cin >> nCases;
    
    while (nCases-- > 0) {
        int n, m;
        cin >> n >> m;
        
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            cin >> pos[i]; // 0-index
            --pos[i];
        }
        
        vector<int> dimensions(n);
        for (int i = 0; i < n; ++i) cin >> dimensions[i];
        
        Solver solver(m, dimensions);
        cout << solver.solve(pos) << endl;
    }

    
    return 0;
}
