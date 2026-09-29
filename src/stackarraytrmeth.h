#ifndef STACKARRAYTRMETH_H
#define STACKARRAYTRMETH_H
#include "stackarraytr.h"
stack* createstack();
void destroystack(stack* S);
bool isEmpty(const stack& S);
bool isFull(const stack& S);
int stackSize(const stack& S);
void displaystack(const stack& S);
stack* copystack(const stack& S);
bool comparestack(const stack& S1, const stack& S2);
int push(stack* S, transaction e);
transaction pop(stack* S);
transaction top(const stack& S);

#endif

