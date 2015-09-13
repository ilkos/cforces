#include <iostream>

using namespace std;

bool exists(long long num, int multiplier, int n) {
	int lo = 0;
	int hi = n;

	if (num % multiplier != 0) {
		return false;
	}

	num /= multiplier;

	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;

		if (mid == num) {
			return true;
		} else if (mid < num) {
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}

	return false;
}

long long solve(int n, long long x) {
	if (x == 1) {
		return 1;
	}

	long long cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (exists(x, i, n)) {
			++cnt;
		}
	}

	return cnt;
}

int main() {
	int n;
	long long x;
	cin >> n >> x;

	cout << solve(n, x) << endl;
}