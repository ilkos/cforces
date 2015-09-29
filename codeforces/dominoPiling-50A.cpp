#include <iostream>

using namespace std;

int calc(const int m, const int n) {
	int area = m * n;
	return area / 2;
}

int main() {
	int m, n;
	cin >> m >> n;

	cout << calc(m, n) << endl;
}