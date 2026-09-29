#include "customerarrayMethods.h"
#include <iostream>

using namespace std;

void initCustomerArray(CustomerArray& arr) {
    arr.size = 0;
}

bool addCustomer(CustomerArray& arr, const customer& c) {
    if (arr.size >= MAX_CUSTOMERS)
        return false;

    if (findCustomerByAccountNumber(arr, c.accountnumber) != -1)
        return false; // already exists

    arr.data[arr.size] = c;
    arr.size++;
    return true;
}


void deleteCustomer(CustomerArray& arr, const customer& c) {
    int i = findCustomerByAccountNumber(arr, c.accountnumber);
    if (i != -1) {
        for (; i < arr.size - 1; i++) {
            arr.data[i] = arr.data[i + 1];
        }
        arr.size--;
    }
    else {
        cout << "error deleting the customer";
    }
}


int findCustomerByAccountNumber(const CustomerArray& arr, int accountnumber) {
    for (int i = 0; i < arr.size; i++) {
        if (arr.data[i].accountnumber == accountnumber)
            return i;
    }
    return -1;
}