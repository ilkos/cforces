#include <vector>
#include <queue>
#include <map>
#include <iostream>

using namespace std;

struct CompareFirst {
    bool operator() (const pair<int, multimap<int, int>::iterator>& lhs,
                     const pair<int, multimap<int, int>::iterator>& rhs) {
        return lhs.first > rhs.first;
    }
};

class Solution {
    typedef priority_queue<pair<int, multimap<int, int>::iterator>,
                vector<pair<int, multimap<int, int>::iterator>>,
                CompareFirst> Queue;

public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {        
        auto result = vector<pair<int, int>>();
        if (buildings.empty()) {
            return result;
        }
        
        // pq of (rightPos, pointer to map<>)
        Queue pq = Queue();
        auto maxSet = multimap<int, int>(); // height -> pos
        
        int buildingIdx = 0;
        while (!pq.empty() || buildingIdx < buildings.size()) {
            // determine next event
            const vector<int>& building = buildings[buildingIdx];

            // no closing events, or the closing event is after the building
            if (pq.empty() || (buildingIdx < buildings.size() && buildings[buildingIdx][0] < pq.top().first)) {
                if (maxSet.empty() || building[2] > maxSet.rbegin()->first) {
                    addToResult(result, building[0], building[2]);
                }
                addToQueue(pq, maxSet, building);
                ++buildingIdx;
            } else { // pq non empty in this clause, closing event
                // pop and add element (or zero)
                int rightPos;
                multimap<int, int>::iterator maxIt;
                tie(rightPos, maxIt) = pq.top(); pq.pop();

                maxSet.erase(maxIt);

                if (!pq.empty()) {
                    auto highestRunningIt = maxSet.rbegin();
                    if (highestRunningIt->second == rightPos) continue;

                    // of the running buildings, pick the greatest height
                    addToResult(result, rightPos, highestRunningIt->first);
                } else {
                    addToResult(result, rightPos, 0);
                }
            }
        }

        // merge identical elements
        auto final = vector<pair<int, int>>();
        
        // merge same startPos with heights
        int pos = 0;
        int startPos = -1;
        int maxHeight = -1;
        while (pos < result.size()) {
            if (startPos < 0 || startPos != result[pos].first) {
                if (startPos >= 0) {
                    final.push_back(make_pair(startPos, maxHeight));
                }
                startPos = result[pos].first;
                maxHeight = result[pos].second;
            } else {
                maxHeight = max(maxHeight, result[pos].second);
            }

            ++pos;
        }
        final.push_back(make_pair(startPos, maxHeight));

        auto final2 = vector<pair<int, int>>();

        // merge same heights
        int prevHeight = final[0].second;
        final2.push_back(final[0]);
        for (int i = 1; i < final.size(); ++i) {
            if (final[i].second == prevHeight) continue;
            final2.push_back(final[i]);
            prevHeight = final[i].second;
        }

        return final2;
    }
    
    void addToResult(vector<pair<int, int>>& result, int pos, int height) {
        result.push_back(make_pair(pos, height));
    }
    
    void addToQueue(Queue& q, multimap<int, int>& maxSet, const vector<int>& building) {
        auto it = maxSet.insert(make_pair(building[2], building[1]));
        q.push(make_pair(building[1], it));
    }
};

int main() {
    Solution s;
    vector<vector<int>> question = {{2,13,10},{10,17,25},{12,20,14}};
    auto result = s.getSkyline(question);

    for (pair<int, int> r: result) {
        cout << r.first << " " << r.second << endl;
    }
}