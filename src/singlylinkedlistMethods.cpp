#include <iostream>
#include "singlylinkedListMethods.h"
#include <new>
using namespace std;



Node1* createNode3(transaction value) {
	Node1* node = new (nothrow) Node1{ value, nullptr };
	if (!node) {
		cerr << "\nMemory allocation failed for node\n";
	}
	return node;
}void destroyNode3(Node1* node) {
	delete node;
}bool isEmpty3(const List1& L) {
	return L.size == 0;
}int listSize3(const List1& L) {
	return L.size;
}bool isFull3(const List1& L) {
	Node1* test = new (nothrow) Node1;
	if (!test) return true;
	delete test;
	return false;
}int insert3(List1* L, transaction e, int pos) {
	if (!L) return 0;
	if (pos < 1 || pos > L->size + 1) {
		cerr << "\nInvalid position";
		return 0;
	}
	Node1* n = createNode3(e);
	if (!n) return 0;
	if (pos == 1) {
		n->next = L->head;
		L->head = n;
	}	else {
		Node1* prev = nullptr;
		Node1* current = L->head;
		for (int i = 1; i < pos; i++) {
			prev = current;
			current = current->next;
		}
		prev->next = n;
		n->next = current;
	}
	L->size++;
	return 1;
}int insertAtEnd3(List1* L, const transaction& e) {
	return insert3(L, e, L->size + 1);
}int removeAt3(List1* L, int pos) {
	if (!L || isEmpty3(*L)) {
		cerr << "\nList is empty";
		return 0;
	}
	if (pos < 1 || pos > L->size) {
		cerr << "\nInvalid position";
		return 0;
	}
	Node1* prev = nullptr;
	Node1* current = L->head;	if (pos == 1) {
		L->head = current->next;
	}
	else {
		for (int i = 1; i < pos; i++) {
			prev = current;
			current = current->next;
		}
		prev->next = current->next;
	}
	destroyNode3(current);
	L->size--;
	return 1;
}transaction getElement3(const List1& L, int pos) {
	if (isEmpty3(L)) {
		cerr << "\nList is empty\n";
		return {};
	}
	if (pos < 1 || pos > L.size) {
		cerr << "\nInvalid position\n";
		return {};
	}	Node1* current = L.head;
	for (int i = 1; i < pos; i++) {
		current = current->next;
	}
	return current->data;
}List1 createList3() {
	return List1{ nullptr, 0 };
}void destroyList3(List1* L) {
	if (!L) return;
	Node1* current = L->head;
	while (current) {
		Node1* temp = current;
		current = current->next;
		destroyNode3(temp);
	}
	L->head = nullptr;
	L->size = 0;}void displayList3(const List1& L) {
	if (L.head == nullptr) {
		cout << "List is empty\n";
		return;
	}

	Node1* current = L.head;
	while (current != nullptr) {
		cout << "[ID: " << current->data.transactionID
			<< ", Acc: " << current->data.accountnumber
			<< ", Type: " << current->data.type
			<< ", Amount: " << current->data.amount
			<< ", Date: " << current->data.Date
			<< "] -> ";
		current = current->next;
	}
	cout << "NULL\n";
}List1 CopyList3(const List1& L) {
	List1 newList = createList3();
	Node1* current = L.head;
	Node1* tail = nullptr;
	while (current) {
		Node1* n = createNode3(current->data);
		if (!n) {
			cerr << "\nMemory allocation failed while copying\n";
			destroyList3(&newList);
			return createList3();		}		if (!newList.head) {
			newList.head = n;
			tail = n;
		}
		else {
			tail->next = n;
			tail = n;
		}
		current = current->next;
	}
	newList.size = L.size;
	return newList;
}bool CompareLists3(const List1& L1, const List1& L2) {
	if (L1.size != L2.size) return false;
	Node1* p1 = L1.head;
	Node1* p2 = L2.head;
	while (p1) {
		if (p1->data.transactionID != p2->data.transactionID) return false;
		p1 = p1->next;
		p2 = p2->next;
	}
	return true;
}