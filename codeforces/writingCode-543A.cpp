#include <iostream>
#include <map>
#include <vector>
using namespace std;

// this is n^3
// do n^2 by only using nlines and nbugs (how to count distinct using all developers?)
vector<map<pair<int, int>, int>> memo;
int solve(const vector<int>& bugsPerLine,
	const int modulo,
	const int nLines,
	const int nBugs,
	const int pIdx) {
  if (nBugs < 0) { // out of bug quota
  	return 0;
  }
  if (nLines == 0) {
  	return 1;
  }
  if (pIdx == bugsPerLine.size() || nBugs == 0) {
  	return 0;
  }

  map<pair<int, int>, int>::const_iterator iter =
      memo[pIdx].find(make_pair(nLines, nBugs));
  if (iter != memo[pIdx].end()) {
  	return iter->second;
  }

  return memo[pIdx][make_pair(nLines, nBugs)] =
      (solve(bugsPerLine, modulo, nLines - 1, nBugs - bugsPerLine[pIdx], pIdx)
      	+ solve(bugsPerLine, modulo, nLines, nBugs, pIdx + 1)) % modulo;
}

int main() {
	int nProgrammers, nLines, nBugs, modulo;
	cin >> nProgrammers >> nLines >> nBugs >> modulo;

	memo = vector<map<pair<int, int>, int>>(nProgrammers);
	vector<int> bugsPerLine(nProgrammers);
	for (int i = 0; i < nProgrammers; ++i) {
		cin >> bugsPerLine[i];
	}

	cout << solve(bugsPerLine, modulo, nLines, nBugs, 0) << endl;
}