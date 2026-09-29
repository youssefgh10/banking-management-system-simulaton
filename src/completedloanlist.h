#ifndef COMPLETEDLOANLIST_H
#define COMPLETEDLOANLIST_H
#include "loan.h"
struct CompletedLoanNode {
	loan data;
	CompletedLoanNode* next;
};
struct CompletedLoanList {
	CompletedLoanNode* head;
	int size;
};
#endif 