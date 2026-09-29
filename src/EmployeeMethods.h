#ifndef EMPLOYEEMETHODS_H
#define EMPLOYEEMETHODS_H

#include "Employeearray.h"
#include "customerarrayMethods.h"
#include "completedloanlist.h"
#include "QueueMethods.h"
#include "singlylinkedlistMethods.h"

using namespace std;

// ================== Employee methods ==================
void addEmployee(EmployeeArray* employees);
void deleteEmployee(EmployeeArray* employees);
void modifyEmployee(EmployeeArray* employees);
void displayEmployeesAlphabetically(EmployeeArray* employees);
void displayEmployeesByBranch(const EmployeeArray* employees);
void displayEmployeesRecentEarliest(const EmployeeArray* employees);


// ================== Customer / loan / stats (unchanged) ==================
void addCustomerAccount(CustomerArray& customers);
void displayAccounts(const CustomerArray& customers);
void changeStatus(CustomerArray& customers);
void displayLoans(CustomerArray& customers);
void deleteClosed(CustomerArray& customers, CustomerArray& archive);
void changeloanstatus(CustomerArray& customers);
void moveCompletedLoansToArchive(CustomerArray& customers, CompletedLoanList& completedLoans);
void manageLoanRequests(CustomerArray& customers, Queue* loanRequests);
void finalizeDailyTransactions(CustomerArray& customers, List1& history);

// ================== Utility functions for employees ==================
int  findEmployeeById(const EmployeeArray* employees, int id);
void swapEmployees(Employee& a, Employee& b);
void sortEmployeesByLastName(EmployeeArray* employees);
bool isNumeric(const string& str);
bool isAlphabetic(const string& str);
string convertDate2(const string& d);
string calculateEndDate(const string& startDate, int durationYears);

// Employee Login 
int loginEmployee(const EmployeeArray* employees);

#endif

