#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool findNext(const string& s, string& next) {
	next = s;

	// find rightmost character that is smaller from the one on its right
	int k = s.size() - 2;
	while (k >= 0) {
		if (next[k] < next[k + 1]) {
			break;
		}
		--k;
	}

	if (k < 0) {
		return false;
	}

	// all elements right of k are guaranteed to be in decreasing order

	// find rightmost character that is greater than next[k] (guaranteed)
	int l = s.size() - 1;
	while (l >= 0) {
		if (next[l] > next[k]) {
			break;
		}
		--l;
	}

	swap(next[k], next[l]);
	// reverse in between
	reverse(next.begin() + k + 1, next.end());
	return true;
}

int main() {
	int t;
	cin >> t;
	while (t-- > 0) {
		string s;
		cin >> s;

		string next;
		if (findNext(s, next)) {
			cout << next << endl;
		} else {
			cout << "no answer" << endl;
		}
	}
    return 0;
}
