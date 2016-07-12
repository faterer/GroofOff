// No.107 easy https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
// Given a binary tree, return the bottom-up level order traversal of its nodes' values. 
// (ie, from left to right, level by level from leaf to root).

// For example:
// Given binary tree [3,9,20,null,null,15,7],
//     3
//    / \
//   9  20
//     /  \
//    15   7
// return its bottom-up level order traversal as:
// [
//   [15,7],
//   [9,20],
//   [3]
// ]
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
	vector<vector<int>> res;

	void buildVec(TreeNode* root, int depth) {
		if(root == NULL) return;
		if(res.size() == depth) res.push_back(vector<int>());
		res[depth].push_back(root->val);
		buildVec(root->left, depth+1);
		buildVec(root->right, depth+1);
	}

    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        buildVec(root, 0);
        reverse(res.begin(), res.end());
        return res;
    }
};