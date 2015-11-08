#include <vector>
#include <exception>
#include <algorithm>
#include <iostream>

template <typename T>
struct MinHeap {
	MinHeap() {}

	void add(const T& element) {
		elements.push_back(element);

		int idx = elements.size() - 1;
		bubbleUp(idx);
	}

	T& top() {
		if (elements.empty()) {
			throw std::exception();
		}

		return elements[0];
	}

	void pop() {
		std::swap(elements[elements.size() - 1], elements[0]);
		elements.resize(elements.size() - 1);
		bubbleDown(0);
	}

	int size() const {
		return elements.size();
	}


private:

	void bubbleUp(int idx) {
		if (idx == 0) {
			return;
		}

		int parent = getParent(idx);
		if (elements[parent] > elements[idx]) {
			std::swap(elements[parent], elements[idx]);
			bubbleUp(parent);
		}
	}

	void bubbleDown(int idx) {
		if (isLeaf(idx)) {
			return;
		}

		int leftChildIdx = getLeftChild(idx);
		int rightChildIdx = getRightChild(idx);

		int dominantIdx = leftChildIdx;
		// select dominant
		if (rightChildIdx < elements.size()) {
			dominantIdx = elements[leftChildIdx] < elements[rightChildIdx] ? leftChildIdx : rightChildIdx;
		}

		if (elements[idx] > elements[dominantIdx]) {
			std::swap(elements[idx], elements[dominantIdx]);
			bubbleDown(dominantIdx);
		}
	}

	bool isLeaf(int idx) const {
		return getLeftChild(idx) >= elements.size();
	}

	static int getParent(int idx) {
		return (idx - 1) / 2;
	}

	static int getLeftChild(int idx) {
		return (1 + idx) * 2 - 1;
	}

	static int getRightChild(int idx) {
		return getLeftChild(idx) + 1;
	}

	std::vector<T> elements;
};


int main(void) {
	using namespace std;

	MinHeap<int> pq;

	for (int i = 10; i >= 0; --i) {
		pq.add(i);
	}

	while (pq.size() > 0) {
		cout << pq.top() << ' ';
		pq.pop();
	}
}