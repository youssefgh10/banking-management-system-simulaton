#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
#include "transaction.h"

struct Node1 {
	transaction data;
	Node1* next;
};
struct List1 {
	Node1* head;
	int size;
};

#endif 
