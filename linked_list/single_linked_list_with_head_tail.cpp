#include <bits/stdc++.h>
using namespace std;

struct Node {
	int data;
	Node *next;
};
struct LinkedList{
	Node *head;
	Node *tail;
};

Node *createNode(int value) {
	Node *node = new Node;
	node -> data = value;
	node -> next = NULL;
	return node;
}
void createList(LinkedList &l) {
	l.head = NULL;
	l.tail = NULL;
}
void addHead(LinkedList &l, Node *node) {
	if(l.head == NULL) {
		l.head = node;
		l.tail = node;
	} else {
		node -> next = l.head;
		l.head = node;
	}
}
void addTail(LinkedList &l, Node *node) {
	if(l.head == NULL) {
		l.head = node;
		l.tail = node;
	} else {
		l.tail -> next = node;
		l.tail = node;
	}
}
void insertAfterQ(LinkedList &l, Node *p, Node *q) {
	if(q != NULL) {
		p -> next = q -> next;
		q -> next = p;
		if(l.tail == q) {
			l.tail = p;
		}
	} else {
		addHead(l, p);
	}
}
int removeHead(LinkedList &l, int &x) {
	if(l.head != NULL) {
		Node *node = l.head;
		x = node -> data;
		l.head = node  ->  next;
		delete node;
		if(l.head == NULL) {
			l.tail = NULL;
		}
		return 1;
	}
	return 0;
}
int removeAfterQ(LinkedList &l, Node *q, int &x) {
	if(q != NULL) {
		Node *p = q -> next;
		if(p != NULL) {
			if(l.tail == p) {
				l.tail = q;
			}
			q -> next = p -> next;
			x = p -> data;
			delete p;
			return 1;
		}
		return 0;
	}
	return 0;
}
Node *getNode(LinkedList &l, int index) {
	Node *node = l.head;
	int i = 0;
	while(node != NULL && i != index) {
		node = node -> next;
		i++;
	}
	if(i == index && node != NULL) {
		return node;
	}
	return NULL;
}
void printList(LinkedList &l) {
	if(l.head != NULL) {
		Node *node = l.head;
		while(node != NULL) {
			cout << node -> data << " ";
			node = node -> next;
		}
	}
}

Node *search(LinkedList l, int x) {
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
int length(LinkedList l) {
	int x = 0;
	Node *node = l.head;
	while(node != NULL) {
		x++;
		node = node -> next;
	}
	return x;
}
void destroyList(LinkedList &l) {
	int x;
	Node *node = l.head;
	while(node != NULL) {
		removeHead(l, x);
		node = l.head;
	}
	l.tail = NULL;
}
int main () {
	LinkedList list;
	createList(list);
	Node* node;
	for (auto i = 1; i <= 10; i++){
		node = createNode(i);
		addTail(list, node);
	}
	printList(list);
	cout << '\n';
	int len = length(list);
	cout << "Length of list: " << len << '\n';
	Node* nodeAtIdx7 = getNode(list, 7);
	if (nodeAtIdx7 != NULL)
		cout << "Data at node have idx 7: " << nodeAtIdx7 -> data << '\n';
	Node* search4InList = search(list, 4);
	if (search4InList != NULL)
		cout << "4 was founded" << '\n';
	else
		cout << "4 not Found" << '\n';
	int x;
	int res = removeAfterQ(list, search4InList, x);
	if (res){
		cout << "Data of node has been removed: " << x << '\n';
		cout << "List after removed: ";
		printList(list);
		cout << '\n';
	}
	else
		cout << "Nothing is removed" << '\n';
	Node* node2409 = createNode(2409);
	insertAfterQ(list, node2409, search4InList);
	cout << "List after insert 2409 after 4: ";
	printList(list);
	cout << '\n';
	res = removeHead(list, x);
	if (res){
		cout << "Data of node has been removed: " << x << '\n';
		cout << "List after removed head: ";
		printList(list);
		cout << '\n';
	}
	else
		cout << "Nothing is removed" << '\n';
	destroyList(list);
	return 0;
}