#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "loan.h"
struct Node {
	loan data;
	Node* next;
	Node* prev;
};
struct List {
	Node* head;
	Node* tail;
	int size;
};

#endif 
