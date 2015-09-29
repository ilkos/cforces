#include <vector>
#include <cmath>
using namespace std;

class BearSortsDiv2 {
public:
	double getProbability(const vector<int>& seq) {
		// essentially count the number of comparisons of the merge sort
		// the only thing we need to exclude is the cases where it cannot happen at all
		
		// we already know the results of the comparisons that took place by virtue of their relative positions
		indexOfSeq = vector<int>(seq.size() + 1);
		for (int i = 0; i < seq.size(); ++i) {
			indexOfSeq[seq[i]] = i;
		}
		
		vector<int> initial = vector<int>(seq.size());
		for (int i = 1; i <= initial.size(); ++i) {
			initial[i - 1] = i;
		}
		
		comparisons = 0;
		mergeSort(initial, 0, initial.size());
		
		return log(0.5) * comparisons;
	}
	
	void mergeSort(vector<int>& array, int lo, int hi) {
		if (lo + 1 >= hi) return;
		int mid = lo + (hi - lo) / 2;
		
		mergeSort(array, lo, mid);
		mergeSort(array, mid, hi);
		
		vector<int> merged = vector<int>();
		int p1 = lo;
		int p2 = mid;
		while (p1 < mid || p2 < hi) {
			if (p1 == mid) {
				merged.push_back(array[p2++]);
			} else if (p2 == hi) {
				merged.push_back(array[p1++]);
			} else {
				if (indexOfSeq[array[p1]] < indexOfSeq[array[p2]]) {
					merged.push_back(array[p1++]);
				} else {
					merged.push_back(array[p2++]);
				}
				++comparisons;
			}
		}
		
		for (int i = 0; i < hi - lo; ++i) {
			array[lo + i] = merged[i];
		}
	}
	
	vector<int> indexOfSeq;
	int comparisons;
};