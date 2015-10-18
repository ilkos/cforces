#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

char findSmallestAvailable(const string& s, int idx,
                           const map<char, int>& occurences,
                           map<char, int> discarded,
                           const map<char, int>& reqOccurences) {
    char minChar = 'z' + 1;
    for (int i = idx; i >= 0; --i) {
        if (!occurences.find(s[i])->second) continue;
        // this char is required
        
        minChar = min(minChar, s[i]);
        discarded[s[i]]++;
        if (discarded[s[i]] > reqOccurences.find(s[i])->second) {
            break;
        }
    }
    return minChar;
}

string solve(const string& s) {
    map<char, int> occurences;
    for (char c: s) {
        occurences[c]++;
    }
    
    for (auto it = occurences.begin(); it != occurences.end(); ++it) {
        it->second /= 2;
    }
    
    const map<char, int> reqOccurences = occurences;
    map<char, int> discarded;
    
    // reverse(result) must appear in the same order in s
    string result = "";
    for (int i = s.size() - 1; i >= 0; --i) {
        if (occurences[s[i]] == 0) continue;
        
        // decide whether to add s[i]
        // in order to add it, it must be the smallest available element, or we have no choice
        char smallestAvailable = findSmallestAvailable(s, i, occurences, discarded, reqOccurences);

        // skip until we reach the character required
        while (s[i] != smallestAvailable) {
            discarded[s[i]]++;
            --i;
        }

        result.push_back(s[i]);
        occurences[s[i]]--;
    }
    return result;
}

void test(const string& input, const string& expected) {
    string solution = solve(input);
    if (solution != expected) {
        cout << "FAILED:" << endl;
        cout << "Expected: " << expected << endl;
        cout << "Actual  : " << solution << endl;
    }
}

int main() {
    test("djjcddjggbiigjhfghehhbgdigjicafgjcehhfgifadihiajgciagicdahcbajjbhifjiaajigdgdfhdiijjgaiejgegbbiigida",
        "aaaaabccigicgjihidfiejfijgidgbhhehgfhjgiibggjddjjd");
}
