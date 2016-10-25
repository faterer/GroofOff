// No.119 easy https://leetcode.com/problems/pascals-triangle-ii/
// Given an index k, return the kth row of the Pascal's triangle.

// For example, given k = 3,
// Return [1,3,3,1].
class Solution {
public:
    vector<int> getRow(int rowIndex) {
    	vector<int> v(rowIndex+1, 0);
    	v[0] = 1;
    	for(int i = 1; i < rowIndex+1; ++i)
    		for(int j = i; j >= 1; j--)
    			v[j] += v[j-1];

    	return v;
    }
};