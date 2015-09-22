#include <iostream>

using namespace std;

int calc(const int m, const int n) {
	int area = m * n;
	return area / 2;
}

int main() {
	int n;
	cin >> n;

	int cnt = 0;
	while (n--) {
		int a, b, c;
		cin >> a >> b >> c;

		cnt += ((a + b + c) > 1) ? 1 : 0;		
	}

	cout << cnt << endl;
}