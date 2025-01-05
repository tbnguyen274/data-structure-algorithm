#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
};

/*
EXERCISE 1
*/

// Create a new Node from a given value.
Node* newNode(int data) {
	Node* temp = new Node;
	temp->key = data;
	temp->left = temp->right = NULL;
	return temp;
}

// Insert a new value into a Binary Search Tree.
Node* insert(Node* root, int data) {
	if (root == NULL) {
		return newNode(data);
	}
	if (data < root->key) {
		root->left = insert(root->left, data);
	}
	else if (data > root->key) {
		root->right = insert(root->right, data);
	}
	return root;
}

// Search a Node with a given value from a Binary Search Tree.
Node* search(Node* root, int data) {
	if (root == NULL || root->key == data)
		return root;

	if (data < root->key) {
		return search(root->left, data);
	}

	return search(root->right, data);
}

// Delete a Node with a given value from a Binary Search Tree.
Node* deleteNode(Node* root, int data) {
	if (root == NULL)
		return NULL;

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

	return root;
}

// Traversal in Pre-order, In-order, Post-order and Level-order.
void NLR(Node* root) {
	if (root == NULL)
		return;
	cout << root->key << " ";
	NLR(root->left);
	NLR(root->right);
}

void LNR(Node* root) {
	if (root == NULL)
		return;
	LNR(root->left);
	cout << root->key << " ";
	LNR(root->right);
}

void LRN(Node* root) {
	if (root == NULL)
		return;
	LRN(root->left);
	LRN(root->right);
	cout << root->key << " ";
}

void levelOrder(Node* root) {
	if (root == NULL)
		return;
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

/*
EXERCISE 2
*/

// Calculate the height of a given Binary Search Tree.
int height(Node* root) {
	if (root == NULL)
		return 0;
	int leftHeight = height(root->left);
	int rightHeight = height(root->right);
	return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// Count the number of Nodes from a given Binary Search Tree.
int countNode(Node* root) {
	if (root == NULL)
		return 0;
	return countNode(root->left) + countNode(root->right) + 1;
}

// Calculate the total value of all Nodes from a given Binary Search Tree.
int sumNode(Node* root) {
	if (root == NULL)
		return 0;
	return sumNode(root->left) + sumNode(root->right) + root->key;
}

// Count the number of leaves from a given Binary Search Tree.
int countLeaf(Node* root) {
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;
	return countLeaf(root->left) + countLeaf(root->right);
}

// Count the number of Nodes from a given Binary Search Tree which key value is less than a given value.
int countLess(Node* root, int x) {
	if (root == NULL)
		return 0;
	if (root->key < x) {
		return countLess(root->left, x) + countLess(root->right, x) + 1;
	}
	return countLess(root->left, x) + countLess(root->right, x);
}

// Count the number of Nodes from a given Binary Search Tree which key value is greater than a given value.
int countGreater(Node* root, int x) {
	if (root == NULL)
		return 0;
	if (root->key > x) {
		return countGreater(root->left, x) + countGreater(root->right, x) + 1;
	}
	return countGreater(root->left, x) + countGreater(root->right, x);
}


int main() {
	// TEST

	// Initialize an empty BST Tree.
	Node* root = NULL;

	// Insert 8, 6, 5, 7, 10, 9.
	root = insert(root, 8);
	root = insert(root, 6);
	root = insert(root, 5);
	root = insert(root, 7);
	root = insert(root, 10);
	root = insert(root, 9);

	// Show the tree in Pre-order, In-order, Post-order.
	cout << "Pre-order: ";
	NLR(root);
	cout << endl;

	cout << "In-order: ";
	LNR(root);
	cout << endl;

	cout << "Post-order: ";
	LRN(root);
	cout << endl;

	// Remove 8. Show the tree in Level Order
	root = deleteNode(root, 8);
	cout << "Removed 8.\n";
	cout << "Level Order: ";
	levelOrder(root);
	cout << endl;

	// Solve the problems in Exercise 2. Test with x = 7 (if the problem requires key)
	int x = 7;
	cout << "Height: " << height(root) << endl;
	cout << "Count Node: " << countNode(root) << endl;
	cout << "Sum Node: " << sumNode(root) << endl;
	cout << "Count Leaf: " << countLeaf(root) << endl;
	cout << "Count Less: " << countLess(root, x) << endl;
	cout << "Count Greater: " << countGreater(root, x) << endl;

	return 0;
}