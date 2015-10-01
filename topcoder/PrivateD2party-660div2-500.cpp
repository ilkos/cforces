#include <vector>
using namespace std;

class PrivateD2party {
public:
	int getsz(const vector<int>& a) {
		vector<bool> isVisited(a.size(), false);
		// for all dislikes forming cycles reduce by one
		int res = 0;
		
		for (int i = 0; i < a.size(); ++i) {
			if (isVisited[i]) continue;
			
			if (a[i] == i) {
				++res;
				isVisited[i] = true;
			} else {
				int cycleMembers = countCycleMembers(a, i, isVisited);
				if (cycleMembers < 0) {
					++res;
				} else {
					res += cycleMembers - 1;
				}
			}
		}
		return res;
	}
	
	int countCycleMembers(const vector<int>& a, const int src, vector<bool>& isVisited) {
		int cycleMembers = 1;
		
		auto nVisited = isVisited;
		
		int pos = src;		
		vector<bool> currVisited(a.size(), false);
		currVisited[pos] = true;
		
		while (true) {
			pos = a[pos];
			if (pos == src) break;
			if (currVisited[pos]) return -1;
			nVisited[pos] = true;
			currVisited[pos] = true;
			++cycleMembers;
		}
		
		isVisited = nVisited;
		return cycleMembers;
	}
};