#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* newNode(int val) {
    TreeNode* node = new TreeNode();
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void inOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

// tree search
TreeNode* treeSearch(TreeNode* root, int val) {
    if (root == NULL || root->val == val) {
        return root;
    }
    if (val < root->val) {
        return treeSearch(root->left, val);
    }
    return treeSearch(root->right, val);
}

TreeNode* minimumSearch(TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

TreeNode* maximumSearch(TreeNode* root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

int main() {

    return 0;
}