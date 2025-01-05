#include <iostream>
#include <cmath>
#include <climits>
using namespace std;

struct Heap {
	int* arr;
	int capacity;
	int size;
	Heap(int capacity);
};

Heap::Heap(int capacity) {
	this->capacity = capacity;
	this->size = 0;
	this->arr = new int[capacity];
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

// Insert a new value into the Min-Heap while maintaining the Min-Heap property.
void insert(Heap* heap, int value) {
	if (heap->arr == NULL) {
		cout << "Heap is not initialized!" << endl;
		return;
	}
	if (heap->size == heap->capacity) {
		cout << "Heap is full!" << endl;
		return;
	}

	int i = heap->size;
	heap->arr[i] = value;
	heap->size++;

	int parent = (i - 1) / 2;
	while (i != 0 && heap->arr[parent] > heap->arr[i]) {
		swap(heap->arr[parent], heap->arr[i]);
		i = parent;
		parent = (i - 1) / 2;
	}
}

// Heapify the subtree rooted at a given index to maintain the Min-Heap property.
void heapify(Heap* heap, int index) {
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int minValue = index;

	if (left < heap->size && heap->arr[left] < heap->arr[minValue]) {
		minValue = left;
	}
	if (right < heap->size && heap->arr[right] < heap->arr[minValue]) {
		minValue = right;
	}

	if (minValue != index) {
		swap(heap->arr[index], heap->arr[minValue]);
		heapify(heap, minValue);
	}
}

/*
Extract the minimum value (the root) from the Min-Heap and adjust the structure to
maintain the Min-Heap property.
*/
int extractMin(Heap* heap) {
	if (heap->arr == NULL) {
		cout << "Heap is not initialized!" << endl;
		return -1;
	}
	if (heap->size == 0) {
		cout << "Heap is empty!" << endl;
		return -1;
	}
	if (heap->size == 1) {
		heap->size--;
		return heap->arr[0];
	}

	int minValue = heap->arr[0];
	heap->arr[0] = heap->arr[heap->size - 1];
	heap->size--;
	heapify(heap, 0);

	return minValue;
}

// Get the minimum value (the root) of the Min-Heap without removing it.
int getMin(Heap* heap) {
	if (heap->arr == NULL) {
		cout << "Heap is not initialized!" << endl;
		return -1;
	}
	if (heap->size == 0) {
		cout << "Heap is empty!" << endl;
		return -1;
	}
	return heap->arr[0];
}

// Delete a specific key from the Min-Heap and maintain the Min-Heap property.
void deleteKey(Heap* heap, int index) {
	if (heap->arr == NULL) {
		cout << "Heap is not initialized!" << endl;
		return;
	}
	if (index >= heap->size) {
		cout << "Index larger than heap size!" << endl;
		return;
	}
	heap->arr[index] = INT_MIN;
	int i = index;
	int parent = (i - 1) / 2;

	// Move the key to the root of the heap
	while (i != 0 && heap->arr[parent] > heap->arr[i]) {
		swap(heap->arr[parent], heap->arr[i]);
		i = parent;
		parent = (i - 1) / 2;
	}
	extractMin(heap);
}

/*
--------------------- Additional Operations and Properties ---------------------
*/ 

int countNodes(Heap* heap) {
	if (heap->arr == NULL) {
		cout << "Heap is not initialized!" << endl;
		return -1;
	}
	if (heap->size == 0) {
		cout << "Heap is empty!" << endl;
		return -1;
	}
	return heap->size;
}

int height(Heap* heap) {
	if (heap->arr == NULL) {
		cout << "Heap is not initialized!" << endl;
		return -1;
	}
	if (heap->size == 0) {
		cout << "Heap is empty!" << endl;
		return -1;
	}
	return (int)log2(heap->size);
}

void printLevelOrder(Heap* heap) {
	if (heap->arr == NULL) {
		cout << "Heap is not initialized!" << endl;
		return;
	}
	if (heap->size == 0) {
		cout << "Heap is empty" << endl;
		return;
	}
	for (int i = 0; i < heap->size; i++) {
		cout << heap->arr[i] << " ";
	}
	cout << endl;
}

void heapSort(Heap* heap) {
	if (heap->arr == NULL) {
		cout << "Heap is not initialized!" << endl;
		return;
	}
	if (heap->size == 0) {
		cout << "Heap is empty" << endl;
		return;
	}

	int n = heap->size;
	int* sortedArr = new int[n];
	for (int i = 0; i < n; i++) {
		sortedArr[i] = extractMin(heap);
	}

	// Copy sorted array back to heap
	for (int i = 0; i < n; i++) {
		heap->arr[i] = sortedArr[i];
	}

	// Restore the heap size
	heap->size = n;

	delete[] sortedArr;	
}

int main() {
	// Initialize an empty Min-Heap with a capacity of 10.
	Heap* heap = new Heap(10);

	// Insert the following values into the Min-Heap: 20, 15, 30, 10, 8, 25.
	insert(heap, 20);
	insert(heap, 15);
	insert(heap, 30);
	insert(heap, 10);
	insert(heap, 8);
	insert(heap, 25);

	// Extract the minimum value from the Min-Heap.
	cout << "Min value: " << extractMin(heap) << endl;

	// Print the Min-Heap level by level.
	cout << "Level order traversal: ";
	printLevelOrder(heap);

	// Heapsort the Min-Heap.
	heapSort(heap);
	cout << "Sorted list: ";
	printLevelOrder(heap);

	// Delete the Min-Heap.
	delete[] heap->arr;
	delete heap;

	return 0;
}