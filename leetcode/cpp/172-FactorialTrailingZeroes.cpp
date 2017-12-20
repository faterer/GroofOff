// No.172 easy https://leetcode.com/problems/factorial-trailing-zeroes
// Given an integer n, return the number of trailing zeroes in n!.
// Note: Your solution should be in logarithmic time complexity.
// https://discuss.leetcode.com/topic/6513/simple-c-c-solution-with-detailed-explaination

class Solution {
public:
    int trailingZeroes(int n) {
        int result = 0;
        for(long long i = 0; n/i > 0; i*=5) {
        	result += (n/i);
        }
        return result;
    }
};