#ifndef STACKARRAYTR_H
#define STACKARRAYTR_H
#include "transaction.h"
constexpr int Max = 100;
struct stack {
	transaction data[Max];
	int Top;
};
#endif