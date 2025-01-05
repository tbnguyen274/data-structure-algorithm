#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Stack {
	Node* top;
};

/*
Utilize the Linked List above, implement the following Stack operations:
1. push: push a new item into stack.
2. pop: pop the top item from the stack.
3. top: get the value of the top item.
*/

void push(Stack*& s, Node* p) {
	if (p == NULL)
		return;
	if (s->top == NULL)	{
		s->top = p;
		return;
	}
	p->next = s->top;
	s->top = p;
}

void pop(Stack*& s) {
	if (s->top == NULL)
		return;
	Node* temp = s->top;
	s->top = s->top->next;
	temp->next = NULL;
	delete temp;
}

int top(Stack* s) {
	if (s->top == NULL)
		return -1;
	return s->top->data;
}

Node* createNode(int data) {
	Node* p = new Node;
	p->data = data;
	p->next = NULL;
	return p;
}

Stack* createStack() {
	Stack* s = new Stack;
	s->top = NULL;
	return s;
}

void deleteStack(Stack*& s) {
	while (s->top != NULL) {
		pop(s);
	}
	delete s;
}

int main() {
	// Test
	Stack* s = createStack();

	push(s, createNode(1));
	push(s, createNode(2));
	push(s, createNode(3));

	cout << top(s) << endl;
	pop(s);
	cout << top(s) << endl;
	pop(s);
	cout << top(s) << endl;
	pop(s);
	cout << top(s) << endl;

	deleteStack(s);
	return 0;
}