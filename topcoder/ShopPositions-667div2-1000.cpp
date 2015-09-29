#include <vector>
#include <limits>
#include <cstring>
using namespace std;

class ShopPositions {
public:
	
	int maxProfit(int n, int m, const vector<int>& c) {
		this->n = n;
		this->m = m;
		this->c = c;
		
		return solve();
	}
	
	int solve() const {
		// let dp[i][j][k] mean the maximum profit in buildings 0..i, with exactly j taco shops in the building i and exactly k shops from building i + 1
		int dp[n][m + 1][m + 1];
		memset(dp, 0, sizeof(dp));
		
		int result = 0;
		
		// populate the first
		for (int i = 0; i <= m; ++i) {
			for (int j = 0; j <= m; ++j) {
				dp[0][i][j] = i * getProfit(0, i + j);
			}
			result = max(result, dp[0][i][0]);
		}
		
		for (int i = 1; i < n; ++i) { // current building
			for (int j = 0; j <= m; ++j) { // how many tacos in this building
				for (int k = 0; k <= m; ++k) { // how many tacos in the prev building
					for (int l = 0; l <= m; ++l) { // fwd building
						dp[i][j][l] = max(dp[i][j][l], dp[i - 1][k][j] + j * getProfit(i, j + k + l));
						result = max(result, dp[i][j][l]);
					}
				}
			}
		}
		
		return result;
	}
	
	int getProfit(int x, int y) const {
		return c[x * 3 * m + y - 1];
	}

private:
	int n;
	int m;
	vector<int> c;
};