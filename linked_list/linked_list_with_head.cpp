#include <bits/stdc++.h>
using namespace std;

struct Node {
	int data;
	Node *next;
};
struct List {
	Node *head;
};
// typedef Node* List;
Node* createNode(int value) {
	Node *node = new Node;
	node -> data = value;
	node -> next = NULL;
	return node;
}
void createList(List &l) {
	l.head = NULL;
}
void addHead(List &l, Node *node) {
	if(l.head == NULL) {
		l.head = node;
	} else {
		node -> next = l.head;
		l.head = node;
	}
}
void addTail(List &l, Node *node) {
	if(l.head == NULL) {
		l.head = node;
	} else {
		Node *tmp = l.head;
		while(tmp -> next != NULL) {
			tmp = tmp -> next;
		}
		tmp -> next = node;
	}
}
void insertAfterQ(List &l, Node *q, Node *p) {
	if(q != NULL) {
		p -> next = q -> next;
		q -> next = p;
	} else {
		addHead(l, p);
	}
}
int removeHead(List &l, int &x) {
	if(l.head != NULL) {
		Node *node = l.head;
		x = node -> data;
		l.head = l.head -> next;
		delete node;
		return 1;
	}
	return 0;
}
int removerAferQ(List &l, Node *q, int &x) {
	if(q != NULL) {
		Node *node = q -> next;
		x = node -> data;
		q -> next = node -> next;
		delete node;
		return 1;
	}
	return 0;
}
Node *getNode(List &l, int index) {
	Node *node = l.head;
	int i = 0;
	while(node != NULL && i != index) {
		node = node -> next;
		i++;
	}
	if(node != NULL && i == index) {
		return node;
	}
	return NULL;
}
Node *search(List l, int x) {
	if(l.head != NULL) {
		Node *node = l.head;
		while(node != NULL && node -> data != x) {
			node = node -> next;
		} 
		if(node != NULL) {
			return node;
		}
		return NULL;
	}
}
int length(List l) {
	int x = 0;
	Node *node = l.head;
	while(node != NULL) {
		node = node -> next;
	}
	return x;
}
void destroyList(List &l) {
	int x;
	Node *node = l.head;
	while(node != NULL) {
		removeHead(l, x);
		node = l.head;
	}
}
void printList(List l) {
	Node *t = l.head;
	while(t != NULL) {
		cout << t -> data << ' ';
		t = t -> next;
	}
}
int main () {
	List l;
	createList(l);
	for(int i = 0; i < 10; i++) {
		addTail(l, createNode(i));
	}
	insertAfterQ(l, getNode(l, 2), createNode(100));
	printList(l);
	cout << '\n'; 
	int x;
	removerAferQ(l, getNode(l, 2), x);
	printList(l);
	return 0;
}