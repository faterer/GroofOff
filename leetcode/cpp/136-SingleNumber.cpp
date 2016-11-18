// No.136 easy https://leetcode.com/problems/single-number/
// Given an array of integers, every element appears twice except for one. 
// Find that single one.

// Note:
// Your algorithm should have a linear runtime complexity. 
// Could you implement it without using extra memory?
class Solution {
public:
	// known that A XOR A = 0 and the XOR operator is commutative, 
	// the solution will be very straightforward.
    int singleNumber(vector<int>& nums) {
        int result = nums[0];
        for(int i = 1; i < nums.size(); ++i) {
            result ^= nums[i];
        }
        return result;
    }

	int singleNumber(vector<int>& nums) {
		int result = 0;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size(); ++i) {
			if (i % 2 == 0)
			result += nums[i];
			else
			result -= nums[i];
		}
		return result;
	}
};