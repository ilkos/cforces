#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct BigInt {
    static const uint64_t BASE = 1000000;
    static const uint32_t BASESZ = 6;
    
    // stored lsb -> msb
    vector<uint64_t> nums;
    
    BigInt() : nums(vector<uint64_t>()) {}
    
    BigInt(uint32_t num) : nums(vector<uint64_t>()) {
        while (num) {
            nums.push_back(num % BASE);
            num /= BASE;
        }
    }
    
    BigInt& operator+= (const BigInt& other) {
        vector<uint64_t> pad;
        
        uint64_t carry = 0;
        for (int i = 0; i < min(nums.size(), other.nums.size()); ++i) {
            uint64_t next = nums[i] + other.nums[i] + carry;
            carry = baseLine(next);
            pad.push_back(next);
        }
        
        const vector<uint64_t>& larger = nums.size() > other.nums.size() ? nums : other.nums;
        for (int i = min(nums.size(), other.nums.size()); i < larger.size(); ++i) {
            uint64_t next = larger[i] + carry;
            carry = baseLine(next);
            pad.push_back(next);
        }
        
        if (carry) {
            pad.push_back(carry);
        }
        
        nums = pad;
        return *this;
    }

    BigInt square() const {
        BigInt result = BigInt();

        for (int i = 0; i < nums.size(); ++i) {
            uint64_t carry = 0;
            for (int j = 0; j < nums.size(); ++j) {
                if (i + j >= result.nums.size()) result.nums.resize(i + j + 1);
                result.nums[i + j] += nums[i] * nums[j] + carry;
                carry = baseLine(result.nums[i + j]);
            }
            
            int n = nums.size();
            while (carry) {
                if (i + n <= result.nums.size()) result.nums.resize(i + n + 1);
                result.nums[i + n] += carry;
                carry = baseLine(result.nums[i + n]);
                ++n;
            }
        }
        
        return result;
    }

    static uint64_t baseLine(uint64_t& num) {
        uint64_t carry = 0;
        if (num >= BASE) {
            carry = num / BASE;
            num %= BASE;
        }
        return carry;
    }

    string toString() const {
        string result;
        
        for (int i = 0; i < nums.size(); ++i) {
            // current factor is nums[i] * 1000000 (1 million) ^ i
            // for each power i, shift left digits and add
            // e.g. 3, 2, 5 = 3 * 1000000^0 + 2 * 1000000 ^ 1 + 5 * 1000000000000 = 5000002000003
            string factor = to_string(nums[i]);
            reverse(factor.begin(), factor.end());
            
            // position factor at i * 6
            result.resize(i * BASESZ, '0');
            result += factor;
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};

int main(void) {
    BigInt bg = BigInt(100042000);
    bg += BigInt(2400000123);
    BigInt copy = bg;
    cout << copy.toString() << endl;

    BigInt mult = BigInt(538783); // expect 290287121089
    cout << mult.square().toString() << endl;
}