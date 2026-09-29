#ifndef MENUES_H
#define MENUES_H

#include "customerMethods.h"
#include <string>
#include "EmployeeMethods.h"
#include "statisticsmeth.h"

using namespace std;

char menu_customer();
void CustomerInterface2(CustomerArray& customers, Queue* loanRequests);

char menu_employee();
void EmployeeInterface2(EmployeeArray* employees, CustomerArray& customers,
    CustomerArray& archivedCustomers, CompletedLoanList& completedLoans, Queue* loanRequests, List1& history);

char menu_statistics();
void statisticsinterface2(CustomerArray& customers, EmployeeArray& employees);

#endif
