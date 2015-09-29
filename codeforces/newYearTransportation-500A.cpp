#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool isPossible(const vector<int>& jmp, const int dst) {
	vector<bool> isVisited(jmp.size(), false);

	int pos = 0;
	while (!isVisited[pos]) {
		if (pos == dst) return true;
		isVisited[pos] = true;
		pos = pos + jmp[pos];
	}
	return false;
}

int main() {
	int n, t;
	cin >> n >> t;

	vector<int> jmp = vector<int>(n);
	for (int i = 0; i < n - 1; ++i) {
		cin >> jmp[i];
	}

	cout << (isPossible(jmp, t - 1) ? "YES" : "NO") << endl;
}