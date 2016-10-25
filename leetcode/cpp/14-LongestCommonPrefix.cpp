// No.14 easy https://leetcode.com/problems/longest-common-prefix/
// Write a function to find the longest common prefix string amongst an array of strings.
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string result;
        if(strs.size() == 0) return result;
        for(int i = 0;;++i) {
        	string s1 = strs[0];
        	for(int j = 0;j < strs.size();++j) {
        		string s2 = strs[j];
        		if(!s1[i] || !s2[i] || s1[i] != s2[i])
        			return result;
        	}
        	result += s1[i];
        }
        return result;
    }
};

int main()
{
	Solution l;
    const char* s[]={"abab","aba","abc"};
    vector<string> v1(s, s+3);
    cout << l.longestCommonPrefix(v1) <<endl;

    vector<string> v2(1,"");
    cout << l.longestCommonPrefix(v2) <<endl;
}
