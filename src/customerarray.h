#ifndef CUSTOMERARRAY_H
#define CUSTOMERARRAY_H

#include "customer.h"

using namespace std;

const int MAX_CUSTOMERS = 1000;

struct CustomerArray {
    customer data[MAX_CUSTOMERS];
    int size;
};

#endif