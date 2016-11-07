// No.242 easy https://leetcode.com/problems/valid-anagram/
// Given two strings s and t, write a function to determine if t is an anagram of s.

// For example,
// s = "anagram", t = "nagaram", return true.
// s = "rat", t = "car", return false.

// Note:
// You may assume the string contains only lowercase alphabets.Given two strings s and t, 
// write a function to determine if t is an anagram of s.

// For example,
// s = "anagram", t = "nagaram", return true.
// s = "rat", t = "car", return false.

// Note:
// You may assume the string contains only lowercase alphabets.
class solution {
public:
	bool isAnagram(string s, string t) {
		sort(s.begin(), s.end());
		sort(t.begin(), t.end());
		return s == t;
	}
}

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        int n = s.length();
        unordered_map<char, int> counts;
        for (int i = 0; i < n; i++) {
            counts[s[i]]++;
            counts[t[i]]--;
        }
        for (auto count : counts)
            if (count.second) return false;
        return true;
    }
};

class Solution {
public:
    bool isAnagram(string s, string t) {
        int alphabets[26] = { 0 };
        for(int i = 0; i < s.size(); ++i) alphabets[s[i] - 'a']++;
        for(int i = 0; i < s.size(); ++i) alphabets[t[i] - 'a']--;

        for(int i = 0; i < 26; ++i) {
            if (alphabets[i] != 0)
                return false;
        }
        return true;
    }
}