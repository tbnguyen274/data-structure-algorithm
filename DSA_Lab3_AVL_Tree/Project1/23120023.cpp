#include <iostream>
#include <string>
#include <math.h>
#include <queue>

using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
	int height;
};

/*	-------------------- EXERCISE 1	-------------------- */

Node* newNode(int data) {
	Node* temp = new Node;
	temp->key = data;
	temp->left = temp->right = NULL;
	temp->height = 0;
	return temp;
}

int height(Node* node) {
	if (node == NULL) return -1;
	return node->height;
}

/*
	y				x
   /				 \
  x      ------->     y			Right Rotation
   \				 /
	z				z
*/
Node* rightRotate(Node* y) {
	Node* x = y->left;
	Node* z = x->right;

	// rotate
	x->right = y;
	y->left = z;

	// update heights
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

/*
	x						y
	 \					   /
	  y	   --------->	  x		Left Rotation
	 /					   \
	z						z
*/
Node* leftRotate(Node* x) {
	Node* y = x->right;
	Node* z = y->left;

	// rotate
	y->left = x;
	x->right = z;

	// update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

int getBalance(Node* root) {
	if (root == NULL) return 0;
	return height(root->left) - height(root->right);
}

Node* insertNode(Node* root, int data) {
	if (root == NULL) return newNode(data);

	if (data < root->key) {
		root->left = insertNode(root->left, data);
	}
	else if (data > root->key) {
		root->right = insertNode(root->right, data);
	}
	// do not add existing key
	else {
		return root;
	}

	// update height
	root->height = max(height(root->left), height(root->right)) + 1;

	// get root's balance factor
	int balance = getBalance(root);

	// LL
	if (balance > 1 && data < root->left->key) {
		return rightRotate(root);
	}
	// RR
	if (balance < -1 && data > root->right->key) {
		return leftRotate(root);
	}
	// LR
	if (balance > 1 && data > root->left->key) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	// RL
	if (balance < -1 && data < root->right->key) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

Node* searchNode(Node* root, int data) {
	if (root == NULL || data == root->key) return root;

	if (data < root->key) {
		return searchNode(root->left, data);
	}

	return searchNode(root->right, data);
}

Node* deleteNode(Node* root, int data) {
	if (root == NULL) return NULL;

	if (data < root->key) {
		root->left = deleteNode(root->left, data);
	}
	else if (data > root->key) {
		root->right = deleteNode(root->right, data);
	}
	// Node found
	else {

		// Case 1: No child (leaf node)
		if (root->left == NULL && root->right == NULL) {
			delete root;
			return NULL;
		}

		// Case 2: One child (right)
		else if (root->left == NULL) {
			Node* temp = root->right;
			delete root;
			return temp;
		}

		// Case 2: One child (left)
		else if (root->right == NULL) {
			Node* temp = root->left;
			delete root;
			return temp;
		}

		// Case 3: Two children
		// Find the smallest node in the right subtree
		Node* temp = root->right;
		while (temp->left != NULL) {
			temp = temp->left;
		}
		root->key = temp->key;
		root->right = deleteNode(root->right, temp->key);
	}

	if (root == NULL) return root;

	// UPDATE HEIGHT
	root->height = max(height(root->left), height(root->right)) + 1;

	// GET THE BALANCE FACTOR
	int balance = getBalance(root);

	// LL
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// LR
	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// RR
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// RL
	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

// Traversal in Pre-order, In-order, Post-order and Level-order.
void NLR(Node* root) {
	if (root == NULL) return;

	cout << root->key << " ";
	NLR(root->left);
	NLR(root->right);
}

void LNR(Node* root) {
	if (root == NULL) return;

	LNR(root->left);
	cout << root->key << " ";
	LNR(root->right);
}

void LRN(Node* root) {
	if (root == NULL) return;

	LRN(root->left);
	LRN(root->right);
	cout << root->key << " ";
}

void levelOrder(Node* root) {
	if (root == NULL) return;

	// BFS
	queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		Node* temp = q.front();
		q.pop();
		cout << temp->key << " ";

		if (temp->left != NULL) {
			q.push(temp->left);
		}
		if (temp->right != NULL) {
			q.push(temp->right);
		}
	}
}

/*	-------------------- EXERCISE 2	-------------------- */

bool isFull(Node* root) {
	if (root == NULL) return true;

	if (root->left == NULL && root->right == NULL) {
		return true;
	}
	if (root->left && root->right) {
		return isFull(root->left) && isFull(root->right);
	}

	return false;
}

bool isComplete(Node* root) {
	if (root == NULL) return true;
	queue<Node*> q;
	q.push(root);

	// if a NULL node is met, all its following nodes must be NULL
	bool flag = false;

	// level order traversal
	while (!q.empty()) {
		Node* temp = q.front();
		q.pop();

		// check left child
		if (temp->left == NULL) {
			flag = true;
		}
		else {
			if (flag) return false;
			q.push(temp->left);
		}

		// check right child
		if (temp->right == NULL) {
			flag = true;
		}
		else {
			if (flag) return false;
			q.push(temp->right);
		}
	}

	return true;
}

int countNodes(Node* root) {
	if (root == NULL) return 0;

	return 1 + countNodes(root->left) + countNodes(root->right);
}

bool isPerfect(Node* root) {
	if (root == NULL) return true;
	
	// a perfect binary tree has 2^(h+1) - 1 nodes
	int h = root->height;
	return countNodes(root) == pow(2, h + 1) - 1;
}

// Find the least common ancestor for any two given nodes in AVL Tree.
int findCommonAncestor(Node* root, int x, int y) {
	if (root == NULL) {
		cout << "Empty tree" << endl;
		return -1;
	}

	// check if x and y are nodes in the tree
	if (searchNode(root, x) == NULL || searchNode(root, y) == NULL) {
		cout << "Node not found" << endl;
		return -1;
	}

	if (root->key > x && root->key > y) {
		return findCommonAncestor(root->left, x, y);
	}
	if (root->key < x && root->key < y) {
		return findCommonAncestor(root->right, x, y);
	}

	return root->key;
}

/*
Find all nodes with 2 child nodes, and the left child is a divisor of the right child. Print them
 to the console in ascending order.
*/
void printSpecialNodes(Node* root) {
	if (root == NULL) return;
	
	// in-order traversal
	printSpecialNodes(root->left);
	if (root->left != NULL && root->right != NULL) {
		if (root->left->key != 0 && root->right->key % root->left->key == 0) {
			cout << root->key << " ";
		}
	}
	printSpecialNodes(root->right);
}

// Helper function to visualize the AVL Tree easily
void printTree(Node* root, string indent = "", bool last = true) {
	if (root == NULL) return;

	cout << indent;
	if (last) {
		cout << "R----";
		indent += "   ";
	}
	else {
		cout << "L----";
		indent += "|  ";
	}
	cout << root->key << endl;

	printTree(root->left, indent, false);
	printTree(root->right, indent, true);
}

// TEST
int main() {
	Node* root = NULL;
	root = insertNode(root, 10);
	root = insertNode(root, 20);
	root = insertNode(root, 30);
	root = insertNode(root, 40);
	root = insertNode(root, 50);
	root = insertNode(root, 60);
	root = insertNode(root, 25);
	root = insertNode(root, 2);
	root = insertNode(root, 12);

	cout << "AVL Tree: " << endl;

	// Pre-order, In-order, Post-order and Level-order
	cout << "Pre-order: ";
	NLR(root);
	cout << endl;
	cout << "In-order: ";
	LNR(root);
	cout << endl;
	cout << "Post-order: ";
	LRN(root);
	cout << endl;
	cout << "Level-order: ";
	levelOrder(root);
	cout << endl;
	printTree(root);
	cout << endl;

	// Search for node 25
	if (searchNode(root, 25) != NULL) {
		cout << "Node 25 found." << endl;
	}
	else {
		cout << "Node 25 not found." << endl;
	}

	root = deleteNode(root, 40);
	root = deleteNode(root, 25);
	cout << "AVL Tree after deleting node 40 and 25: " << endl;
	cout << "Pre-order: ";
	NLR(root);
	cout << endl;
	printTree(root);
	cout << endl;

	// Check if the current tree is full, complete, perfect
	cout << "Is Full: " << isFull(root) << endl;
	cout << "Is Complete: " << isComplete(root) << endl;
	cout << "Is Perfect: " << isPerfect(root) << endl;
	cout << "Least Common Ancestor of 60 and 12: " << findCommonAncestor(root, 60, 12) << endl;
	cout << "Special Nodes: ";
	printSpecialNodes(root);
	cout << endl;

	return 0;
}