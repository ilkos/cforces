#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <set>
using namespace std;

int upper_bound(const vector<int>& array, const int num) {
	int lo = 0;
	int hi = array.size() - 1;

	int ret = -1;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;

		if (array[mid] < num) {
			lo = mid + 1;
		} else {
			ret = mid;
			hi = mid - 1;
		}
	}

	return ret;
}

struct Node {
	Node() : zero(nullptr), one(nullptr) {}

	void setIncludesIndex(int idx) {
		indexes.push_back(idx);
	}

	bool hasRange(const int p, const int q) const {
		int idx = upper_bound(indexes, p);
		if (idx == -1) {
			return false;
		}
		return indexes[idx] <= q;
	}

	// indexes are guaranteed to be in order since we insert sequentially
	vector<int> indexes;
	Node* zero;
	Node* one;
};

struct Trie {
	Node* root;
	const static int MAXBIT = 15;

	Trie() : root(new Node()) {}

	void add(const uint num, const int idx) {
		Node* node = root;

		int maskBit = MAXBIT;
		while (maskBit >= 0) {
			if (num & (1 << maskBit)) {
				if (!node->one) {
					node->one = new Node();
				}
				node = node->one;
			} else {
				if (!node->zero) {
					node->zero = new Node();
				}
				node = node->zero;
			}

			node->setIncludesIndex(idx);
			--maskBit;
		}
	}

	int findMaxXor(const uint a, const int p, const int q) const {
		uint num = 0;
		Node* node = root;
		int maskBit = MAXBIT;

		while (maskBit >= 0) {
			if ((a & (1 << maskBit)) == 0) { // try to go for 1
				if (node->one != nullptr && node->one->hasRange(p, q)) {
					node = node->one;
					num |= 1;
				} else {
					// assert(node->zero->hasRange(p, q));
					node = node->zero;
				}
			} else { // try to go for 0
				if (node->zero != nullptr && node->zero->hasRange(p, q)) {
					node = node->zero;
				} else {
					// assert(node->one->hasRange(p, q));
					node = node->one;
					num |= 1;
				}
			}

			--maskBit;
			num <<= 1;
		}

		num >>= 1;
		return num ^ a;
	}
};

int main() {
	int nCases;
	scanf("%d", &nCases);
	while (nCases-- > 0) {
		int n, q;
		scanf("%d %d", &n, &q);

		Trie trie;
		for (int i = 0; i < n; ++i) {
			int num;
			scanf("%d", &num);

			trie.add(num, i);
		}

		for (int i = 0; i < q; ++i) {
			int a, p, q;
			scanf("%d %d %d", &a, &p, &q);
			printf("%d\n", trie.findMaxXor(a, p - 1, q - 1));
		}

	}
    return 0;
}
