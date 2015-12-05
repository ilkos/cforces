#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int MODULO = 1000000007;

vector<int64_t> memoPow10 = vector<int64_t>(200001, -1);
int64_t pow10Mod(const int n) {
	if (n == 0) return 1;
	if (memoPow10[n] >= 0) {
		return memoPow10[n];
	}
	return memoPow10[n] = (pow10Mod(n - 1) * 10) % MODULO;
}

vector<int64_t> memoSumPow10 = vector<int64_t>(200001, -1);
int64_t sumPow10Mod(const int n) {
	if (n == 0) return 1;

	if (memoSumPow10[n] >= 0) {
		return memoSumPow10[n];
	}
	int result = pow10Mod(n);
	return memoSumPow10[n] = (sumPow10Mod(n - 1) + result) % MODULO;
}

int64_t calcDigitImpact(int digit, int pos, int total) {
	// impact of each digit is
	// sum of i from 0 to total - pos - 1 of [(pos + 1) * digit * 10^i]
	// that is the sum of digits to the right
	int64_t result = sumPow10Mod(total - pos - 1);
	result *= digit;
	result %= MODULO;
	result *= pos + 1;
	result %= MODULO;
	return result;
}

int calculate(const string& s) {
	int64_t result = 0;
	for (int i = 0; i < s.size(); ++i) {
		result += calcDigitImpact(s[i] - '0', i, s.size());
		result %= MODULO;
	}
	return result;
}

int main() {
	string s;
	cin >> s;
	cout << calculate(s) << endl;
    return 0;
}
