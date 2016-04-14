// No.1 easy https://leetcode.com/problems/two-sum/
// Given an array of integers, 
// return indices of the two numbers such that they add up to a specific target.
// You may assume that each input would have exactly one solution.
// Example:
// Given nums = [2, 7, 11, 15], target = 9,
// Because nums[0] + nums[1] = 2 + 7 = 9,
// return [0, 1].
// The return format had been changed to zero-based indices. 
// Please read the above updated description carefully.
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
    	unordered_map<int, int> m;
    	vector<int> result;

    	for (int i = 0; i < nums.size(); ++i) {
    		if (m.find(nums[i]) == m.end()) {
    			m[target - nums[i]] = i;
    		} else {
    			result.push_back(m[nums[i]]+1);
    			result.push_back(i+1);
    			break;
    		}
    	}
        return result;
    }
};

int main()
{
	int a[] = {2,7,11,15};
	vector<int> nums(a,a+4);
	Solution s;
	vector<int> result(s.twoSum(nums, 9));
	for(auto i : result)
		cout << i << ",";
	cout << endl;
}