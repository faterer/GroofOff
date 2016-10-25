// No.171 easy https://leetcode.com/problems/excel-sheet-column-number/
// Given a column title as appear in an Excel sheet, return its corresponding column number.
// For example:
// A -> 1
// B -> 2
// C -> 3
// ...
// Z -> 26
// AA -> 27
// AB -> 28 

class Solution {
public:
    int titleToNumber(string s) {
        int result = 0;
        for (int i = 0; i < s.size(); ++i)
            result = result * 26 + (s[i] - 'A' + 1);
        return result;        
    }
};