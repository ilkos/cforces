#include <iostream>
using namespace std;
int main() {
	int n;
	cin >> n;

	int x = 0;
	string op;
	while (n-- > 0) {
		cin >> op;
		if (op[0] == '+' || op[2] == '+') ++x;
		else --x;
	}

	cout << x << endl;
}