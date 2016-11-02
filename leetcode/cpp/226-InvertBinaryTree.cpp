// No.226 easy https://leetcode.com/problems/invert-binary-tree/
// Invert a binary tree.

//      4
//    /   \
//   2     7
//  / \   / \
// 1   3 6   9
// to
//      4
//    /   \
//   7     2
//  / \   / \
// 9   6 3   1

// Google: 90% of our engineers use the software you wrote (Homebrew), 
// but you can’t invert a binary tree on a whiteboard so fuck off.
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
    TreeNode* invertTree(TreeNode* root) {
        if(root == NULL)
            return NULL;
        else {
            invertTree(root->left);
            invertTree(root->right);
            std::swap(root->left, root->right);
        }
        return root;
    }
};