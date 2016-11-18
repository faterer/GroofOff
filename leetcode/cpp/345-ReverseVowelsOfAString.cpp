// No.345 easy https://leetcode.com/problems/reverse-vowels-of-a-string/
// Write a function that takes a string as input and reverse only the vowels of a string.
// Example 1:
// Given s = "hello", return "holle".
// Example 2:
// Given s = "leetcode", return "leotcede".
// Note:
// The vowels does not include the letter "y".
class Solution {
public:
	string reverseVowels(string s) {
		int i = 0;
		int j = s.size() - 1;

		while(i < j) {
			i = s.find_first_of("aeiouAEIOU", i);
			j = s.find_last_of("aeiouAEIOU", j);
			if (i < j) {
			    swap(s[i++], s[j--]);
			}
		}
		return s;  
	}

	string reverseVowels(string s) {
		int dict[256] = {0};
		dict['a'] = 1, dict['A'] = 1;
		dict['e'] = 1, dict['E'] = 1;
		dict['i'] = 1, dict['I'] = 1;
		dict['o'] = 1, dict['O'] = 1;
		dict['u'] = 1, dict['U'] = 1;
		int start = 0, end = (int)s.size() - 1;
		while(start < end){
			while(start < end && dict[s[start]] == 0) start++;
			while(start < end && dict[s[end]] == 0) end--;
			swap(s[start],s[end]);
			start++;end--;
		}
		return s;
	}
};