#ifndef QUEUEMETHODS_H
#define QUEUEMETHODS_H
#include "QueueArray.h"

Queue* CreateQueue();
void DestroyQueue(Queue* Q);
void DisplayQueue(const Queue& Q);
bool IsEmpty(const Queue& Q);
bool IsFull(const Queue& Q);
int QueueSize(const Queue& Q);
Loanrequest Dequeue(Queue* Q);
Loanrequest Enqueue(Queue* Q, Loanrequest e, bool silent = false);
Loanrequest FrontElement(const Queue& Q);
Queue* CopyQueue(const Queue& Q);
bool CompareQueues(const Queue& Q1, const Queue& Q2);

#endif
