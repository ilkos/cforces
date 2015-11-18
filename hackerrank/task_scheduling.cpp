#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

struct Task {
	int idx;
	int deadline;
	int numRequired;
};

// Essentially we annotate the tree nodes with lazy 'enhancements' (they never get absorbed in the tree)
// That is the range summaries that we keep adding
// We initialize to min value to ensure that bad values do not propagate to the max
struct SegmentTree {
	SegmentTree(const int len) :
		_len(len),
		_original(len, numeric_limits<int64_t>::min()) {

		// calculate the size of a full binary tree containing at least len leaf nodes
		int totalSize = 1;
		int size = 1;
		while (size < len) {
			size <<= 1;
			totalSize += size;
		}

		_tree = vector<int64_t>(totalSize, numeric_limits<int64_t>::min());
		_lazy = vector<int64_t>(totalSize, 0);
	}

	// Add value to [from, to] via the lazy vector
	// Will also propagate changes to the max values
	// O(logn)
	void addToRange(int l, int r, const int value) {
		assert(l >= 0 && l < _len);
		assert(r >= 0 && r < _len);
		assert(l <= r);
#ifdef DEBUG
		cout << "add " << l << " -> " << r << ": " << value << endl;
#endif
		add(getRoot(), 0, _len - 1, l, r, value);
	}

	// O(logn)
	void setValue(int index, const int value) {
		assert(index >= 0 && index < _len);

#ifdef DEBUG
		cout << "setValue " << index << " " << value << endl;
#endif
		_original[index] = value;
		set(getRoot(), 0, _len - 1, index, value);
	}

	int getMax() {
		return _tree[getRoot()];
	}

private:

	void add(const int root, const int nodeSpanLeft, const int nodeSpanRight,
			 const int left, const int right, const int val) {

		if (nodeSpanLeft > nodeSpanRight || nodeSpanLeft > right || nodeSpanRight < left) {
			return;
		}

		if (nodeSpanLeft >= left && nodeSpanRight <= right) { // totally covered
			_lazy[root] += val;
			recalculate(root, nodeSpanLeft == nodeSpanRight, nodeSpanLeft);
			return;
		}

		int mid = (nodeSpanLeft + nodeSpanRight) / 2;
		add(getLeftChild(root), nodeSpanLeft, mid, left, right, val);
		add(getRightChild(root), mid + 1, nodeSpanRight, left, right, val);

		// recalculate bottom -> top
		recalculate(root, nodeSpanLeft == nodeSpanRight, nodeSpanLeft);
	}

	void set(const int root, const int nodeSpanLeft, const int nodeSpanRight,
			 const int index, const int val) {
		if (nodeSpanLeft == nodeSpanRight) {
			assert(nodeSpanLeft == index);
			recalculate(root, true, index);
			return;
		}

		int mid = (nodeSpanLeft + nodeSpanRight) / 2;

		if (index <= mid) {
			set(getLeftChild(root), nodeSpanLeft, mid, index, val);
		} else {
			set(getRightChild(root), mid + 1, nodeSpanRight, index, val);
		}

		// non leaf node
		recalculate(root, false);
	}

	void recalculate(const int root, const bool isLeaf, const int originalIdx = -1) {
		if (!isLeaf) {
			assert(getRightChild(root) < _tree.size());
			_tree[root] = max(_tree[getLeftChild(root)], _tree[getRightChild(root)]) + _lazy[root];
		} else {
			assert(originalIdx >= 0 && originalIdx < _len);
			_tree[root] = _original[originalIdx] + _lazy[root];
		}

#ifdef DEBUG
		cout << "Recalculated " << root << " " << _tree[root] << " with lazy " << _lazy[root] << endl;
#endif
	}

	bool hasNode(const int node) const {
		return node < _tree.size();
	}

	static int getLeftChild(const int node) {
		return (node * 2) + 1;
	}

	static int getRightChild(const int node) {
		return getLeftChild(node) + 1;
	}

	static int getRoot() {
		return 0;
	}

	const int _len;
	vector<int64_t> _tree; // stores the max values
	vector<int64_t> _original; // stores the max values
	vector<int64_t> _lazy; // lazy addition to tree nodes, consumed when traversing bottom->top for active nodes
};

int main() {
	int nTasks;
	cin >> nTasks;

	vector<Task> tasks(nTasks);
	for (int i = 0; i < nTasks; ++i) {
		tasks[i].idx = i;
		cin >> tasks[i].deadline >> tasks[i].numRequired;
	}

	sort(tasks.begin(), tasks.end(), [] (const Task& lhs, const Task& rhs) {
		return lhs.deadline < rhs.deadline;
	});

	vector<int> indexToElement(nTasks);
	for (int i = 0; i < tasks.size(); ++i) {
		indexToElement[tasks[i].idx] = i;
	}

	SegmentTree segmentTree(nTasks);
	// anything slower than O(nlogn) is infeasible
	// so we cannot use the naive insertion-sort and update prefix tables
	for (int i = 0; i < nTasks; ++i) { // already O(n), meaning the calculation must happen in O(logn)
		const int elementIndex = indexToElement[i];

		segmentTree.setValue(elementIndex, tasks[elementIndex].numRequired - tasks[elementIndex].deadline);
		if (elementIndex + 1 <= nTasks - 1) {
			segmentTree.addToRange(elementIndex + 1, nTasks - 1, tasks[elementIndex].numRequired);
		}

		cout << (segmentTree.getMax() >= 0 ? segmentTree.getMax() : 0) << endl;
	}

    return 0;
}
