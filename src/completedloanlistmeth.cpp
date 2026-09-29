#include<iostream>
#include "completedloanlistmeth.h"
using namespace std;
CompletedLoanNode* createNode2(loan value) {
	CompletedLoanNode* node = new (nothrow) CompletedLoanNode{ value, nullptr };
	if (!node) {
		cerr << "\nMemory allocation failed for node\n";
	}
	return node;
}
void destroyNode2(CompletedLoanNode* node) {
	delete node;
}
bool isEmpty2(const CompletedLoanList& L) {
	return L.size == 0;
}
int listSize2(const CompletedLoanList& L) {
	return L.size;
}
bool isFull2(const CompletedLoanList& L) {
	CompletedLoanNode* test = new (nothrow) CompletedLoanNode;
	if (!test) return true;
	delete test;
	return false;
}
int insert2(CompletedLoanList* L, loan e, int pos) {
	if (!L) return 0;
	if (pos < 1 || pos > L->size + 1) {
		cerr << "\nInvalid position";
		return 0;
	}
	CompletedLoanNode* n = createNode2(e);
	if (!n) return 0;
	if (pos == 1) {
		n->next = L->head;
		L->head = n;
	}
	else {
		CompletedLoanNode* prev = nullptr;
		CompletedLoanNode* current = L->head;
		for (int i = 1; i < pos; i++) {
			prev = current;
			current = current->next;
		}
		prev->next = n;
		n->next = current;
	}

	L->size++;
	return 1;
}
int removeAt2(CompletedLoanList* L, int pos) {
	if (!L || isEmpty2(*L)) {
		cerr << "\nList is empty";
		return 0;
	}
	if (pos < 1 || pos > L->size) {
		cerr << "\nInvalid position";
		return 0;
	}
	CompletedLoanNode* prev = nullptr;
	CompletedLoanNode* current = L->head;
	if (pos == 1) {
		L->head = current->next;
	}
	else {
		for (int i = 1; i < pos; i++) {
			prev = current;
			current = current->next;
		}
		prev->next = current->next;
	}
	destroyNode2(current);
	L->size--;
	return 1;
}
loan getElement2(const CompletedLoanList& L, int pos) {
	if (isEmpty2(L)) {
		cerr << "\nList is empty\n";
		return {};
	}

	if (pos < 1 || pos > L.size) {
		cerr << "\nInvalid position\n";
		return {};
	}
	CompletedLoanNode* current = L.head;
	for (int i = 1; i < pos; i++) {
		current = current->next;
	}

	return current->data;
}
CompletedLoanList createList2() {
	return CompletedLoanList{ nullptr, 0 };
}
void destroyList2(CompletedLoanList* L) {
	if (!L) return;
	CompletedLoanNode* current = L->head;
	while (current) {
		CompletedLoanNode* temp = current;
		current = current->next;
		destroyNode2(temp);
	}
	L->head = nullptr;
	L->size = 0;
}
void displayList2(const CompletedLoanList& L) {
	if (isEmpty2(L)) {
		cout << "List is empty\n";
		return;
	}
	CompletedLoanNode* current = L.head;
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
CompletedLoanList CopyList2(const CompletedLoanList& L) {
	CompletedLoanList newList = createList2();
	CompletedLoanNode* current = L.head;
	CompletedLoanNode* tail = nullptr;

	while (current) {
		CompletedLoanNode* n = createNode2(current->data);
		if (!n) {

			cerr << "\nMemory allocation failed while copying\n";
			destroyList2(&newList);
			return createList2();
		}
		if (!newList.head) {
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
}
bool CompareLists2(const CompletedLoanList& L1, const CompletedLoanList& L2) {
	if (L1.size != L2.size) return false;

	CompletedLoanNode* p1 = L1.head;
	CompletedLoanNode* p2 = L2.head;

	while (p1) {
		if (p1->data.loanID != p2->data.loanID ||
			p1->data.loantype != p2->data.loantype ||
			p1->data.principalamount != p2->data.principalamount ||
			p1->data.interestrate != p2->data.interestrate ||
			p1->data.amountpaid != p2->data.amountpaid ||
			p1->data.remainingbalance != p2->data.remainingbalance ||
			p1->data.startdate != p2->data.startdate ||
			p1->data.enddate != p2->data.enddate ||
			p1->data.loanstatus != p2->data.loanstatus) return false;
		p1 = p1->next;
		p2 = p2->next;
	}
	return true;
}
