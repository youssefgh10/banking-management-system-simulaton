#include "doublylinkedlist.h"
#include <iostream>
using namespace std;

Node* createNode(loan value) {
	Node* node = new (nothrow) Node{ value, nullptr,nullptr };
	if (!node) {
		cerr << "\nMemory allocation failed for node\n";
	}
	return node;
}
void destroyNode(Node* node) {
	delete node;
}
bool isEmpty(const List& L) {
	return L.size == 0;
}
int listSize(const List& L) {
	return L.size;
}
bool isFull(const List& L) {
	Node* test = new (nothrow) Node;
	if (!test) return true;
	delete test;
	return false;
}
int insert(List* L, loan e, int pos) {  // Should be 'loan', not 'int'
	if (!L) return 0;
	if (pos < 1 || pos > L->size + 1) {
		cout << "\nInvalid position";
		return 0;
	}
	Node* n = createNode(e);
	if (!n) return 0;

	if (isEmpty(*L)) {
		L->head = n;
		L->tail = n;
	}
	else if (pos == 1) {
		n->next = L->head;
		L->head->prev = n;
		L->head = n;
	}
	else if (pos == L->size + 1) {
		n->prev = L->tail;
		L->tail->next = n;
		L->tail = n;
	}
	else {
		Node* prev = nullptr;
		Node* current = L->head;
		for (int i = 1; i < pos; i++) {
			prev = current;
			current = current->next;
		}
		prev->next = n;
		n->prev = prev;
		n->next = current;
		current->prev = n;
	}

	L->size++;   
	return 1;    
}
int removeAt(List* L, int pos) {
	if (!L || isEmpty(*L)) {
		cout << "\nList is empty";
		return 0;
	}
	if (pos < 1 || pos > L->size) {
		cout << "\nInvalid position";
		return 0;
	}
	Node* current = nullptr;
	if (L->size == 1) {
		current = L->head;
		L->head = nullptr;
		L->tail = nullptr;
	}
	else if (pos == 1) {
		current = L->head;
		L->head = L->head->next;
		L->head->prev = nullptr;
	}
	else if (pos == L->size) {
		current = L->tail;
		L->tail = L->tail->prev;
		L->tail->next = nullptr;
	}
	else {
		Node* prevNode = nullptr;
		current = L->head;
		for (int i = 1; i < pos; i++) {
			prevNode = current;
			current = current->next;
		}
		current->next->prev = prevNode;
		prevNode->next = current->next;
	}
	destroyNode(current);  
	L->size--;             
	return 1; 
}
loan getElement(const List& L, int pos) {
	if (isEmpty(L)) {
		cerr << "\nList is empty\n";
		return {};
	}
	if (pos < 1 || pos > L.size) {
		cerr << "\nInvalid position\n";
		return {};
	}
	Node* current = L.head;
	for (int i = 1; i < pos; i++) {
		current = current->next;
	}
	return current->data;
}

List createList() {
	return List{ nullptr,nullptr,0 };
}
void destroyList(List* L) {
	if (!L) return;
	Node* current = L->head;
	while (current) {
		Node* temp = current;
		current = current->next;
		destroyNode(temp);
	}
	L->head = nullptr;
	L->size = 0;
}
void displayList(const List& L) {
	if (isEmpty(L)) {
		cout << "List is empty\n";
		return;
	}
	Node* current = L.head;
	while (current) {
		cout << "----------------------------------------\n";
		cout << "Loan ID: " << current->data.loanID << "\n";
		cout << "Loan Type: " << current->data.loantype << "\n";
		cout << "Principal Amount: " << current->data.principalamount << "\n";
		cout << "Interest Rate: " << current->data.interestrate << "%\n";
		cout << "Amount Paid: " << current->data.amountpaid << "\n";
		cout << "Remaining Balance: " << current->data.remainingbalance << "\n";
		cout << "Start Date: " << current->data.startdate << "\n";
		cout << "End Date: " << current->data.enddate << "\n";
		cout << "Loan Status: " << current->data.loanstatus << "\n";
		cout << "----------------------------------------\n";

		current = current->next;
	}

	cout << "END OF LIST\n";
}
List CopyList(const List& L) {
	List newList = createList();
	Node* current = L.head;
	Node* tail = nullptr;
	while (current) {
		Node* n = createNode(current->data);
		if (!n) {
			cerr << "\nMemory allocation failed while copying\n";
			destroyList(&newList);
			return createList();
		}
		if (!newList.head) {
			newList.head = n;
			tail = n;
		}
		else {
			n->prev = tail;      
			tail->next = n;
			tail = n;
		}
		current = current->next;
	}
	newList.tail = tail; 
	newList.size = L.size;
	return newList;
}
bool CompareLists(const List& L1, const List& L2) {
	if (L1.size != L2.size) return false;

	Node* p1 = L1.head;
	Node* p2 = L2.head;

	while (p1 != nullptr && p2 != nullptr) {
		const loan& a = p1->data;
		const loan& b = p2->data;

		if (a.loanID != b.loanID ||
			a.loantype != b.loantype ||
			a.principalamount != b.principalamount ||
			a.interestrate != b.interestrate ||
			a.amountpaid != b.amountpaid ||
			a.remainingbalance != b.remainingbalance ||
			a.startdate != b.startdate ||
			a.enddate != b.enddate ||
			a.loanstatus != b.loanstatus)
		{
			return false;
		}

		p1 = p1->next;
		p2 = p2->next;
	}

	return true;
}