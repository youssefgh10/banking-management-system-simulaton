#ifndef CUSTOMERMETHODS_H
#define CUSTOMERMETHODS_H
#include "customerarray.h"
#include "QueueMethods.h"
#include "completedloanlist.h"
#include "singlylinkedlist.h"

// Customer methods
int login(CustomerArray& customers);
void viewloans(customer& Customer);
void submitLoanRequest(customer& Customer, Queue* loanRequests);
void deposit(customer& Customer);
void withdrawMoney(customer& Customer);
void viewTransactions(const customer& Customer);
void undotransaction(customer& Customer);

// Utility functions;
string getCurrentDate();
int generateTransactionID();
int generateLoanID();
void initializeIds(const CustomerArray& customers, const Queue& requests,
    const CompletedLoanList& completedLoans, const List1& history);

#endif