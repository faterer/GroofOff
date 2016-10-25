// No.9 easy https://leetcode.com/problems/palindrome-number/
// Determine whether an integer is a palindrome. Do this without extra space.

#include <iostream>

using namespace std;


class Solution {
public:
    bool isPalindrome(int x) {
    	if(x < 0 || (x != 0 && x%10 == 0))
    		return false;
    	int sum = 0;
    	while(x > sum) {
    		sum = sum*10 + x%10;
    		x = x/10;
    	}
    	return (x == sum) || (x == sum/10);
    }
};

int main()
{
	Solution s;
	cout << s.isPalindrome(121) << endl;
	cout << s.isPalindrome(22) << endl;
	cout << s.isPalindrome(1234321) << endl;
	cout << s.isPalindrome(-2147483648) << endl;
	return 0;
}
