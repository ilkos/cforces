#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

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
// assume that the probability of getting 1 problem by asking x is better than the one for x and y:
// Px > P(x + y)
// Translated to Px > Px * (1 - Py) + (1 - Px) * Py
// Let's try to add Pz in the mix (mult by (1 - Pz)):
// Px * (1 - Pz) > Px * (1 - Py) * (1 - Pz) + (1 - Px) * Py * (1 - Pz)
// add (1 - Px) * Pz:
// Px * (1 - Pz) + (1 - Px) * Pz > Px * (1 - Py) * (1 - Pz) + (1 - Px) * Py * (1 - Pz) + (1 - Px) * Pz
// All terms are positive, and (1 - Py) <= 1, so (1 - Px) * Pz >= (1 - Px) * (1 - Py) * Pz
// Therefore:
// Px * (1 - Pz) + (1 - Px) * Pz > Px * (1 - Py) * (1 - Pz) + (1 - Px) * Py * (1 - Pz) + (1 - Px) * (1 - Py) * Pz
// P(x + z) > P(x + y + z)
// Therefore it is always redundant to add a term that does not benefit us.
double calc(const vector<double>& pList, vector<bool>& consumed, const CondProbability current) {
	int best = -1;
	double bestResult = current.getProbability();

	for (int i = 0; i < pList.size(); ++i) {
		if (consumed[i]) continue;
		consumed[i] = true;
		CondProbability with = current.addConditional(pList[i]);
		if (with.getProbability() > bestResult) {
			bestResult = with.getProbability();
			best = i;
		}
		consumed[i] = false;
	}

	if (best < 0) {
		return bestResult;
	} else {
		consumed[best] = true;
		return calc(pList, consumed, current.addConditional(pList[best]));
	}
}

int main() {
	int n;
	cin >> n;
	vector<double> prob(n);
	for (int i = 0; i < n; ++i) {
		cin >> prob[i];
	}
	vector<bool> consumed(n);
	cout << setprecision(12) << calc(prob, consumed, CondProbability()) << endl;
}