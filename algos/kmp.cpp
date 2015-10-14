#include <string>
#include <vector>
#include <iostream>
using namespace std;

void printVector(const vector<int>& v) {
    for (int n: v) {
        cout << n << " ";
    }
    cout << endl;
}

void assertEquals(int expected, int actual) {
    if (expected != actual) {
        cout << "Expected:\t" << expected << endl;
        cout << "Actual:\t\t" << actual << endl;
    }
}
void assertEquals(const vector<int>& expected, const vector<int>& actual) {
    if (expected != actual) {
        cout << "Expected:\t";
        printVector(expected);

        cout << "Actual:\t\t";
        printVector(actual);
    }
}

class KMPMatcher {
private:
    const std::string _pattern;
    const std::vector<int> _failTable;

public:
    KMPMatcher(const std::string& pattern): _pattern(pattern), _failTable(buildMatchingPrefix(pattern)) {
    }

    int findPatternIn(const std::string& str) {
        int patternIdx = 0;
        int strIdx = 0; // beginning of the evaluated string

        while (strIdx + _pattern.size() < str.size()) {
            if (str[strIdx + patternIdx] == _pattern[patternIdx]) {
                ++patternIdx;

                if (patternIdx == _pattern.size()) {
                    return strIdx;
                }
            } else { // no match
                strIdx += patternIdx + 1 - _failTable[patternIdx];
                patternIdx = _failTable[patternIdx];
            }
        }

        return -1;
    }

    static std::vector<int> buildMatchingPrefix(const std::string& str) {
        // KMP failure function
        const int len = str.size();
        
        // result is the failure function
        // result[i] is the length of the greater proper suffix of str[0..i] equal to its proper prefix
        // example: "a b a b a b a d e f"
        // indexes:  0 1 2 3 4 5 6 7 8 9
        // result:   0 0 1 2 3 4 5 0 0 0
        // result[i + 1] == result[i] + 1 iff str[i + 1] == str[result[i]]
        // if str[i + 1] != str[result[i]], reuse the previously calculated overlap (i.e. result[result[i]])
        auto result = std::vector<int>(len);

        // we start with k = -1 to ensure that result[k] < k
        int k = -1;
        result[0] = k;
        for (int i = 1; i < len; ++i) {            
            while (k >= 0 && str[i] != str[k + 1]) {
                k = result[k];
            }

            if (str[i] == str[k + 1]) {
                ++k;
            }

            result[i] = k;
        }

        for (int i = 0; i < result.size(); ++i) {
            ++result[i];
        }
        return result;
    }
};

int main() {
    vector<int> matching = KMPMatcher::buildMatchingPrefix("abababadef");
    vector<int> expected = { 0, 0, 1, 2, 3, 4, 5, 0, 0, 0 };
    assertEquals(expected, matching);

    matching = KMPMatcher::buildMatchingPrefix("ababyababa");
    expected = { 0, 0, 1, 2, 0, 1, 2, 3, 4, 3};
    assertEquals(expected, matching);

    matching = KMPMatcher::buildMatchingPrefix("bba.abb");
    expected = { 0, 1, 0, 0, 0, 1, 2 };
    assertEquals(expected, matching);

    KMPMatcher matcher("abababadef");
    assertEquals(19, matcher.findPatternIn("4152345dsafgabassasabababadefewfw"));
}