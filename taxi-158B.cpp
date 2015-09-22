#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int calc(vector<int>& groups) {
	int result = groups[3] + groups[4];
	groups[1] -= groups[3];

	// left to combine 1s and 2s
	result += groups[2] / 2;

	if (groups[2] % 2 == 1) {
		result++;
		groups[1] -= 2;
	}
	if (groups[1] < 0) groups[1] = 0;

	result += groups[1] / 4;
	if (groups[1] % 4 > 0) result++;

	return result;
}

int main() {
	int n;
	cin >> n;

	vector<int> groups = vector<int>(5, 0);
	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		groups[num]++;
	}

	cout << calc(groups) << endl;
}