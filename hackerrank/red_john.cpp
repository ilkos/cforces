#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// wall is 4 * n size
// bricks are 1*4 or 4*1
vector<int> dp_ways;
int waysToCoverWall(int n) {
	if (!n) {
		return 1;
	}

	if (dp_ways[n] >= 0) return dp_ways[n];

	int result = 0;
	if (n >= 4) {
		result += waysToCoverWall(n - 4);
	}

	result += waysToCoverWall(n - 1);

	return dp_ways[n] = result;	
}

bool isPrime(int num) {
	if (num <= 1) return false;
	if (num == 2) return true;

	for (int i = 3; i <= (int) sqrt(num) + 1; ++i) {
		if (num % i == 0) {
			return false;
		}
	}

	return true;
}

int primeFactors(int num) {
	if (num <= 1) {
		return 0;
	}

	int result = 1; // 2
	for (int i = 3; i <= num; i += 2) {
		if (isPrime(i)) ++result;
	}
	return result;
}

int solve(int n) {
	dp_ways = vector<int>(n + 1, -1);
	int waysToCover = waysToCoverWall(n);

	return primeFactors(waysToCover);
}

int main() {
    int nCases;
    cin >> nCases;
    while (nCases-- > 0) {
    	int n;
    	cin >> n;
    	cout << solve(n) << endl;
    }
}
