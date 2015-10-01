#include <vector>
using namespace std;

const static long MOD = 1000000007;
typedef long long ll;

class ColorfulLineGraphsDiv2 {
public:
	int countWays(int N, int K) {
		auto dp = vector<ll>(N + 1);
		dp[1] = K;
		for (int i = 2; i <= N; ++i) {
			ll edgeCombinations = (K - 1) * (i - 1);
			dp[i] = (((dp[i - 1] * K) % MOD) + // just add an additional node (which can be one of j colours) with no additional edge
				((dp[i - 1] * edgeCombinations) % MOD)) % MOD; // all possible edge combinations from that node
		}
		
		return dp[N];
	}
};