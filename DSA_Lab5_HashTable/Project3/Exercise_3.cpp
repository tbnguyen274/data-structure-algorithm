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
		hashNode* next;
	};

	int capacity;
	vector<hashNode*> table;

	// Methods
	hashNode* createNode(string key, int value) {
		hashNode* node = new hashNode;
		node->key = key;
		node->value = value;
		node->next = NULL;
		return node;
	}

	void addTail(hashNode*& head, hashNode* newNode) {
		if (head == NULL) {
			head = newNode;
			return;
		}
		hashNode* cur = head;
		while (cur->next != NULL) {
			if (cur->key == newNode->key) {
				cur->value = newNode->value;	// Key already exists, update the value
				delete newNode;
				return;
			}
			cur = cur->next;
		}
		if (cur->key == newNode->key) {
			cur->value = newNode->value;		// Key already exists, update the value
			delete newNode;
			return;
		}
		cur->next = newNode;
	}

	hashNode* searchKey(hashNode* head, string key) {
		hashNode* cur = head;
		while (cur != NULL) {
			if (cur->key == key) {
				return cur;
			}
			cur = cur->next;
		}
		return NULL;
	}

	hashNode* deleteNode(hashNode* head, string key) {
		hashNode* cur = head;
		hashNode* prev = NULL;
		while (cur != NULL) {
			if (cur->key == key) {
				if (prev == NULL) {
					head = cur->next;
				}
				else {
					prev->next = cur->next;
				}
				delete cur;
				break;
			}
			prev = cur;
			cur = cur->next;
		}
		return head;
	}

	void init(int capacity) {
		this->capacity = capacity;
		table.resize(capacity, NULL);
	}

	void release() {
		for (int i = 0; i < capacity; i++) {
			hashNode* cur = table[i];
			while (cur != NULL) {
				hashNode* next = cur->next;
				delete cur;
				cur = next;
			}
			table[i] = NULL;
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
		hashNode* newNode = createNode(key, value);
		unsigned int index = hashFunction(key);
		addTail(table[index], newNode);
	}

	int* searchValue(string key) {
		unsigned int index = hashFunction(key);
		hashNode* target = searchKey(table[index], key);
		if (target != NULL) {
			return &target->value;
		}
		return NULL;
	}

	void removeKey(string key) {
		unsigned int index = hashFunction(key);
		table[index] = deleteNode(table[index], key);
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