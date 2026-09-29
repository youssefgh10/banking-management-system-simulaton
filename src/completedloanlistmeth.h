#ifndef COMPLETEDLOANLISTMETH_H
#define COMPLETEDLOANLISTMETH_H
#include "completedloanlist.h"
CompletedLoanNode* createNode2(loan value);
void destroyNode2(CompletedLoanNode* Node);
CompletedLoanList createList2();
void destroyList2(struct CompletedLoanList* L);
bool isEmpty2(const CompletedLoanList& L);
bool isFull2(const CompletedLoanList& L);
int listSize2(const CompletedLoanList& L);
int insert2(CompletedLoanList* L, loan e, int pos);
int removeAt2(CompletedLoanList* L, int pos);
loan getElement2(const CompletedLoanList& L, int pos);
void displayList2(const CompletedLoanList& L);
CompletedLoanList CopyList2(const CompletedLoanList& L);
bool CompareLists2(const CompletedLoanList& L1, const CompletedLoanList& L2);
#endif
