

#include <iostream>
#include "QueueMethods.h"

using namespace std;


// ======================================================
// CREATE QUEUE
// ======================================================
Queue* CreateQueue() {

    Queue* Q = new (nothrow) Queue;

    if (!Q) {
        cout << RED << "\n[ERROR] Unable to allocate memory for queue!\n" << RESET;
    }
    else {
        Q->Front = 0;
        Q->Tail = 0;
        cout << GREEN << "[SUCCESS] Queue created.\n" << RESET;
    }
    return Q;
}


// ======================================================
// DESTROY QUEUE
// ======================================================
void DestroyQueue(Queue* Q) {
    delete Q;
    cout << BLUE << "[INFO] Queue destroyed and memory freed.\n" << RESET;
}



// ======================================================
// DISPLAY QUEUE
// ======================================================
void DisplayQueue(const Queue& Q) {

    if (IsEmpty(Q)) {
        cout << RED << "\n[Queue is empty]\n" << RESET;
        return;
    }

    cout << CYAN << "\n===== LOAN REQUEST QUEUE =====\n" << RESET;

    for (int i = Q.Front; i <= Q.Tail; i++) {

        const Loanrequest& L = Q.elements[i];

        cout << MAGENTA << "\n----------------------------------------\n" << RESET;

        cout << WHITE << "Request ID:        " << YELLOW << L.requestID << RESET << "\n";
        cout << WHITE << "Account Number:    " << YELLOW << L.accountNumber << RESET << "\n";
        cout << WHITE << "Customer Name:     " << L.customerName << "\n";
        cout << WHITE << "Loan Type:         " << L.loanType << "\n";
        cout << WHITE << "Requested Amount:  " << YELLOW << L.requestedAmount << RESET << "\n";
        cout << WHITE << "Request Date:      " << L.requestDate << "\n";
        cout << WHITE << "Status:            " << GREEN << L.status << RESET << "\n";
        cout << WHITE << "Duration (Years):  " << YELLOW << L.durationYears << RESET << "\n";
    }

    cout << MAGENTA << "\n----------------------------------------\n" << RESET;
}



// ======================================================
// CHECK EMPTY
// ======================================================
bool IsEmpty(const Queue& Q) {
    return (Q.Front == 0);
}


// ======================================================
// CHECK FULL
// ======================================================
bool IsFull(const Queue& Q) {
    return (Q.Tail == Max1);
}



// ======================================================
// GET SIZE
// ======================================================
int QueueSize(const Queue& Q) {
    if (IsEmpty(Q)) return 0;
    return Q.Tail - Q.Front + 1;
}



// ======================================================
// ENQUEUE
// ======================================================
Loanrequest Enqueue(Queue* Q, Loanrequest e, bool silent) { // silent hedheya tkhalina ken nhotou true maach fama couts
    if (IsFull(*Q) && Q->Front > 1) {
        const int count = QueueSize(*Q);
        for (int i = 0; i < count; ++i) Q->elements[i + 1] = Q->elements[Q->Front + i];
        Q->Front = 1;
        Q->Tail = count;
    }
    if (IsFull(*Q)) {
		if (!silent)
        cout << RED << "\n[ERROR] Queue is full. Cannot enqueue.\n" << RESET;
        return {};
    }

    if (IsEmpty(*Q)) {
        Q->Front = 1;
        Q->Tail = 1;
    }
    else {
        Q->Tail++;
    }

    Q->elements[Q->Tail] = e;

	if (!silent)
    cout << GREEN << "[SUCCESS] Enqueued request ID "
        << YELLOW << e.requestID << RESET << "\n";

    return e;
}



// ======================================================
// DEQUEUE
// ======================================================
Loanrequest Dequeue(Queue* Q) {

    if (IsEmpty(*Q)) {
        cout << RED << "\n[ERROR] Queue is empty. Cannot dequeue.\n" << RESET;
        return {};
    }

    Loanrequest removed = Q->elements[Q->Front];

    if (Q->Front == Q->Tail) {
        Q->Front = 0;
        Q->Tail = 0;
    }
    else {
        Q->Front++;
    }

    cout << BLUE << "[INFO] Dequeued request ID "
        << YELLOW << removed.requestID << RESET << "\n";

    return removed;
}



// ======================================================
// FRONT ELEMENT
// ======================================================
Loanrequest FrontElement(const Queue& Q) {

    if (IsEmpty(Q)) {
        cout << RED << "\n[ERROR] Queue is empty.\n" << RESET;
        return {};
    }

    return Q.elements[Q.Front];
}



// ======================================================
// COPY QUEUE
// ======================================================
Queue* CopyQueue(const Queue& Q) {

    Queue* newQ = CreateQueue();

    for (int i = Q.Front; i != 0 && i <= Q.Tail; i++) {
        Enqueue(newQ, Q.elements[i],true);
    }

    cout << GREEN << "[SUCCESS] Queue copied.\n" << RESET;
    return newQ;
}



// ======================================================
// COMPARE QUEUES
// ======================================================
bool CompareQueues(const Queue& Q1, const Queue& Q2) {

    if (QueueSize(Q1) != QueueSize(Q2)) {
        return false;
    }

    int i1 = Q1.Front;
    int i2 = Q2.Front;

    while (i1 <= Q1.Tail && i2 <= Q2.Tail) {

        if (Q1.elements[i1].requestID != Q2.elements[i2].requestID)
            return false;

        i1++;
        i2++;
    }

    return true;
}


 

