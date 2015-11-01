#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<vector<int64_t>>> memo;

vector<int64_t> getMaxScore(const vector<int64_t>& bricks, const bool turn, const int top) {
	if (top >= bricks.size()) {
		return vector<int64_t>(2, 0);
	}

	if (!memo[top][turn].empty()) {
		return memo[top][turn];
	}

	vector<int64_t> best = vector<int64_t>(2, 0);
	vector<int64_t> score = vector<int64_t>(2, 0);

	for (int i = min(3, (int) bricks.size() - top); i >= 1; --i) {
		score[0] = score[1] = 0;

		for (int j = 0; j < i; ++j) {
			score[turn] += bricks[top + j];
		}
		vector<int64_t> rscore = getMaxScore(bricks, !turn, top + i);

		score[0] += rscore[0];
		score[1] += rscore[1];

		if (score[turn] > best[turn]) {
			best = score;
		}
	}

	return memo[top][turn] = best;
}

int main() {
    int nCases;
    cin >> nCases;

    while (nCases-- > 0) {
    	int n;
    	cin >> n;
    	vector<int64_t> bricks(n);
    	for (int i = 0; i < n; ++i) {
    		cin >> bricks[i];
    	}

    	memo = vector<vector<vector<int64_t>>>(bricks.size(), vector<vector<int64_t>>(2));
    	cout << getMaxScore(bricks, 0, 0)[0] << endl;
    } 
    return 0;
}
