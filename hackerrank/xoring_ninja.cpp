#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
	int nTests;
	cin >> nTests;
	while (nTests-- > 0) {
		int n;
		cin >> n;
		int allBitsSet = 0;
		for (int i = 0; i < n; ++i) {
			int number;
			cin >> number;
			allBitsSet |= number;
		}

		// total number of subsets of N elements is 2^N (for each element, we either pick it or we do not)
		// each of the bits set in any number will contribute 2^(bit + N) / 2 (times picked) = 2^(bit + N - 1)
		// to the total sum
		int64_t result = 1;
		for (int p = 0; p < n - 1; ++p) {
			result <<= 1;
			result %= 1000000007;
		}

		result = (result * allBitsSet) % 1000000007;
		cout << result << endl;
	}
    return 0;
}
