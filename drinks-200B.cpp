#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
using namespace std;

double calc(vector<int>& fractions) {
	int sum = accumulate(fractions.begin(), fractions.end(), 0);
	int total = fractions.size();

	return ((double) sum / total);
}

int main() {
	int n;
	cin >> n;

	vector<int> fractions(n);
	for (int i = 0; i < n; ++i) {
		cin >> fractions[i];
	}

	cout << setprecision(12) << fixed << calc(fractions) << endl;
}