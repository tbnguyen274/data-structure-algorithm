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
	};

	int capacity;
	vector<hashNode*> table;

	// Methods
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

	bool isPrime(int n) {
		if (n <= 1) return false;
		for (int i = 2; i * i <= n; i++) {
			if (n % i == 0) {
				return false;
			}
		}
		return true;
	}

	unsigned int hashFunctionSecondary(string key) {
		int prime = capacity - 1;
		while (!isPrime(prime)) {
			prime--;
		}
		if (prime == 0) prime = 1;
		unsigned int res = hashFunction(key) % prime;
		return (res != 0) ? res : (prime - res);
	}

	bool isFull() {
		for (int i = 0; i < capacity; i++) {
			if (table[i] == NULL) {
				return false;
			}
		}
		return true;
	}

	void add(string key, int value) {
		if (isFull()) {
			cout << "Table is full!" << endl;
			return;
		}

		unsigned int index = hashFunction(key);
		unsigned int offset = hashFunctionSecondary(key);
		unsigned int originalIndex = index;
		int i = 0;

		while (table[index] != NULL) {
			if (table[index]->key == key) {
				table[index]->value = value;	// Key already exists, update the value
				return;
			}
			i++;
			index = (originalIndex + i * offset) % capacity;

			if (i >= capacity) {	// Hash function cannot find an empty slot
				cout << "Cannot find an empty slot for: " << key << "!" << endl;
				return;
			}
		}

		hashNode* newNode = new hashNode{ key, value };
		table[index] = newNode;
	}

	int* searchValue(string key) {
		unsigned int index = hashFunction(key);
		unsigned int offset = hashFunctionSecondary(key);
		unsigned int originalIndex = index;
		int i = 0;

		while (table[index] != NULL) {
			if (table[index]->key == key) {
				return &table[index]->value;
			}

			i++;
			index = (originalIndex + i * offset) % capacity;

			if (i >= capacity) {
				break;
			}
		}

		return NULL;
	}

	void removeKey(string key) {
		unsigned int index = hashFunction(key);
		unsigned int offset = hashFunctionSecondary(key);
		unsigned int originalIndex = index;
		int i = 0;

		while (table[index] != NULL) {
			if (table[index]->key == key) {
				delete table[index];
				table[index] = NULL;

				// Rehash to fill the empty slot
				i++;
				unsigned int nextIndex = (originalIndex + i * offset) % capacity;
				while (table[nextIndex] != NULL) {
					hashNode* node = table[nextIndex];
					table[nextIndex] = NULL;
					add(node->key, node->value);
					delete node;
					i++;
					nextIndex = (originalIndex + i * offset) % capacity;
				}
				return;
			}

			i++;
			index = (originalIndex + i * offset) % capacity;

			if (i >= capacity) {
				break;
			}
		}
		// out of loop, key not found
		cout << "Key: " << key << " not found to be removed!" << endl;
	}

	void display() {
		for (int i = 0; i < capacity; i++) {
			if (table[i] != NULL) {
				cout << "Index " << i << ": " << table[i]->key << " - " << table[i]->value << endl;
			}
		}
	}
};

int main() {
    hashTable ht;
    ht.init(17);

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
    } else {
        cout << "'two' not found" << endl;
    }

    value = ht.searchValue("four");
    if (value != NULL) {
        cout << "Value for 'four': " << *value << endl;
    } else {
        cout << "'four' not found" << endl;
    }


    // Remove an element
    ht.removeKey("one");

    // Search for the removed element
    value = ht.searchValue("one");
    if (value != NULL) {
        cout << "Value for 'one': " << *value << endl;
    } else {
        cout << "'one' not found" << endl;
    }


    // Add more elements to test rehashing
    ht.add("eleven", 11);
    ht.add("twelve", 12);

    // Search for new elements
    value = ht.searchValue("eleven");
    if (value != NULL) {
        cout << "Value for 'eleven': " << *value << endl;
    } else {
        cout << "'eleven' not found" << endl;
    }

    value = ht.searchValue("twelve");
    if (value != NULL) {
        cout << "Value for 'twelve': " << *value << endl;
    } else {
        cout << "'twelve' not found" << endl;
    }


    // Test searching for a non-existent key
    value = ht.searchValue("thirteen");
    if (value != NULL) {
        cout << "Value for 'thirteen': " << *value << endl;
    } else {
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
    } else {
        cout << "'two' not found" << endl;
    }


    // Release memory
    ht.release();

    return 0;
}