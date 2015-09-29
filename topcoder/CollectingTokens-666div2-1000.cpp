#include <vector>
#include <map>
#include <cassert>
#include <stack>
using namespace std;

struct Graph {
	Graph(int sz) : _edges(vector<vector<int>>(sz + 1)) {
	}
	
	void addEdge(int src, int dst) {
		assert(src >= 0 && src < getSize());
		assert(dst >= 0 && dst < getSize());
		
		_edges[src].push_back(dst);
		_edges[dst].push_back(src);
	}
	
	const vector<int>& getEdges(int node) const {
		return _edges[node];
	}
	
	int getSize() const {
		return _edges.size();
	}
	
private:
	vector<vector<int>> _edges;
};

class CollectingTokens {
public:
	int maxTokens(vector<int>& A, vector<int>& B, vector<int>& tokens, int L) {
		Graph g(tokens.size());
		for (int i = 0; i < A.size(); ++i) {
			g.addEdge(A[i] - 1, B[i] - 1);
		}
		
		this->edges = vector<vector<int>>(tokens.size());
		this->tokens = tokens;
		dfs(g, 0);
		
		dp = vector<vector<vector<vector<int>>>>(tokens.size(), vector<vector<vector<int>>>(tokens.size() - 1, vector<vector<int>>(L + 1, vector<int>(2, -1))));
		return tokens[0] + calculate(0, 0, L, 0);
	}
	
	// spanning tree
	void dfs(const Graph& g, int pos) {
		stack<int> s;
		vector<bool> isVisited = vector<bool>(g.getSize());
		s.push(pos);
		isVisited[pos] = true;
		
		while (!s.empty()) {
			int curr = s.top(); s.pop();
			
			for (int tgt: g.getEdges(curr)) {
				if (isVisited[tgt]) continue;
				isVisited[tgt] = true;
				edges[curr].push_back(tgt);
				s.push(tgt);
			}
		}
	}
	
	// for each of the subtrees e [0..edges[pos].size())
	// we either pick it up or we do not
	// calculateMax(pos, e) refers to the max tokens we can acquire from the e-th subtree rooted at pos
	int calculate(const int pos, const int e, const int L, const int mustReturn) {
		if (L <= 0) {
			return 0;
		}
		
		if (e == edges[pos].size()) {
			return 0;
		}
		
		
		if (dp[pos][e][L][mustReturn] >= 0) {
			return dp[pos][e][L][mustReturn];
		}
		
		int maxRet = 0;
		const int tgt = edges[pos][e];
		
		for (int steps = 0; steps <= L; ++steps) {
			if (L - steps - 2 >= 0) {
				maxRet = max(maxRet, tokens[tgt] + 
					calculate(tgt, 0, steps, 1) + // branch assigning steps, you must come back to do the rest of the steps
					calculate(pos, e + 1, L - steps - 2, mustReturn)); // calculate rest of subtrees of pos with remaining steps	- 2 (for the previous to return)
			}
			
			if (!mustReturn && L - steps - 1 >= 0) {
				maxRet = max(maxRet, tokens[tgt] +
					calculate(tgt, 0, steps, 0) +
					calculate(pos, e + 1, L - steps - 1, 1)); // -1, the previous has to enter but not return
			}
		}
		
		maxRet = max(maxRet, calculate(pos, e + 1, L, mustReturn));
		
		return dp[pos][e][L][mustReturn] = maxRet;
	}
	
	vector<vector<vector<vector<int>>>> dp;
	vector<vector<int>> edges;
	vector<int> tokens;
};