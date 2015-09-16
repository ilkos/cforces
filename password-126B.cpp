#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const static int PRIME = 17;
const static int LARGE_PRIME = 1000000007;

bool equalStr(const string& s1, const int lo1, const string& s2, const int lo2, const size_t len) {
    for (int i = 0; i < len; ++i) {
        if (s1[lo1 + i] != s2[lo2 + i]) {
            return false;
        }
    }

    return true;
}

int64_t powMod(int64_t num, int32_t power, int64_t modulo) {
    int64_t result = 1;
    for (int i = 0; i < power; ++i) {
        result = (result * num) % modulo;
    }
    return result;
}

int rkmatch(const string& s, int len) {
    if (!len) return -1;

    // matches s[0, len) with another substring of s[]
    int64_t patternHash = 0;
    for (int i = 0; i < len; ++i) {
        patternHash *= PRIME;
        patternHash += s[i];
        patternHash %= LARGE_PRIME;
    }

    const int64_t searchedHash = patternHash;
    const int64_t lenPow = powMod(PRIME, len - 1, LARGE_PRIME);

    for (int i = len; i < s.size(); ++i) {
        patternHash -= s[i - len] * lenPow;
        patternHash *= PRIME;
        patternHash += s[i];
        patternHash %= LARGE_PRIME;

        if (patternHash < 0) patternHash += LARGE_PRIME;

        if (patternHash == searchedHash) {
            // actual string comparison
            if (equalStr(s, 0, s, i - len + 1, len)) {
                return i - len + 1;
            }
        }
    }

    return -1;
}

string solve(const string& s) {
    // initially find the largest prefix that is also a match for another substring
    // if there exist one of length l, one of l - 1 is also bound to exist -> binary search
    int lo = 0;
    int hi = s.size() - 1;

    int highestLen = 0;
    int substrMatch = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        int match = rkmatch(s, mid);

        if (match >= 0 && match + mid < s.size()) {
            lo = mid + 1;
            if (mid > highestLen) {
                highestLen = mid;
                substrMatch = match;
            }
        } else {
            hi = mid - 1;
        }
    }

    if (substrMatch < 0) {
        return string();
    }

    while (highestLen > 0) {
        bool prefixSuffixMatch = equalStr(s, 0, s, s.size() - highestLen, highestLen);
        if (prefixSuffixMatch) break;
        --highestLen;
    }

    return s.substr(0, highestLen);
}

int main() {
    string s;
    cin >> s;

    string result = solve(s);
    if (result.empty()) {
        cout << "Just a legend" << endl;
    } else {
        cout << result << endl;
    }
}