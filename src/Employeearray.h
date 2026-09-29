#ifndef EMPLOYEEARRAY_H
#define EMPLOYEEARRAY_H

#include "Employee.h"

using namespace std;

const int MAX_EMPLOYEES = 1000;

struct EmployeeArray {
    Employee data[MAX_EMPLOYEES];
    int size;
};

#endif
