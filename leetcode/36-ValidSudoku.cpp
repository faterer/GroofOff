// No.36 easy https://leetcode.com/problems/valid-sudoku/
// Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
// The Sudoku board could be partially filled, 
// where empty cells are filled with the character '.'.
// A partially filled sudoku which is valid.
// Note:
// A valid Sudoku board (partially filled) is not necessarily solvable. 
// Only the filled cells need to be validated.
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
       int used1[9][9] = {0}, used2[9][9] = {0}, used3[9][9] = {0};

        for(int i = 0; i < board.size(); ++i)
            for(int j = 0; j < board[i].size(); ++j)
                if(board[i][j] != '.')
                {
                    int num = board[i][j] - '0' - 1, k = i / 3 * 3 + j / 3;
                    if(used1[i][num] || used2[j][num] || used3[k][num])
                        return false;
                    used1[i][num] = used2[j][num] = used3[k][num] = 1;
                }

        output(used1);cout <<"=========================" <<endl;
        output(used2);cout <<"=========================" <<endl;
        output(used3);cout <<"=========================" <<endl;

        return true;        
    }
  
    void output(int used[][9]) {
    	for(int i = 0; i < 9; ++i) {
    		for (int j = 0; j < 9; ++j) {
    			cout << used[i][j] << ",";
    		}
    		cout << endl;
        }   
    }
};

int main(int argc, char const *argv[])
{
	vector<vector<char>> board1 = {
		{'5','3','.','.','7','.','.','.','.'},
		{'6','.','.','1','9','5','.','.','.'},
		{'.','9','8','.','.','.','.','6','.'},
		{'8','.','.','.','6','.','.','.','3'},
		{'4','.','.','8','.','3','.','.','1'},
		{'7','.','.','.','2','.','.','.','6'},
		{'.','6','.','.','.','.','2','8','.'},
		{'.','.','.','4','1','9','.','.','5'},
		{'.','.','.','.','8','.','.','7','9'}
	};
	Solution s;
	cout << s.isValidSudoku(board1) << endl;
	return 0;
}