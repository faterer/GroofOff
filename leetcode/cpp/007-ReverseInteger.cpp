// No.7 easy https://leetcode.com/problems/reverse-integer/
// Reverse digits of an integer.
// Example1: x = 123, return 321
// Example2: x = -123, return -321
#include <iostream>
#include <climits>

using namespace std;

class Solution {
public:
	int reverse(int x) {
		long long res = 0;

		while(x) {
			res = res * 10 + x % 10;
			x /= 10;
		}

		return (res < INT_MIN || res > INT_MAX) ? 0 : res;
	}
};

int main()
{
	Solution s;
	cout << s.reverse(123) << endl;
	cout << s.reverse(-123) << endl;
	cout << s.reverse(1534236469) <<endl;
	cout << s.reverse(-2147483412) <<endl;
	cout << s.reverse(-2147483648) <<endl;
	return 0;
}