#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Range {
  Range() : l(-1), r(-1) {}
  Range(int l, int r) : l(l), r(r) {}

  bool overlaps(int start, int end) const {
    return l <= end && start <= r;
  }

  bool fullyCovers(int start, int end) const {
    return start >= l && end <= r;
  }

  int l, r;
};

struct Limit : public Range {
  int value;
};

class OrSegmentTree {
public:
  OrSegmentTree(int nElements) {
    int elementsCovered = 1;
    tree_.emplace_back(elementsCovered, 0);
    while (elementsCovered < nElements) {
      elementsCovered *= 2;
      tree_.emplace_back(elementsCovered, 0);
    }

    depth_ = tree_.size();
    elementsCovered_ = elementsCovered;
  }

  void orRange(Range range, int value) {
    applyOr(range, value, 0, 0, 0, elementsCovered_ - 1);
  }

  int getElementAt(size_t index) const {
    int level = depth_ - 1;
    int result = 0;
    while (level >= 0) {
      result |= tree_[level][index];
      --level;
      index /= 2;
    }
    return result;
  }

private:
  void applyOr(const Range range, const int value, const int lvl, const int idx,
               const int start, const int end) {
    if (!range.overlaps(start, end)) {
      return;
    }

    if (range.fullyCovers(start, end)) {
      tree_[lvl][idx] |= value;
      return;
    }

    int mid = start + (end - start) / 2;
    applyOr(range, value, lvl + 1, idx * 2, start, mid);
    applyOr(range, value, lvl + 1, idx * 2 + 1, mid + 1, end);
  }

  int depth_;
  int elementsCovered_;
  vector<vector<int>> tree_;
};

class RangeAndTree {
public:
  RangeAndTree(const vector<int>& values) {
    int elementsCovered = 1;
    tree_.emplace_back(elementsCovered, NOT_CALCULATED);
    while (elementsCovered < values.size()) {
      elementsCovered *= 2;
      tree_.emplace_back(elementsCovered, NOT_CALCULATED);
    }

    depth_ = tree_.size();
    elementsCovered_ = elementsCovered;
    copy(values.begin(), values.end(), tree_[depth_ - 1].begin());
  }

  int andRange(const Range range) const {
    return doAndRange(range, 0, 0, 0, elementsCovered_ - 1);
  }

private:
  int doAndRange(const Range range, const int lvl, const int idx,
                 const int start, const int end) const {
    if (!range.overlaps(start, end)) {
      return 0xffffffff;
    }

    if (range.fullyCovers(start, end) && tree_[lvl][idx] != NOT_CALCULATED) {
      return tree_[lvl][idx];
    }

    int mid = start + (end - start) / 2;
    int result = doAndRange(range, lvl + 1, idx * 2, start, mid)
        & doAndRange(range, lvl + 1, idx * 2 + 1, mid + 1, end);

    if (range.fullyCovers(start, end)) {
      tree_[lvl][idx] = result;
    }
    return result;
  }

  const int NOT_CALCULATED = -1;
  int depth_;
  int elementsCovered_;
  mutable vector<vector<int>> tree_;
};

bool solve(const vector<Limit>& limits, vector<int>& elements) {
  OrSegmentTree segmentTree(elements.size());
  for (auto limit : limits) {
    segmentTree.orRange(limit, limit.value);
  }

  for (int i = 0; i < elements.size(); ++i) {
    elements[i] = segmentTree.getElementAt(i);
  }

  // verify validity
  RangeAndTree andTree(elements);
  for (auto limit : limits) {
    if (andTree.andRange(limit) != limit.value) return false;
  }

  return true;
}

int main() {
  int nElements, nLimits;
  cin >> nElements >> nLimits;

  vector<Limit> limits(nLimits);
  for (int i = 0; i < nLimits; ++i) {
    cin >> limits[i].l >> limits[i].r >> limits[i].value;
    --limits[i].l;
    --limits[i].r;
  }

  vector<int> resultingElements(nElements);
  bool result = solve(limits, resultingElements);
  if (result) {
    cout << "YES" << endl;
    for (int i = 0; i < nElements; ++i) {
      cout << resultingElements[i] << " ";
    }
    cout << endl;
  } else {
    cout << "NO" << endl;
  }
}