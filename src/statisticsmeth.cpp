

#include <iostream>
#include "statisticsmeth.h"
#include "doublylinkedlist.h"

using namespace std;


// ======================================================
// 1) TOTAL LOANS
// ======================================================
void totalloans(const CustomerArray& customers) {
    int total = 0;
    for (int i = 0; i < customers.size; i++) {
        total += listSize(customers.data[i].loans);
    }

    cout << CYAN << "\n===== TOTAL LOANS =====\n" << RESET;

    if (total == 0)
        cout << RED << "There are no loans for any customer.\n" << RESET;
    else
        cout << WHITE << "Total loans across all customers: "
        << YELLOW << total << RESET << "\n";
}



// ======================================================
// 2) NUMBER OF LOANS BY TYPE
// ======================================================
void numberofloansbytype(const CustomerArray& customers) {
    int car = 0, home = 0, student = 0, business = 0;

    for (int i = 0; i < customers.size; i++) {
        Node* current = customers.data[i].loans.head;
        while (current) {
            if (current->data.loantype == "car") car++;
            else if (current->data.loantype == "home") home++;
            else if (current->data.loantype == "student") student++;
            else if (current->data.loantype == "business") business++;
            current = current->next;
        }
    }

    cout << CYAN << "\n===== LOANS BY TYPE =====\n" << RESET;

    cout << WHITE << "Car Loans:      " << YELLOW << car << RESET << "\n";
    cout << WHITE << "Home Loans:     " << YELLOW << home << RESET << "\n";
    cout << WHITE << "Student Loans:  " << YELLOW << student << RESET << "\n";
    cout << WHITE << "Business Loans: " << YELLOW << business << RESET << "\n";
}



// ======================================================
// 3) NUMBER OF LOANS BY STATUS
// ======================================================
void numberofloansbystatus(const CustomerArray& customers) {
    int active = 0, completed = 0, overdue = 0;

    for (int i = 0; i < customers.size; i++) {
        Node* current = customers.data[i].loans.head;
        while (current) {
            if (current->data.loanstatus == "active") active++;
            else if (current->data.loanstatus == "completed") completed++;
            else if (current->data.loanstatus == "overdue") overdue++;
            current = current->next;
        }
    }

    cout << CYAN << "\n===== LOANS BY STATUS =====\n" << RESET;

    cout << WHITE << "Active:     " << GREEN << active << RESET << "\n";
    cout << WHITE << "Completed:  " << BLUE << completed << RESET << "\n";
    cout << WHITE << "Overdue:    " << RED << overdue << RESET << "\n";
}



// ======================================================
// 4) ACTIVE LOANS WITHIN DATE RANGE
// ======================================================
string convertDate(const string& d) {
    return d.substr(6, 4) + d.substr(3, 2) + d.substr(0, 2);
}

void activeloansdaterange(const CustomerArray& customers) {
    if (customers.size == 0) {
        cout << RED << "\nNo customers available.\n" << RESET;
        return;
    }

    string Startdate, Enddate;

    cout << CYAN << "\n===== ACTIVE LOANS IN DATE RANGE =====\n" << RESET;
    cout << YELLOW << "Enter Start Date (DD/MM/YYYY): " << RESET;
    cin >> Startdate;
    cout << YELLOW << "Enter End Date (DD/MM/YYYY):   " << RESET;
    cin >> Enddate;

    string normStart = convertDate(Startdate);
    string normEnd = convertDate(Enddate);

    // If user entered wrong order, swap them
    if (normStart > normEnd) {
        swap(normStart, normEnd);
        swap(Startdate, Enddate);
    }

    cout << MAGENTA
        << "\nSearching for active loans from "
        << Startdate << " to " << Enddate << "...\n"
        << RESET;

    bool found = false;

    for (int i = 0; i < customers.size; i++) {
        Node* current = customers.data[i].loans.head;

        while (current != nullptr) {
            if (current->data.loanstatus == "active") {

                string loanStart = convertDate(current->data.startdate);
                string loanEnd = convertDate(current->data.enddate);

                // Overlap condition
                if (loanStart >= normStart && loanEnd <= normEnd) {

                    found = true;

                    cout << CYAN << "\n----------------------------------------\n" << RESET;
                    cout << WHITE << "Customer: "
                        << customers.data[i].accountholdername
                        << " (Account " << customers.data[i].accountnumber << ")\n";
                    cout << WHITE << "Loan ID: " << YELLOW << current->data.loanID << RESET << "\n";
                    cout << "Loan Type:         " << WHITE << current->data.loantype << "\n";
                    cout << "Principal Amount:  " << YELLOW << current->data.principalamount << RESET << "\n";
                    cout << "Interest Rate:     " << YELLOW << current->data.interestrate << "%" << RESET << "\n";
                    cout << "Amount Paid:       " << YELLOW << current->data.amountpaid << RESET << "\n";
                    cout << "Remaining Balance: " << YELLOW << current->data.remainingbalance << RESET << "\n";
                    cout << "Start Date:        " << WHITE << current->data.startdate << "\n";
                    cout << "End Date:          " << WHITE << current->data.enddate << "\n";
                    cout << "Status:            " << GREEN << "active" << RESET << "\n";
                }
            }
            current = current->next;
        }
    }

    if (!found) {
        cout << RED
            << "\nNo active loans found between "
            << Startdate << " and " << Enddate << ".\n"
            << RESET;
    }
}



// ======================================================
// 5) CUSTOMER(S) WITH MOST LOANS
// ======================================================
void highestnumberofloans(const CustomerArray& customers) {
    if (customers.size == 0) {
        cout << RED << "No customers available.\n" << RESET;
        return;
    }

    int highesttotal = 0;

    for (int i = 0; i < customers.size; i++) {
        highesttotal = max(highesttotal, listSize(customers.data[i].loans));
    }

    cout << CYAN << "\n===== CUSTOMERS WITH MOST LOANS =====\n" << RESET;

    int count = 0;

    for (int i = 0; i < customers.size; i++) {
        if (listSize(customers.data[i].loans) == highesttotal) {
            count++;
            cout << MAGENTA << "\n-----------------------------------\n" << RESET;
            cout << WHITE << "Account Number: " << YELLOW << customers.data[i].accountnumber << RESET << "\n";
            cout << WHITE << "Name: " << customers.data[i].accountholdername << "\n";
            cout << WHITE << "Loans: " << YELLOW << highesttotal << RESET << "\n";
        }
    }

    if (highesttotal == 0)
        cout << RED << "No customers have loans.\n" << RESET;
}



// ======================================================
// 6) CUSTOMER(S) WITH HIGHEST BALANCE
// ======================================================
void highestaccountbalance(const CustomerArray& customers) {
    if (customers.size == 0) {
        cout << RED << "No customers available.\n" << RESET;
        return;
    }

    double highest = customers.data[0].balance;

    for (int i = 1; i < customers.size; i++)
        highest = max(highest, customers.data[i].balance);

    cout << CYAN << "\n===== HIGHEST ACCOUNT BALANCE =====\n" << RESET;

    for (int i = 0; i < customers.size; i++) {
        if (customers.data[i].balance == highest) {
            cout << MAGENTA << "\n-----------------------------------\n" << RESET;
            cout << WHITE << "Account Number: " << YELLOW << customers.data[i].accountnumber << RESET << "\n";
            cout << WHITE << "Name: " << customers.data[i].accountholdername << "\n";
            cout << WHITE << "Balance: " << GREEN << highest << RESET << "\n";
        }
    }
}



// ======================================================
// 7) CUSTOMER(S) WITH LOWEST BALANCE
// ======================================================
void lowestaccountbalance(const CustomerArray& customers) {
    if (customers.size == 0) {
        cout << RED << "No customers available.\n" << RESET;
        return;
    }

    double lowest = customers.data[0].balance;

    for (int i = 1; i < customers.size; i++)
        lowest = min(lowest, customers.data[i].balance);

    cout << CYAN << "\n===== LOWEST ACCOUNT BALANCE =====\n" << RESET;

    for (int i = 0; i < customers.size; i++) {
        if (customers.data[i].balance == lowest) {
            cout << MAGENTA << "\n-----------------------------------\n" << RESET;
            cout << WHITE << "Account Number: " << YELLOW << customers.data[i].accountnumber << RESET << "\n";
            cout << WHITE << "Name: " << customers.data[i].accountholdername << "\n";
            cout << WHITE << "Balance: " << RED << lowest << RESET << "\n";
        }
    }
}



// ======================================================
// 8) TOTAL EMPLOYEES
// ======================================================
void totalemployees(const EmployeeArray& employees) {
    cout << CYAN << "\n===== TOTAL EMPLOYEES =====\n" << RESET;

    if (employees.size == 0) {
        cout << RED << "No employees available.\n" << RESET;
        return;
    }

    cout << WHITE << "Total employees: " << YELLOW << employees.size << RESET << "\n";
}



// ======================================================
// 9) NUMBER OF EMPLOYEES BY BRANCH
// ======================================================
void numberemployeesbranch(const EmployeeArray& employees) {
    if (employees.size == 0) {
        cout << RED << "No employees available.\n" << RESET;
        return;
    }

    cout << CYAN << "\n===== EMPLOYEES BY BRANCH =====\n" << RESET;

    int* branches = new int[employees.size];
    int* counts = new int[employees.size]();

    int branchCount = 0;

    for (int i = 0; i < employees.size; i++) {
        bool found = false;

        for (int j = 0; j < branchCount; j++) {
            if (branches[j] == employees.data[i].bankbranch) {
                counts[j]++;
                found = true;
                break;
            }
        }

        if (!found) {
            branches[branchCount] = employees.data[i].bankbranch;
            counts[branchCount] = 1;
            branchCount++;
        }
    }

    // Display
    for (int i = 0; i < branchCount; i++) {
        cout << MAGENTA << "Branch " << branches[i] << ": "
            << YELLOW << counts[i] << RESET << " employees\n";
    }

    delete[] branches;
    delete[] counts;
}

