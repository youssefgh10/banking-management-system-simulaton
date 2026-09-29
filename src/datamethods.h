#ifndef DATAMETHODS_H
#define DATAMETHODS_H
#include "customerMethods.h"
#include "EmployeeMethods.h"
#include "QueueMethods.h" 
#include "completedloanlistmeth.h"
#include <fstream> //containing open and read files functions
#include <sstream> //It lets you treat a string like a file - you can read from it piece by piece.

// Load functions (nestaamlohom mech c++ yakra data mel files)
void loadCustomers(CustomerArray& customers);
void loadLoans(CustomerArray& customers);
void loadEmployees(EmployeeArray& employees);
void loadTransactions(CustomerArray& customers);         
void loadLoanRequests(Queue& loanRequestQueue);            
void loadArchivedCustomers(CustomerArray& archivedCustomers);
void loadCompletedLoans(CompletedLoanList& completedLoans);
void loadTransactionHistory(List1& transactionHistory);
// Save functions (nestaamlohom mech c++ ibadel el files ki nzidou hajet okhra)
void saveCustomers(const CustomerArray& customers);
void saveLoans(const CustomerArray& customers);
void saveEmployees(const EmployeeArray& employees);
void saveTransactions(const CustomerArray& customers);     
void saveLoanRequests(const Queue& loanrequestQueue);  
void saveArchivedCustomers(const CustomerArray& archivedCustomers);
void saveCompletedLoans(const CompletedLoanList& completedLoans);
void saveTransactionHistory(const List1& transactionHistory);
#endif