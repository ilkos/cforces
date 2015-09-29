#include <iostream>
#include <cmath>
using namespace std;

// there exist n * (n - 1) / 2 pairs of friends in a group
int64_t getPairs(int64_t groupSz) {
	return groupSz * (groupSz - 1) / 2;
}

int64_t getMax(int64_t n, int64_t m) {
	int64_t group1 = m - 1;
	return getPairs(n - group1);
}

// minimum number of friends when teams are smallest
int64_t getMin(int64_t n, int64_t m) {
	// try to distribute n elements in m groups in an even fashion is n / m
	// however, there will be n % m people remaining
	// we distribute them evenly among all the groups
	// so there will be groups of n / m size and of (n / m) + 1 size
	return (int64_t) (m - n % m) * getPairs(n / m) +
				(n % m) * getPairs(n / m + 1);
}

int main() {
	int n, m;
	cin >> n >> m;

	int64_t kmin = getMin(n, m);
	int64_t kmax = getMax(n, m);

	cout << kmin << " " << kmax << endl;
}