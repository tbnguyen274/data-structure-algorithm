#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Queue {
	Node* front;
	Node* rear;
};

/*
Utilize the Linked List above, implement the following Queue operations:
1. enqueue: enqueue a new item into queue.
2. dequeue: dequeue the front item from the queue.
3. front: get the value of the front item.
*/

void enqueue(Queue*& q, Node* node) {
	if (node == NULL)
		return;

	if (q->front == NULL) {
		q->front = node;
		q->rear = node;
	}
	else {
		q->rear->next = node;
		q->rear = node;
	}
}

void dequeue(Queue*& q) {
	if (q->front == NULL)
		return;

	if (q->front == q->rear) {
		delete q->front;
		q->front = NULL;
		q->rear = NULL;
		return;
	}

	Node* temp = q->front;
	q->front = q->front->next;
	temp->next = NULL;
	delete temp;
}

int front(Queue* q) {
	if (q->front == NULL)
		return -1;

	return q->front->data;
}

Node* createNode(int data) {
	Node* p = new Node;
	p->data = data;
	p->next = NULL;
	return p;
}

Queue* createQueue() {
	Queue* q = new Queue;
	q->front = NULL;
	q->rear = NULL;
	return q;
}

void deleteQueue(Queue*& q) {
	if (q->front == NULL)
		return;

	while (q->front != NULL) {
		dequeue(q);
	}
	delete q;
	q = NULL;
}

int main() {
	// Test
	Queue* q = createQueue();

	enqueue(q, createNode(1));
	enqueue(q, createNode(2));
	enqueue(q, createNode(3));

	cout << front(q) << endl;
	dequeue(q);
	cout << front(q) << endl;
	dequeue(q);
	cout << front(q) << endl;
	dequeue(q);
	cout << front(q) << endl;

	deleteQueue(q);

	return 0;
}