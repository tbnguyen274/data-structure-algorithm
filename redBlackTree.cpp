/*
the height of a red-black tree with n keys is at most 2log*(n+1), which is O(log n).

Each node of the tree now contains the attributes color, key, left , right , and parent.

A red-black tree is a binary search tree that satisûes the following red-black
properties:
1. Every node is either red or black
2. The root is black
3. Every leaf (NIL) is black
4. If a node is red, then both its children are black
5. For each node, all simple paths from the node to descendant leaves contain the same
number of black nodes.
*/

#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    bool color; // 0 for black, 1 for red
    TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL), color(1) {}
};

// Time complexity: O(1)
void leftRotate(TreeNode* root, TreeNode* x) {
    TreeNode* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) 
        root = y;
    else if (x == x->parent->left) 
        x->parent->left = y;
    else 
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Time complexity: O(1)
void rightRotate(TreeNode* root, TreeNode* x) {
    TreeNode* y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) 
        root = y;
    else if (x == x->parent->right) 
        x->parent->right = y;
    else 
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void insertFixup(TreeNode* root, TreeNode* node) {
    while (node->parent->color == 1) {
        // is node's parent a left child?
        if (node->parent == node->parent->parent->left) {
            // y is z's uncle
            TreeNode* y = node->parent->parent->right;
            // case 1
            if (y->color == 1) {
                node->parent->color = 0;
                y->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            }
            else {
                // case 2
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(root, node);
                }
                // case 3
                node->parent->color = 0;
                node->parent->parent->color = 1;
                rightRotate(root, node->parent->parent);
            }
        }
        // "right" and "left" are swapped from above
        else {
            TreeNode* y = node->parent->parent->left;
            if (y->color == 1) {
                node->parent->color = 0;
                y->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(root, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                leftRotate(root, node->parent->parent);
            }
        }
    }
    root->color = 0;
}

// Time complexity: O(log n)
// Never perform more than 2 rotations
void insertRB (TreeNode* root, TreeNode* node) {
    TreeNode* x = root;
    TreeNode* y = NULL;
    while (x != NULL) {
        y = x;
        if (node->val < x->val) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = y;
    if (y == NULL) {
        root = node;
    } else if (node->val < y->val) {
        y->left = node;
    } else {
        y->right = node;
    }
    node->left = NULL;
    node->right = NULL;
    node->color = 1;
    insertFixup(root, node);
}

void transplantRB(TreeNode* root, TreeNode* u, TreeNode* v) {
    if (u->parent == NULL) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

TreeNode* minimumSearch(TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

void deleteFixup(TreeNode* root, TreeNode* node) {
    while (node != root && node->color == 0) {
        if (node == node->parent->left) {
            TreeNode* w = node->parent->right;

            // case 1
            if (w->color == 1) {
                w->color = 0;
                node->parent->color = 1;
                leftRotate(root, node->parent);
                w = node->parent->right;
            }

            // case 2
            if (w->left->color == 0 && w->right->color == 0) {
                w->color = 1;
                node = node->parent;
            }
            else {
                // case 3
                if (w->right->color == 0) {
                    w->left->color = 0;
                    w->color = 1;
                    rightRotate(root, w);
                    w = node->parent->right;
                }

                // case 4
                w->color = node->parent->color;
                node->parent->color = 0;
                w->right->color = 0;
                leftRotate(root, node->parent);
                node = root;
            }
        }
        // "right" and "left" exchanged
        else {
            TreeNode* w = node->parent->left;
            if (w->color == 1) {
                w->color = 0;
                node->parent->color = 1;
                rightRotate(root, node->parent);
                w = node->parent->left;
            }
            if (w->right->color == 0 && w->left->color == 0) {
                w->color = 1;
                node = node->parent;
            } else {
                if (w->left->color == 0) {
                    w->right->color = 0;
                    w->color = 1;
                    leftRotate(root, w);
                    w = node->parent->left;
                }
                w->color = node->parent->color;
                node->parent->color = 0;
                w->left->color = 0;
                rightRotate(root, node->parent);
                node = root;
            }
        }
    }
    node->color = 0;
}

// Time complexity: O(log n)
void deleteRB(TreeNode* root, TreeNode* node) {
    TreeNode* y = node;
    TreeNode* x;
    bool yOriginalColor = y->color;
    if (node->left == NULL) {
        x = node->right;
        transplantRB(root, node, node->right);
    } else if (node->right == NULL) {
        x = node->left;
        transplantRB(root, node, node->left);
    } else {
        y = minimumSearch(node->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == node) {
            x->parent = y;
        } else {
            transplantRB(root, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        transplantRB(root, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }
    if (yOriginalColor == 0) {
        deleteFixup(root, x);
    }
}

/*
------------ AVL tree ----------------
An AVL tree is a binary search tree that is height balanced: for each node x, the heights of the left and right subtrees of x differ by at most 1. To implement an AVL tree, maintain an extra attribute h in each node such that x:h is the height of node x. As for any other binary search tree T , assume that T:root points to the root 
node.

The height of an AVL tree storing n keys is O(log n). The AVL tree is named after its inventors, Adelson-Velskii and Landis.
*/