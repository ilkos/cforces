#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int calculate(string str) {
        return calc(str, 0);
    }
    
    // will return sexpr result, and set nextIndex
    int calc(const string& str, const int spos, int* nextIndex = 0) {
        int result = 0;

        int idx = spos;
        char op = '+';

        while (idx < str.size()) {
            if (isdigit(str[idx])) {
                int next = numTok(str, idx);
                result += op == '+' ? next : -next;
            } else if (str[idx] == '+' || str[idx] == '-') {
                op = str[idx++];
            } else if (str[idx] == ')') {
                break;
            } else if (isspace(str[idx])) {
                ++idx;
            } else if (str[idx] == '(') {
                int next = calc(str, idx + 1, &idx);
                result += op == '+' ? next : -next;
            }
        }

        if (nextIndex) *nextIndex = idx + 1;

        return result;
    }

    // will advance idx to end of token
    int numTok(const string& str, int& idx) {
        int num = 0;
        while (isdigit(str[idx])) {
            num *= 10;
            num += str[idx++] - '0';
        }
        return num;
    }
};

int main() {
    Solution s;
    cout << s.calculate("(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))") << endl;
    cout << s.calculate("   (  3 ) ") << endl;
}