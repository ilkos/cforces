#include <vector>
using namespace std;

class ExactTreeEasy {
public:
	vector<int> getTree(int n, int m) {
		// let node 0 be the central
		// reserve the first m for leaves [1..m]
		// connect all the leaves to the central node 0
		// take the last leaf and form a chain with the rest
		vector<int> result;
		
		for (int i = 1; i <= m; ++i) {
			result.push_back(0);
			result.push_back(i);
		}
		
		for (int i = m; i < n - 1; ++i) {
			result.push_back(i);
			result.push_back(i + 1);
		}
		
		return result;
	}
};