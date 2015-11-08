#include <iostream>
using namespace std;

uint32_t numBits(uint32_t num) {
	uint32_t r = 0;
	while (num) {
		++r;
		num >>= 1;
	}
	return r;
}

uint32_t divide(const uint32_t dividend, const uint32_t divisor) {
	if (divisor == 0) {
		throw exception();
	}

	if (divisor > dividend) {
		return 0;
	}

	uint32_t result = 0;
	uint32_t remaining = dividend;
	int32_t shiftLen = numBits(dividend) - numBits(divisor);

	while (remaining >= divisor) {
		result <<= 1;

		uint32_t actual = divisor << shiftLen--;
		if (actual <= remaining) {
			result |= 1;
			remaining -= actual;
		}
	}

	result <<= shiftLen + 1;
	return result;
}

int main() {
	for (int i = 0; i < 100; ++i) {
		for (int j = 1; j < 100; ++j) {
			if (divide(i, j) != i / j) {
				cout << "ERROR " << i << ' ' << j << endl;
			}
		}
	}
}