#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int findLucky(const vector<int>& numbers) {
    int maxLucky = 0;
    // keep a stack of open problems, and discard solutions that we will not possibly need
    stack<int> s;

    s.push(numbers[0]);
    for (int i = 1; i < numbers.size(); ++i) {
        while (!s.empty()) {
            maxLucky = max(maxLucky, numbers[i] ^ s.top());

            // numbers are guaranteed to be distinct so the equality never holds
            if (s.top() < numbers[i]) {
                s.pop();
            } else {
                break;
            } 
        }

        s.push(numbers[i]);
    }

    return maxLucky;
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    cout << findLucky(numbers) << endl;
}