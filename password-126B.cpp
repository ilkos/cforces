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

int64_t rkhash(const vector<int64_t>& primePowers, const vector<int64_t>& partialHashes, int lo, int hi) {
    int64_t result = partialHashes[hi];
    if (lo > 0) {
        result -= partialHashes[lo - 1];
        result %= LARGE_PRIME;
        if (result < 0) result += LARGE_PRIME;
    }

    result *= primePowers[primePowers.size() - 1 - lo];
    return result % LARGE_PRIME;
}

int rkmatch(const vector<int64_t>& primePowers, const vector<int64_t>& partialHashes,
            const string& s, int len) {
    if (!len) return -1;

    // matches s[0, len) with another substring of s[]
    const int64_t searchedHash = rkhash(primePowers, partialHashes, 0, len - 1);

    for (int i = 1; i + len < s.size(); ++i) {
        const int64_t patternHash = rkhash(primePowers, partialHashes, i, i + len - 1);

        if (patternHash == searchedHash) {
            // actual string comparison
            if (equalStr(s, 0, s, i, len)) {
                return i;
            }
        }
    }

    return -1;
}

string solve(const string& s) {
    // precalculate the powers of our prime
    auto primePowers = vector<int64_t>(s.size());
    primePowers[s.size() - 1] = 1;
    for (int i = s.size() - 2; i >= 0; --i) {
        primePowers[i] = (PRIME * primePowers[i + 1]) % LARGE_PRIME;
    }

    // precalculate the partial hashes of s
    auto partialHashes = vector<int64_t>(s.size());
    for (int i = 0; i < s.size(); ++i) {
        partialHashes[i] = (primePowers[i] * s[i]) + ((i > 0) ? partialHashes[i - 1] : 0);
        partialHashes[i] %= LARGE_PRIME;
    }

    // at this point partialHashes[s.size() - 1] is the hash of the whole string
    // our hash reference is primePowers[0]
    // (for all hashes calculated, this should be the multiplier of the 1st char)

    // initially find the largest prefix that is also a match for another substring
    // if there exist one of length l, one of l - 1 is also bound to exist -> binary search
    int lo = 1;
    int hi = s.size() - 1;

    int highestLen = 0;
    int substrMatch = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        int match = rkmatch(primePowers, partialHashes, s, mid);

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
        if (rkhash(primePowers, partialHashes, 0, highestLen - 1) ==
                rkhash(primePowers, partialHashes, s.size() - highestLen, s.size() - 1)) {
            bool prefixSuffixMatch = equalStr(s, 0, s, s.size() - highestLen, highestLen);
            if (prefixSuffixMatch) break;
        }

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