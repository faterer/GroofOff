// No.7 easy https://leetcode.com/problems/string-to-integer-atoi/
// Implement atoi to convert a string to an integer.
// Hint: Carefully consider all possible input cases. 
// If you want a challenge, please do not see below and ask yourself 
// what are the possible input cases.
// Notes: It is intended for this problem to be specified 
// vaguely (ie, no given input specs). You are responsible to 
// gather all the input requirements up front.

#include <string>
#include <iostream>
#include <climits>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        int sign = 1, base = 0, i = 0;
        while (str[i] == ' ') i++;
        if (str[i] == '+' || str[i] == '-') {
        	sign = 1 - 2 * (str[i++] == '-');
        }
        while (str[i] >= '0' && str[i] <= '9') {
        	if (base > INT_MAX/10 || (base == INT_MAX/10 && str[i] - '0' > INT_MAX%10)) {
        		if (sign == 1) return INT_MAX;
        		else return INT_MIN;
        	}
        	base = 10*base + str[i++] - '0';
        }
        return base * sign;
    }
};

int main()
{
	Solution s;
	cout << s.myAtoi(string("123")) << endl;
	cout << s.myAtoi(string("-123")) << endl;
	cout << s.myAtoi(string("1534236469")) <<endl;
	cout << s.myAtoi(string("-2147483412")) <<endl;
	cout << s.myAtoi(string("-2147483649")) <<endl;
	return 0;
}