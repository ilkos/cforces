#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;
	int cnt = 0;
	int req = 0;
	while (n-- > 0) {
		int a, b;
		cin >> a >> b;
		cnt -= a;
		cnt += b;
		req = max(req, cnt);
	}

	cout << req << endl;
}