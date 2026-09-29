#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
#include "colors.h"
using namespace std;

// Employee structure to store employee data - pretty straightforward ngl
struct Employee {
    int id;
    string name;
    string lastName;
    string address;
    double salary;
    string hireDate;        // Hire date format: DD/MM/YYYY
    int bankbranch;
};
#endif