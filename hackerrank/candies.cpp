#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int solve(const vector<int>& ratings) {
    vector<int> assignment(ratings.size(), 1);
    
    for (int i = 1; i < ratings.size(); ++i) {
        if (ratings[i] > ratings[i - 1]) {
            assignment[i] = assignment[i - 1] + 1;
        }
    }
    
    for (int i = ratings.size() - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1]) {
            assignment[i] = max(assignment[i], assignment[i + 1] + 1);
        }
    }

    int s = 0;
    for (int n: assignment) s += n;
    return s;
}

int main() {
    int n;
    cin >> n;
    vector<int> ratings(n);
    for (int i = 0; i < n; ++i) {
        cin >> ratings[i];
    }
    
    cout << solve(ratings) << endl;
    return 0;
}
