#ifndef QUEUEARRAY_H
#define QUEUEARRAY_H
#include "loanrequest.h"
constexpr int Max1 = 100;
struct Queue {
	Loanrequest elements[Max1 + 1];
	int Front; 
	int Tail; 
};
#endif
