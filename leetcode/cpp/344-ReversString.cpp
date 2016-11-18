// No.344 https://leetcode.com/problems/reverse-string/
// Write a function that takes a string as input and returns the string reversed.

// Example:
// Given s = "hello", return "olleh".
class Solution {
public:
    string reverseString(string s) {
        std::reverse(s.begin(), s.end());
        return s;
    }

    string reverseString(string s) {
    	int i = 0, j = s.size() - 1;
    	while(i < j) {
    		std::swap(s[i++], s[j--]);
    	}
    	return s;
    }
};