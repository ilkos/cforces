#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

template <typename T>
struct RangeStore {
	vector<T> values;
	const int rangeLo;
	const int rangeHi;

	RangeStore(const int rangeLo, const int rangeHi) : rangeLo(rangeLo), rangeHi(rangeHi) {
		int total = rangeHi - rangeLo + 1;
		values = vector<T>(total);
	}

	const T operator[] (int rangeIndex) const {
		if (rangeIndex < rangeLo) {
			rangeIndex = rangeLo;
		} else if (rangeIndex > rangeHi) {
			rangeIndex = rangeHi;
		}

		return const_cast<RangeStore<T>*>(this)->operator[](rangeIndex);
	}

	T& operator[] (int rangeIndex) {
		assert(rangeIndex >= rangeLo);
		assert(rangeIndex <= rangeHi);
		return values[rangeIndex - rangeLo];
	}
};

// return the sum on the absolute value
// should wrap the prefix sums into an object that can calculate interval sums
int64_t calcSum(const RangeStore<int>& freqPrefixSums,
				 const RangeStore<int64_t>& negPrefixSums,
				 const RangeStore<int64_t>& posPrefixSums,
				 const int64_t query) {

	int64_t sum = 0;
	if (query > 0) {
		// negative numbers <= -query
		sum = -negPrefixSums[-query] - freqPrefixSums[-query] * query;

		// positive numbers
		sum += posPrefixSums[2000] + (freqPrefixSums[2000] - freqPrefixSums[-1]) * query;
		
		// negative numbers that will switch sign
		sum += (negPrefixSums[-1] - negPrefixSums[-query]) +
				query * (freqPrefixSums[-1] - freqPrefixSums[-query]);

	} else if (query < 0) {
		// positive numbers >= -query
		sum = (posPrefixSums[2000] - posPrefixSums[-query - 1]) + (freqPrefixSums[2000] - freqPrefixSums[-query - 1]) * query;
		
		// negative numbers
		sum += -negPrefixSums[-1] + freqPrefixSums[-1] * (-query);

		// positive numbers that will switch sign
		sum += abs(posPrefixSums[-query - 1] + query * (freqPrefixSums[-query - 1] - freqPrefixSums[-1]));

	} else { // 0 displacement - 0 sum
		sum = -negPrefixSums[0] + posPrefixSums[2000];
	}

	return sum;
}

int main() {
	int n;
	scanf("%d", &n);

	// Counting sort
	RangeStore<int> freqTable(-2000, 2000);
	for (int i = 0; i < n; ++i) {
		int num;
		scanf("%d", &num);
		freqTable[num]++;
	}

	// numbers when being displaced by +X
	// -oo ..... -X ...... 0 ...... X ...... +oo
	// all negative numbers <= -X result in smaller abs values
	// all negative numbers > -X will become positive
	// ---> with total of sum(num[i] + X) = sum(num[i]) + X*numbers in range 
	// all positive numbers result in greater abs values

	// calculate freq sums (for amount of values in range)
	RangeStore<int> freqPrefixSums(-2001, 2000);
	for (int i = -2000; i <= 2000; ++i) {
		freqPrefixSums[i] = freqPrefixSums[i - 1] + freqTable[i];
	}

	// calculate prefix sums
	RangeStore<int64_t> negPrefixSums(-2001, 0);
	for (int i = -2000; i <= 0; ++i) {
		negPrefixSums[i] = negPrefixSums[i - 1] + i * freqTable[i];
	}

	RangeStore<int64_t> posPrefixSums(0, 2000);
	for (int i = 1; i <= 2000; ++i) {
		posPrefixSums[i] = posPrefixSums[i - 1] + i * freqTable[i];
	}

	int cumulative = 0;
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; ++i) {
		int displacement;
		scanf("%d", &displacement);
		cumulative += displacement;

		// O(1) return displaced sum
		printf("%lld\n", calcSum(freqPrefixSums, negPrefixSums, posPrefixSums, cumulative));
	}
    return 0;
}
