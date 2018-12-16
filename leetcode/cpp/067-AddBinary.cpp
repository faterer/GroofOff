// No.67 easy https://leetcode.com/problems/add-binary/
// Given two binary strings, return their sum (also a binary string).
// For example,
// a = "11"
// b = "1"
// Return "100".
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string s = "";

        int c = 0, i = a.size() - 1, j = b.size() - 1;
        while(i >= 0 || j >= 0 || c == 1) {
        	c += i >= 0 ? a[i--] - '0' : 0;
        	c += j >= 0 ? b[j--] - '0' : 0;
        	s += char(c % 2 + '0');
        	c /= 2;
        }
        
        return s;
    }
};

int main()
{
	string a = "11";
	string b = "1";
	Solution s;
	string result = s.addBinary(a, b);
	cout << result << endl;
	return 0;
}