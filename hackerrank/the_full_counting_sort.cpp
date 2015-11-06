#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Element {
	int num;
	string s;
	bool isPrintable;
};

int numDigits(int num) {
	int r = 0;
	while (num) {
		num /= 10;
		++r;
	}
	return r;
}

int extractDigit(int num, const int digit) {
	for (int i = 0; i < digit; ++i) num /= 10;
	return num % 10;
}

void doSort(vector<Element>& elements, const int currentDigit, const int numDigits) {
	if (currentDigit >= numDigits) return;

	vector<int> indexes(11);
	// count
	for (Element element: elements) {
		indexes[extractDigit(element.num, currentDigit) + 1]++;
	}

	for (int i = 1; i <= 10; ++i) {
		indexes[i] += indexes[i - 1];
	}

	vector<Element> newElements = vector<Element>(elements.size());
	for (Element element: elements) {
		int digit = extractDigit(element.num, currentDigit);
		int index = indexes[digit]++;
		newElements[index] = element;
	}

	elements = newElements;
	doSort(elements, currentDigit + 1, numDigits);
}

void countSort(vector<Element>& elements) {
	// lsb counting sort is stable, if is done as a base10 sort given the constraints
	// we only need 2 levels of recursion

	// find max
	int maxNum = max_element(elements.begin(), elements.end(), [] (Element lhs, Element rhs) {
		return lhs.num < rhs.num;
	})->num;

	doSort(elements, 0, numDigits(maxNum));
}

int main() {
    int n;
    cin >> n;
    vector<Element> elements(n);
    for (int i = 0; i < n; ++i) {
    	cin >> elements[i].num >> elements[i].s;
    	elements[i].isPrintable = i >= n/2;
    }

    countSort(elements);
    for (Element element: elements) {
    	if (element.isPrintable) {
    		cout << element.s << " ";
    	} else {
    		cout << "- ";
    	}
    }
    cout << endl;
    return 0;
}
