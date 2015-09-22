#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int k;
	cin >> k;
	vector<int> months(12);
	for (int i = 0; i < 12; ++i) {
		cin >> months[i];
	}

	sort(months.begin(), months.end());

	int result = 0;
	for (int i = months.size() - 1; k > 0 && i >= 0; --i) {
		k -= months[i];
		result++;
	}

	cout << (k <= 0 ? result : -1) << endl;
}