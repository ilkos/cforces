#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum Result {
	automaton, array, both, impossible
};

bool canOnlyRemove(const string& s, const string& t) {
	int tIdx = 0, sIdx = 0;
	while (sIdx < s.size()) {
		if (s[sIdx] == t[tIdx]) {
			++sIdx;
			++tIdx;
		} else {
			++sIdx;
		}
	}

	return tIdx == t.size();
}

Result solve(const string& s, const string& t) {
	if (s.size() < t.size()) {
		return Result::impossible;
	}

	vector<int> occurrences(26);
	bool hasRemovableElements = false;
	for (char c : s) occurrences[c - 'a']++;
	for (char c : t) occurrences[c - 'a']--;
	for (int i = 0; i < 26; ++i) {
		if (occurrences[i] < 0) {
			return impossible;
		}

		if (occurrences[i] > 0) {
			hasRemovableElements = true;
		}
	}
	// at this point we have all the characters required
	if (!hasRemovableElements) {
		// no characters that we can remove, just swapping will do it
		return Result::array;
	}

	// at this point, we need to remove characters and potentially swap
	return canOnlyRemove(s, t) ? Result::automaton : Result::both;
}

int main() {
	string s, t;
	cin >> s >> t;

	Result result = solve(s, t);
	if (result == Result::automaton) {
		cout << "automaton";
	} else if (result == Result::array) {
		cout << "array";
	} else if (result == Result::both) {
		cout << "both";
	} else {
		cout << "need tree";
	}
	cout << endl;
}