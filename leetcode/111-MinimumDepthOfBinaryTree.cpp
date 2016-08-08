// No.111 easy https://leetcode.com/problems/minimum-depth-of-binary-tree/
// Given a binary tree, find its minimum depth.

// The minimum depth is the number of nodes along 
// the shortest path from the root node down to the nearest leaf node.

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
    int minDepth(TreeNode* root) {
        if(root == NULL) return 0;
        if(root->left == NULL) return 1 + minDepth(root->left);
        if(root->right == NULL) return 1 + minDepth(root->right);
        return 1 + min(minDepth(root->left), minDepth(root->right));
    }
};