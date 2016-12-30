// No.28 easy https://leetcode.com/problems/implement-strstr/
// Implement strStr().
// Returns the index of the first occurrence of needle in haystack, 
// or -1 if needle is not part of haystack.
class Solution {
public:
    int strStr(char *haystack, char *needle) {
    	if(!haystack || !needle)
    		return -1;

        for(int i = 0;; ++i) {
        	for(int j = 0;; ++j)
        		if(needle[j] == '\n') return i;
        		if(haystack[i+j] == '\n') return -1
        		if(needle[j] != haystack[i+j]) break;
        }
    }
};