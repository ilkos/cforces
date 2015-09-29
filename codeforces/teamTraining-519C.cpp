#include <iostream>

using namespace std;

int solve(int n, int m) {
	int result = 0;

	while (n && m && n + m >= 3) {
		// more experienced, go for NNM
		if (n > m) {
			result++;
			n -= 2;
			m--;
		} else { // more newbies, go for NMM
			result++;
			n--;
			m -= 2;
		}
	}

	return result;
}

int main() {
	int n, m;
	cin >> n >> m;

	int solution = solve(n, m);
	cout << solution << endl;
}