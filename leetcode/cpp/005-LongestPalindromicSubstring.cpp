// No.5 medium https://leetcode.com/problems/longest-palindromic-substring/
// Given a string s, find the longest palindromic substring in s. 
// You may assume that the maximum length of s is 1000.
// Example:
// Input: "babad"
// Output: "bab"
// Note: "aba" is also a valid answer.
// Example:
// Input: "cbbd"
// Output: "bb"
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        if (s.size() == 1) return s;
        int min_start = 0, max_len = 1;
        for (int i = 0; i < s.size(); ) {
        	if (s.size() - i <= max_len / 2) break;
        	int j = i, k = i;
        	while (k < s.size() - 1 && s[k+1] == s[k]) ++k; //skip duplicate characters.
        	i = k + 1;
        	while (k < s.size() - 1 && j > 0 && s[k+1] == s[j-1]) {
        		++k;
        		--j;
        	}
        	int new_len = k - j + 1;
        	if (new_len > max_len) {
        		min_start =j;
        		max_len = new_len;
        	}
        }
        return s.substr(min_start, max_len);
    }
};