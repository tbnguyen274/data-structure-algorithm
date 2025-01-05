#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct hashTable {

	// Attributes
	struct hashNode {
		string key;
		int value;
		hashNode* left;
		hashNode* right;	// AVL tree
		int height;
	};

	int capacity;
	vector<hashNode*> table;

	// Methods
	void createNode(hashNode*& node, string key, int value) {
		node = new hashNode();
		node->key = key;
		node->value = value;
		node->left = node->right = NULL;
		node->height = 1;
	}

	int getHeight(hashNode* root) {
		if (root == NULL) return 0;
		return root->height;
	}

	int getBalance(hashNode* root) {
		if (root == NULL) return 0;
		return getHeight(root->left) - getHeight(root->right);
	}

	int max(int a, int b) {
		return (a > b) ? a : b;
	}

	void updateHeight(hashNode* root) {
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	}

	hashNode* rotateRight(hashNode* root) {
		hashNode* newRoot = root->left;
		hashNode* temp = newRoot->right;

		newRoot->right = root;
		root->left = temp;

		updateHeight(root);
		updateHeight(newRoot);

		return newRoot;
	}

	hashNode* rotateLeft(hashNode* root) {
		hashNode* newRoot = root->right;
		hashNode* temp = newRoot->left;

		newRoot->left = root;
		root->right = temp;

		updateHeight(root);
		updateHeight(newRoot);

		return newRoot;
	}

	hashNode* insert(hashNode* root, string key, int value) {
		if (root == NULL) {
			createNode(root, key, value);
			return root;
		}

		if (key < root->key) {
			root->left = insert(root->left, key, value);
		}
		else if (key > root->key) {
			root->right = insert(root->right, key, value);
		}
		else {
			root->value = value;	// Key already exists, update the value
			return root;
		}

		updateHeight(root);

		int balance = getBalance(root);

		// Left Left Case
		if (balance > 1 && key < root->left->key) {
			return rotateRight(root);
		}

		// Right Right Case
		if (balance < -1 && key > root->right->key) {
			return rotateLeft(root);
		}

		// Left Right Case
		if (balance > 1 && key > root->left->key) {
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}

		// Right Left Case
		if (balance < -1 && key < root->right->key) {
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}

		return root;
	}

	hashNode* search(hashNode* root, string key) {
		if (root == NULL || root->key == key) return root;

		if (key < root->key) {
			return search(root->left, key);
		}
		else {
			return search(root->right, key);
		}
	}

	hashNode* deleteNode(hashNode* root, string key) {
		if (root == NULL) return root;

		if (key < root->key) {
			root->left = deleteNode(root->left, key);
		}
		else if (key > root->key) {
			root->right = deleteNode(root->right, key);
		}
		else {
			if (root->left == NULL || root->right == NULL) {
				hashNode* temp = root->left ? root->left : root->right;

				if (temp == NULL) {
					temp = root;
					root = NULL;
				}
				else {
					*root = *temp;
				}
				delete temp;
			}
			else {
				hashNode* temp = root->right;
				while (temp->left != NULL) {
					temp = temp->left;
				}

				root->key = temp->key;
				root->value = temp->value;
				root->right = deleteNode(root->right, temp->key);
			}
		}

		if (root == NULL) return root;

		updateHeight(root);

		int balance = getBalance(root);

		// Left Left Case
		if (balance > 1 && getBalance(root->left) >= 0) {
			return rotateRight(root);
		}

		// Left Right Case
		if (balance > 1 && getBalance(root->left) < 0) {
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}

		// Right Right Case
		if (balance < -1 && getBalance(root->right) <= 0) {
			return rotateLeft(root);
		}

		// Right Left Case
		if (balance < -1 && getBalance(root->right) > 0) {
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}

		return root;
	}

	void init(hashNode* node, string key, int value) {
		node->key = key;
		node->value = value;
		node->left = node->right = NULL;
	}

	void init(int capacity) {
		this->capacity = capacity;
		table.resize(capacity, NULL);
	}

	void release() {
		for (int i = 0; i < capacity; i++) {
			if (table[i] != NULL) {
				delete table[i];
				table[i] = NULL;
			}
		}
	}

	unsigned int hashFunction(string key) {
		int n = (int)key.length();
		int p = 31;
		const long long m = (long long)1e9 + 9;
		unsigned int hashValue = 0;

		for (int i = 0; i < n; i++) {
			hashValue = (hashValue + ((int)key[i] * (long long)pow(p, i)) % m) % m;
		}
		return hashValue % capacity;
	}

	void add(string key, int value) {
		unsigned int index = hashFunction(key);
		if (table[index] == NULL) {
			createNode(table[index], key, value);
		}
		else {
			table[index] = insert(table[index], key, value);
		}
	}

	int* searchValue(string key) {
		unsigned int index = hashFunction(key);
		hashNode* node = search(table[index], key);
		if (node != NULL) {
			return &node->value;
		}
		return NULL;
	}

	void removeKey(string key) {
		unsigned int index = hashFunction(key);
		table[index] = deleteNode(table[index], key);
	}
	
	void display(hashNode* root) {
		if (root != NULL) {
			display(root->left);
			cout << root->key << " - " << root->value << endl;
			display(root->right);
		}
	}

	void display() {
		for (int i = 0; i < capacity; i++) {
			if (table[i] != NULL) {
				cout << "Index " << i << ": " << endl;
				display(table[i]);
			}
		}
	}
};

int main() {
	hashTable ht;
	ht.init(11);

	// Add elements
	ht.add("one", 1);
	ht.add("two", 2);
	ht.add("three", 3);
	ht.add("four", 4);
	ht.add("five", 5);
	ht.add("six", 6);
	ht.add("seven", 7);
	ht.add("eight", 8);
	ht.add("nine", 9);
	ht.add("ten", 10);

	// update the value for 'two'
	ht.add("two", 22);


	// Search for elements
	int* value = ht.searchValue("two");
	if (value != NULL) {
		cout << "Value for 'two': " << *value << endl;
	}
	else {
		cout << "'two' not found" << endl;
	}

	value = ht.searchValue("four");
	if (value != NULL) {
		cout << "Value for 'four': " << *value << endl;
	}
	else {
		cout << "'four' not found" << endl;
	}


	// Remove an element
	ht.removeKey("one");

	// Search for the removed element
	value = ht.searchValue("one");
	if (value != NULL) {
		cout << "Value for 'one': " << *value << endl;
	}
	else {
		cout << "'one' not found" << endl;
	}


	// Add more elements to test rehashing
	ht.add("eleven", 11);
	ht.add("twelve", 12);

	// Search for new elements
	value = ht.searchValue("eleven");
	if (value != NULL) {
		cout << "Value for 'eleven': " << *value << endl;
	}
	else {
		cout << "'eleven' not found" << endl;
	}

	value = ht.searchValue("twelve");
	if (value != NULL) {
		cout << "Value for 'twelve': " << *value << endl;
	}
	else {
		cout << "'twelve' not found" << endl;
	}


	// Test searching for a non-existent key
	value = ht.searchValue("thirteen");
	if (value != NULL) {
		cout << "Value for 'thirteen': " << *value << endl;
	}
	else {
		cout << "'thirteen' not found" << endl;
	}

	// Test removing a non-existent key
	ht.removeKey("thirteen");

	// Test removing and re-adding elements
	ht.removeKey("two");
	ht.add("two", 222);

	value = ht.searchValue("two");
	if (value != NULL) {
		cout << "Value for 'two': " << *value << endl;
	}
	else {
		cout << "'two' not found" << endl;
	}


	// Release memory
	ht.release();

	return 0;
}