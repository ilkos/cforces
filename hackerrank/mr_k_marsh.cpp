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
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[0].size(); ++j) {
            for (int k = i + 1; k < field.size(); ++k) {
                for (int l = j + 1; l < field[0].size(); ++l) {
                    // (i,j), (k,l) are the two points
                    // constant time check to see if we can do a rectangle
                    
                    // top
                    if (l - j > horizontalLand[i][l]) {
                        continue;
                    }
                    
                    // bottom
                    if (l - j > horizontalLand[k][l]) {
                        continue;
                    }
                    
                    // left
                    if (k - i > verticalLand[k][j]) {
                        continue;
                    }
                    
                    // right
                    if (k - i > verticalLand[k][l]) {
                        continue;
                    }

                    best = max(best, 2 * (l - j) + 2 * (k - i));
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
