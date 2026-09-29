#ifndef STATISTICSMETH_H
#define STATISTICSMETH_H
#include "customerarray.h"
#include "Employeearray.h"
void totalloans(const CustomerArray& customers);
void numberofloansbytype(const CustomerArray& customers);
void numberofloansbystatus(const CustomerArray& customers);
void activeloansdaterange(const CustomerArray& customers);
void highestnumberofloans(const CustomerArray& customers);
void highestaccountbalance(const CustomerArray& customers);
void lowestaccountbalance(const CustomerArray& customers);
void totalemployees(const EmployeeArray& employees);
void numberemployeesbranch(const EmployeeArray& employees);


string convertDate(const string& d);
#endif 


//********