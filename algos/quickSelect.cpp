#include <vector>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // quickSelect
        return quickSelect(nums, 0, nums.size() - 1, k);
    }
    
    int quickSelect(vector<int>& nums, const int lo, const int hi, const int k) {
        int pivotIdx = lo + (hi - lo) / 2;
        int pivot = nums[pivotIdx];
        swap(nums[nums.size() - 1], nums[pivotIdx]);
        
        // partition numbers around pivot value and get the divider index
        int wlo = 0;
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] > pivot) {
                swap(nums[wlo++], nums[i]);
            }
        }
        swap(nums[wlo++], nums[nums.size() - 1]);
        
        // [0, wlo) are greater than pivot, wlo is equal, the [wlo + 1, end] are smaller
        if (k == wlo) {
            return pivot;
        } else if (k < wlo) { // higher number, go left
            return quickSelect(nums, lo, wlo - 1, k);
        } else { // k > wlo, smaller number, go right
            return quickSelect(nums, wlo + 1, hi, k - wlo);
        }
    }
};

int main(void) {
    
}