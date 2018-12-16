// No.66 easy https://leetcode.com/problems/plus-one/
// Given a non-negative number represented as an array of digits, plus one to the number.
// The digits are stored such that the most significant digit is at the head of the list.
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
    	int n = digits.size();

    	for(int i = n-1; i >= 0; i--) {
    		if(digits[i] == 9) {
    			digits[i] = 0;
    		} else {
    			digits[i] += 1;
    			return digits;
    		}
    	}   

    	digits[0] = 1;
    	digits.push_back(0);
    	return digits;
    }
};

int main()
{
	int array1[] = {9,9,9,9};
	int array2[] = {1,1,1,1};
	vector<int> digits1(array1, array1+4);
	vector<int> digits2(array2, array2+4);
	vector<int> digits;
	Solution s;
	digits = s.plusOne(digits1);
	for(auto digit : digits1)
		cout << digit;
	cout << endl;
	digits = s.plusOne(digits2);
	for(auto digit : digits)
	cout << digit;
	cout << endl;
	return 0;
}