#include <vector>
#include <string>
#include <cmath>
using namespace std;
typedef long long ll;

class CheeseRolling {
	vector<string> wins;
	vector<vector<ll>> dp;

	struct Generator {
		Generator(int valid) : valid(valid), curr(valid), required(__builtin_popcount(valid) / 2) {
			findNext();
		}
		
		bool hasNext() {
			return curr > 0;
		}
		
		int next() {
			int toRet = curr;
			findNext();
			return toRet;
		}
		
		void findNext() {
			// find next
			for (curr = (curr - 1) & valid; curr > 0; curr = (curr - 1) & valid) {
				if (__builtin_popcount(curr) == required) break;
			}
		}
		
		const int valid;
		int curr;
		const int required;
	};

public:
	ll calc(int player, int validPlayers) {
		if (__builtin_popcount(validPlayers) == 1) {
			return 1;
		}
		
		if (dp[player][validPlayers] >= 0) {
			return dp[player][validPlayers];
		}
		// need to exploit the symmetry around the tournament distributions, 16 choose 8 ±= 12000
		ll numWays = 0;
		Generator generator(validPlayers);
		
		while (generator.hasNext()) {
			int validLeft = generator.next();
			int validRight = validPlayers & ~validLeft;
			
			if (isInSet(player, validLeft)) {
				for (int other = 0; other != wins.size(); ++other) {
					if (!beats(player, other) || !isInSet(other, validRight)) continue;
					numWays += 2 * calc(player, validLeft) * calc(other, validRight);
				}
			}
		}
		
		return dp[player][validPlayers] = numWays;
	}
	
	bool isInSet(int player, int mask) {
		return (1 << player) & mask;
	}
	
	vector<ll> waysToWin(const vector<string>& wins) {
		this->wins = wins;
		this->dp = vector<vector<ll>>(wins.size(), vector<ll>(1 << wins.size(), -1));
		
		vector<ll> result = vector<ll>(wins.size());
		for (int i = 0; i < wins.size(); ++i) {
			// let calc(i, bitmask) be the ways of player i being the winner of the round with the bitmask'ed participants
			result[i] = calc(i, (1 << wins.size()) - 1); // set all as avail
		}
		
		return result;
	}
	
private:
	inline bool beats(int player1, int player2) {
		return wins[player1][player2] == 'Y';
	}
};