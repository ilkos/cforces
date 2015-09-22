#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;

	int maxHeight = 0, minHeight = 1000;
	int minHeightIdx, maxHeightIdx;
	for (int i = 0; i < n; ++i) {
		int height;
		cin >> height;

		if (height > maxHeight) {
			maxHeight = height;
			maxHeightIdx = i;
		}

		if (height <= minHeight) {
			minHeight = height;
			minHeightIdx = i;
		} 
	}

	int result = maxHeightIdx + (n - minHeightIdx - 1);
	if (maxHeightIdx > minHeightIdx) {
		--result;
	}

	cout << result << endl;
}