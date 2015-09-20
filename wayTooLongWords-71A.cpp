#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

string& change(string& s) {
	if (s.size() <= 10) {
		return s;
	}

	int numDigits = s.size() - 2;
	ostringstream os;
	os << numDigits;

	s = s[0] + os.str() + s[s.size() - 1];
	return s;
}

int main() {
	int n;
	cin >> n;
	string s;

	while (n-- > 0) {
		cin >> s;
		cout << change(s) << endl;
	}
}