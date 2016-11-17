#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct CondProbability {
	CondProbability() : probability(0.0), inverse(1.0) {}
	CondProbability addConditional(double p) const {
		CondProbability result = CondProbability();
		result.probability = probability * (1.0 - p) + inverse * p;
		result.inverse = inverse * (1.0 - p);
		return result;
	}

	double getProbability() const {
		return probability;
	}
private:
	double probability;
	double inverse;
};

// never add another probability in the mix unless it results in a better result.
double calc(const vector<double>& pList, const CondProbability current, const int index) {
	if (index >= pList.size()) {
		return current.getProbability();
	}

	double result = calc(pList, current, index + 1); // skip current

	CondProbability with = current.addConditional(pList[index]);
	if (with.getProbability() > current.getProbability()) {
		result = max(result, calc(pList, with, index + 1));
	}

	return result;
}

int main() {
	int n;
	cin >> n;
	vector<double> prob(n);
	for (int i = 0; i < n; ++i) {
		cin >> prob[i];
	}

	cout << setprecision(12) << calc(prob, CondProbability(), 0) << endl;
}