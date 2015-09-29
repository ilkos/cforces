#include <iostream>
#include <string>
using namespace std;
bool isVowel(char c) {
	return c == 'a' || c == 'o' || c == 'y' || c == 'e' || c == 'u' || c == 'i';
}

string process(string s) {
	for (int i = 0; i < s.size(); ++i) {
		s[i] = tolower(s[i]);
	}

	string result = string();
	for (int i = 0; i < s.size(); ++i) {
		if (!isVowel(s[i])) {
			result.push_back('.');
			result.push_back(s[i]);
		}
	}

	return result;
}

int main() {
	string s;
	cin >> s;

	s = process(s);
	cout << s << endl;
}