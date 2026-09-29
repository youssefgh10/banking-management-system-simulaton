#include <iostream>
#include "stackarraytrmeth.h"
using namespace std;
stack* createstack() {
	stack* S = new (nothrow) stack;
	if (!S) {
		cout << "\n Error: unable to allocate memory";
	}
	else {
		S->Top = 0;
	}
	return S;
}
bool isEmpty(const stack& S) {
	return S.Top == 0;
}
int stackSize(const stack& S) {
	return S.Top;
}
bool isFull(const stack& S) {
	return S.Top == Max;
}
void destroystack(stack* S) {
	delete S;
}
void displaystack(const stack& S) {
	for (int i = S.Top; i >= 1; i--) {
		cout << "----------------------------------------\n";
		cout <<"Transaction ID: "<<S.data[i].transactionID <<"\n";
		cout << "Account Number: " << S.data[i].accountnumber << "\n";
		cout << "Type: " << S.data[i].type << "\n";
		cout << "Amount: " << S.data[i].amount << "\n";
		cout << "Date: " << S.data[i].Date << "\n";
		cout << "----------------------------------------\n";
	}
	cout << endl;
}
stack* copystack(const stack& S) {
	stack* newstack = createstack();

	for (int i = 1; i <= S.Top; i++) {
		push(newstack, S.data[i]);
	}

	return newstack;
}
bool comparestack(const stack& S1, const stack& S2) {
	if (S1.Top != S2.Top) return false;
	for (int i = 0; i <= S1.Top; i++) {
		if (S1.data[i].transactionID != S2.data[i].transactionID
			|| S1.data[i].accountnumber != S2.data[i].accountnumber
			|| S1.data[i].type != S2.data[i].type
			|| S1.data[i].amount != S2.data[i].amount
			|| S1.data[i].Date != S2.data[i].Date) {
			return false;
		}
	}
	return true;
}
int push(stack* S, transaction e) {
	if (!S) {
		cerr << "Stack pointer is NULL\n";
		return -1;
	}
	if (S->Top >= Max - 1) {
		cerr << "Stack is full\n";
		return -1;
	}
	S->Top++;
	S->data[S->Top] = e;
	return 0;
}
transaction pop(stack* S) {
	if (!S) {
		cerr << "Stack pointer is NULL\n";
		return {};
	}
	if (S->Top == 0) {
		cerr << "Stack is empty\n";
		return {};
	}
	transaction element = S->data[S->Top];
	S->Top--;
	return element;
}

transaction top(const stack& S) {
	transaction e = {};

	if (isEmpty(S)) {
		cout << "\nStack is empty";
	}
	else {
		e = S.data[S.Top];
	}

	return e;
}
