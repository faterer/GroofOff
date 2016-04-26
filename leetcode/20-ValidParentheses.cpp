// No.20 easyhttps://leetcode.com/problems/valid-parentheses/
// Given a string containing just the characters '(', ')', '{', '}', '[' and ']', 
// determine if the input string is valid.
// The brackets must close in the correct order, "()" and "()[]{}" are all valid
// but "(]" and "([)]" are not.
#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
        	if (c == '('||c == '{'||c=='[')
        		st.push(c);
        	else {
        		if (st.empty()) return false;
        		if (c == ')' && st.top() != '(') return false;
        		if (c == '}' && st.top() != '{') return false;
        		if (c == ']' && st.top() != '[') return false;
        		st.pop();
        	}
        }
        return st.empty();
    }
};

int main(int argc, char**argv)
{
	Solution s;
    string s1 = "{{}{[]()}}";
    if (argc>1){
        s1 = argv[1];
    }
    cout << "str = \"" << (s1) << "\"" << endl;
    cout << s.isValid(s1) << endl;
}