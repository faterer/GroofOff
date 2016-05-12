// No.26 easy https://leetcode.com/problems/remove-duplicates-from-sorted-array/
// Given a sorted array, remove the duplicates in place such that 
// each element appear only once and return the new length.
// Do not allocate extra space for another array, 
// you must do this in place with constant memory.
// For example,
// Given input array nums = [1,1,2],
// Your function should return length = 2, 
// with the first two elements of nums being 1 and 2 respectively. 
// It doesn't matter what you leave beyond the new length.
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return n;
        int idx = 1;
        for (int i = 1; i < n; ++i) {
        	if (nums[i] != nums[i-1])
        		nums[idx++] = nums[i];
        }
        return idx;
    }
};

int main()
{
	int array[] = {1,1,2,2,2,3,3};
	vector<int> v(array, array+7);
	Solution s;
	int idx = s.removeDuplicates(v);
	for (int i = 0; i < idx; ++i)
	{
		cout << v[i] << ",";
	}
	cout << endl;
}