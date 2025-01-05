#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

struct LinkedList
{
	Node* head;
	Node* tail;
};

Node* createNode(int data) {
	Node* p = new Node;
	p->data = data;
	p->next = NULL;
	return p;
}

LinkedList* createLinkedList() {
	LinkedList* list = new LinkedList;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void traversalNodes(LinkedList* list) {
	if (list->head == NULL)
		return;
	Node* p = list->head;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
}

int countNodes(LinkedList* list) {
	if (list->head == NULL)
		return 0;
	int count = 0;
	Node* p = list->head;
	while (p != NULL) {
		count++;
		p = p->next;
	}
	return count;
}

void addHead(LinkedList* list, Node* p) {
	if (p == NULL)
		return;
	if (list->head == NULL)	{
		list->head = p;
		list->tail = p;
		return;
	}
	p->next = list->head;
	list->head = p;
}

void addTail(LinkedList* list, Node* p) {
	if (p == NULL)
		return;
	if (list->head == NULL) {
		list->head = p;
		list->tail = p;
	}
	else {
		list->tail->next = p;
		list->tail = p;
	}
}

void removeHead(LinkedList* list) {
	if (list->head == NULL)
		return;

	if (list->head == list->tail) {
		delete list->head;
		list->head = NULL;
		list->tail = NULL;
		return;
	}

	Node* p = list->head;
	list->head = list->head->next;
	p->next = NULL;
	delete p;
}

void removeTail(LinkedList* list) {
	if (list->head == NULL)
		return;

	if (list->head == list->tail) {
		delete list->head;
		list->head = NULL;
		list->tail = NULL;
		return;
	}

	Node* p = list->head;
	while (p->next != list->tail) {
		p = p->next;
	}
	delete list->tail;
	list->tail = p;
	list->tail->next = NULL;
}

void deleteList(LinkedList*& list) {
	if (list->head == NULL)
		return;
	while (list->head != NULL) {
		removeHead(list);
	}
	delete list;
	list = NULL;
}

int main() {
	// Test
	LinkedList* list = createLinkedList();

	addHead(list, createNode(1));
	addHead(list, createNode(2));
	addHead(list, createNode(3));
	addHead(list, createNode(4));
	addHead(list, createNode(5));
	addTail(list, createNode(6));
	addTail(list, createNode(7));

	traversalNodes(list);
	cout << endl;
	cout << "Number of nodes: " << countNodes(list) << endl;

	cout << "Remove the head node of the linked list" << endl;
	removeHead(list);
	traversalNodes(list);
	cout << endl;
	cout << "Number of nodes: " << countNodes(list) << endl;

	cout << "Remove the head node of the linked list" << endl;
	removeHead(list);
	traversalNodes(list);
	cout << endl;
	cout << "Number of nodes: " << countNodes(list) << endl;

	cout << "Remove the tail node of the linked list" << endl;
	removeTail(list);
	traversalNodes(list);
	cout << endl;
	cout << "Number of nodes: " << countNodes(list) << endl;

	cout << "Remove the tail node of the linked list" << endl;
	removeTail(list);
	traversalNodes(list);
	cout << endl;
	cout << "Number of nodes: " << countNodes(list) << endl;

	deleteList(list);
	return 0;

}