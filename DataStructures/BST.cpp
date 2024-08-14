#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
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

TreeNode* successorSearch(TreeNode* root) {
    if (root->right != NULL) {
        return minimumSearch(root->right);
    }
    TreeNode* parent = root->parent;
    while (parent != NULL && root == parent->right) {
        root = parent;
        parent = parent->parent;
    }
    return parent;
}

TreeNode* predecessorSearch(TreeNode* root) {
    if (root->left != NULL) {
        return maximumSearch(root->left);
    }
    TreeNode* parent = root->parent;
    while (parent != NULL && root == parent->left) {
        root = parent;
        parent = parent->parent;
    }
    return parent;
}

// Time complexity: O(h), h is the height of the tree
void insert(TreeNode* root, TreeNode* node) {
    TreeNode* x = root;
    TreeNode* y = NULL;     // y is parent of node
    while (x != NULL) {
        y = x;
        if (node->val < x->val) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = y;
    if (y == NULL) root = node;
    else if (node->val < y->val) 
        y->left = node;
    else y->right = node;
}

void transplant(TreeNode* root, TreeNode* u, TreeNode* v) {
    if (u->parent == NULL)
        root = v;
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else u->parent->right = v;
    if (v != NULL) {
        v->parent = u->parent;
    }
}

// Time complexity: O(h), h is the height of the tree
void deleteTreeNode(TreeNode* root, TreeNode* node) {
    if (node->left == NULL) {
        transplant(root, node, node->right);            // replace z by its right child
    }
    else if (node->right == NULL) {
        transplant(root, node, node->left);             // replace z by its left child
    }
    else {                                              // y is node's successor
        TreeNode* y = minimumSearch(root->right);
        if (y != node->right) {
            // replace y by its right child
            transplant(root, y, y->right);
            // node's right child becomes y's right child
            y->right = node->right;
            y->right->parent = y;
        }
        // replace node by its successor y
        transplant(root, node, y);
        // give node's left child to y, which had no left child
        y->left = node->left;
        y->left->parent = y;
    }
}

int main() {

    return 0;
}