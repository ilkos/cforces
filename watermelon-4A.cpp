#include <iostream>

using namespace std;

int main() {
	int w;
	cin >> w;

	bool result = w != 2 && (w % 2 == 0);
	cout << (result ? "YES" : "NO") << endl;
}
