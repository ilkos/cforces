#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

struct Task {
	int deadline;
	int numRequired;
};

bool isPossible(const vector<Task>& tasks, const int len, const int overshoot) {
	int timeReq = 0;
	for (int i = 0; i < len; ++i) {
		timeReq += tasks[i].numRequired;
		if (timeReq - tasks[i].deadline > overshoot) {
			return false;
		}
	}

	return true;
}

int calcMaxOvershoot(const vector<Task>& tasks, const int len) {
	if (!len) {
		return 0;
	}

	int lo = 0;
	int hi = 100000000; // 10^8 as a worst case of all tasks serializing

	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;

		if (isPossible(tasks, len, mid)) {
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
	}

	return lo;
}

int main() {
	int nTasks;
	cin >> nTasks;

	vector<Task> tasks(nTasks);
	for (int i = 0; i < nTasks; ++i) {
		cin >> tasks[i].deadline >> tasks[i].numRequired;
	}

	for (int i = 1; i <= nTasks; ++i) {

		// insertion sort
		int pos = i - 1;
		while (pos > 0 && tasks[pos].deadline < tasks[pos - 1].deadline) {
			swap(tasks[pos], tasks[pos - 1]);
			--pos;
		}

		cout << calcMaxOvershoot(tasks, i) << endl;
	}

    return 0;
}
