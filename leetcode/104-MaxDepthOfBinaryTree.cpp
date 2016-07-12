// No.104 easy https://leetcode.com/problems/maximum-depth-of-binary-tree/
// Given a binary tree, find its maximum depth.
// The maximum depth is the number of nodes along the longest path 
// from the root node down to the farthest leaf node.
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
    int maxDepth(TreeNode* root) {
        return root == NULL ? 0 : 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};