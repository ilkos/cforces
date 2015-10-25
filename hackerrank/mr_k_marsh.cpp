#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int getField(int previous) {
    if (previous < 0) {
        return 0;
    }
    return previous + 1;
}

void populateHorizontal(const vector<string>& field, vector<vector<int>>& horizontal) {
    for (int i = 0; i < field.size(); ++i) {
        horizontal[i][0] = field[i][0] == '.' ? 0 : -1;

        for (int j = 1; j < field[0].size(); ++j) {
            horizontal[i][j] = field[i][j] == '.' ? getField(horizontal[i][j - 1]) : -1;
        }
    }
}

void populateVertical(const vector<string>& field, vector<vector<int>>& vertical) {
    for (int i = 0; i < field[0].size(); ++i) {
        vertical[0][i] = field[0][i] == '.' ? 0 : -1;

        for (int j = 1; j < field.size(); ++j) {
            vertical[j][i] = field[j][i] == '.' ? getField(vertical[j - 1][i]) : -1;
        }
    }
}

int solve(const vector<string>& field) {
    vector<vector<int>> horizontalLand(field.size(), vector<int>(field[0].size()));
    vector<vector<int>> verticalLand(field.size(), vector<int>(field[0].size()));
    
    populateHorizontal(field, horizontalLand);
    populateVertical(field, verticalLand);
    
    int best = 0;
    // fix the top and bottom rows
    // scanline left to right (with 2 pointers)
    for (int i = 0; i < field.size(); ++i) {
        for (int j = i + 1; j < field.size(); ++j) {
            int left = 0;
            int right = 0;

            // find valid left
            for (; left < field[0].size(); ++left) {
                if (j - i > verticalLand[j][left]) {
                    continue;
                }

                // valid left
                right = max(right, left + 1);
                for (; right < field[0].size(); ++right) {
                    if (j - i > verticalLand[j][right]) {
                        continue;
                    }

                    if (right - left <= horizontalLand[i][right] && right - left <= horizontalLand[j][right]) {
                        best = max(best, 2 * (j - i) + 2 * (right - left));
                    } else {
                        break;
                    }
                }
            }
        }
    }
    
    return best;
}

int main() {
    int m, n;
    cin >> m >> n;
    
    vector<string> field(m);
    for (int i = 0; i < m; ++i) {
        cin >> field[i];
    }
    
    int result = solve(field);
    if (result <= 0) {
        cout << "impossible" << endl;
    } else {
        cout << result << endl;
    }
    return 0;
}
