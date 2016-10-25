// No.125 easy https://leetcode.com/problems/valid-palindrome/
// Given a string, determine if it is a palindrome, 
// considering only alphanumeric characters and ignoring cases.

// For example,
// "A man, a plan, a canal: Panama" is a palindrome.
// "race a car" is not a palindrome.
#include <ctype.h> // int isalnum(int ch); int toupper(int ch);

class Solution {
public:
    bool isPalindrome(string s) {
        for(int i = 0, j = s.size() - 1; i < j; ++i,--j) {
        	// isalnum includes 0-9 A-Z a-z
            while(!isalnum(s[i]) && i < j) ++i;
            while(!isalnum(s[j]) && i < j) --j;
            if(toupper(s[i]) != toupper(s[j]))
                return false;
        }
        
        return true;
    }
};