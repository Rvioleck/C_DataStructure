//
// Created by Rvioleck on 2021/2/9.
//

#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:

    TreeNode *cur = new TreeNode(0);
    TreeNode *ret = cur;

//    TreeNode* convertBiNode(TreeNode* root) {
//        if (!root)
//            return nullptr;
//        convertBiNode(root->left);
//        res->right = root;
//        res->left = nullptr;
//        res = res->right;
//        convertBiNode(root->right);
//        return ret->right;
//    }

    void inOrder(TreeNode *root) {
        if (!root)
            return;
        inOrder(root->left);
        cur->right = root;
        cur->left = nullptr;
        cur = cur->right;
        inOrder(root->right);
    }

    TreeNode* convertBiNode(TreeNode* root) {
        inOrder(root);
        return ret->right;
    }
};