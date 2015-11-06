#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool findMatch(const string& str1, const string& str2) {
	// we do not need the largest match, so a single character will suffice
	vector<bool> chars = vector<bool>(26);
	for (char c: str1) {
		chars[c - 'a'] = true;
	}

	for (char c: str2) {
		if (chars[c - 'a']) {
			return true;
		}
	}

	return false;
}

int main() {
	int nCases;
	cin >> nCases;

	while (nCases-- > 0) {
		string a, b;
		cin >> a >> b;

		bool isFound = findMatch(a, b);
		cout << (isFound ? "YES" : "NO") << endl;
	}
    return 0;
}
