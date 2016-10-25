// No.101 easy https://leetcode.com/problems/symmetric-tree/
// Given a binary tree, check whether it is a mirror of itself 
// (ie, symmetric around its center).
// For example, this binary tree [1,2,2,3,4,4,3] is symmetric:
//     1
//    / \
//   2   2
//  / \ / \
// 3  4 4  3
// But the following [1,2,2,null,3,null,3] is not:
//     1
//    / \
//   2   2
//    \   \
//    3    3
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
    bool isSymmetric(TreeNode* root) {
    	if(root == NULL) return true;
    	return helper(root->left, root->right);   
    }

    bool helper(TreeNode* p, TreeNode* q) {
    	if (p == NULL || q == NULL)
    		return p == q;
    	if (p->val != q->val)
    		return false;
    	return helper(p->left, q->right) && helper(p->right, q->left);
    }
};