
#ifndef CUSTOMERARRAYMETHODS_H
#define CUSTOMERARRAYMETHODS_H
#include "customerarray.h"
// CustomerArray methods
void initCustomerArray(CustomerArray& arr);
bool addCustomer(CustomerArray& arr, const customer& c);
void deleteCustomer(CustomerArray& arr, const customer& c);
int findCustomerByAccountNumber(const CustomerArray& arr, int accountNumber);
#endif
