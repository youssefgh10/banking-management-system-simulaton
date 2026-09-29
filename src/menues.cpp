#include <iostream>
#include <string>
#include "menues.h"
#include "customerarrayMethods.h"

using namespace std;

// ========================================
// CUSTOMER MENU
// ========================================

char menu_customer() {
    string input;

    cout << CYAN << "\n========================================\n";
    cout << "          CUSTOMER INTERFACE\n";
    cout << "========================================\n" << RESET;

    cout << GREEN << "1." << RESET << " LOGIN AS CUSTOMER\n";
    cout << RED << "2." << RESET << " Back to Main Menu\n";

    cout << CYAN << "========================================\n" << RESET;

    while (true) {
        cout << YELLOW << "Enter your choice: " << RESET;
        cin >> input;

        if (input.size() == 1 && (input[0] == '1' || input[0] == '2')) {
            return input[0];
        }

        cout << RED << "Invalid input. Please enter 1 or 2.\n\n" << RESET;
    }
}

void CustomerInterface2(CustomerArray& customers, Queue* loanRequests) {

    char choice = menu_customer();

    if (choice == '2') {
        cout << CYAN << "========================================\n";
        cout << "Returning to Main Menu...\n";
        cout << "========================================\n" << RESET;
        system("pause");
        system("cls");
        return; // Return to main menu
    }

    // Clear screen for clean login interface
    system("cls");

    // LOGIN with clean interface
    cout << CYAN << "\n+----------------------------------------+\n";
    cout << "|         CUSTOMER LOGIN PORTAL          |\n";
    cout << "+----------------------------------------+\n" << RESET;
    cout << "\n";

    int customerIndex = login(customers);


    if (customerIndex == -1) {
        cout << RED << "\n========================================\n";
        cout << "  LOGIN FAILED - RETURNING TO MAIN MENU\n";
        cout << "========================================\n" << RESET;
        system("pause");
        system("cls");
        return; // Return to main menu on failed login
    }

    cout << GREEN << "\n========================================\n";
    cout << "      LOGIN SUCCESSFUL! WELCOME!\n";
    cout << "========================================\n" << RESET;
    system("pause");

    customer& currentCustomer = customers.data[customerIndex];
    string input;

    while (true) {

        system("cls");

        cout << CYAN
            << "\n========================================\n"
            << "              CUSTOMER MENU\n"
            << "========================================\n"
            << RESET;

        cout << YELLOW << "Account: " << RESET << currentCustomer.accountholdername << "\n";
        cout << YELLOW << "Balance: " << RESET << currentCustomer.balance << " TND\n";
        cout << "----------------------------------------\n";

        cout << GREEN << "1." << RESET << " View Loans\n";
        cout << GREEN << "2." << RESET << " Submit Loan Request\n";
        cout << GREEN << "3." << RESET << " Deposit Money\n";
        cout << GREEN << "4." << RESET << " Withdraw Money\n";
        cout << GREEN << "5." << RESET << " View Transactions\n";
        cout << GREEN << "6." << RESET << " Undo Last Transaction\n";
        cout << RED << "0." << RESET << " Logout and Return to Main Menu\n";

        cout << CYAN << "========================================\n" << RESET;
        cout << YELLOW << "Enter your choice: " << RESET;

        cin >> input;

        bool valid = (input.size() == 1 && input[0] >= '0' && input[0] <= '6');

        if (!valid) {
            cout << RED << "Invalid choice. Please enter 0–6.\n" << RESET;
            system("pause");
        }
        else {

            char custChoice = input[0];
            system("cls");

            if (custChoice == '0') {
                cout << YELLOW << "\n========================================\n";
                cout << "  LOGGING OUT - RETURNING TO MAIN MENU\n";
                cout << "========================================\n" << RESET;
                system("pause");
                system("cls");
                return; // Return to main menu
            }

            switch (custChoice) {
            case '1':
                viewloans(currentCustomer);
                break;
            case '2':
                submitLoanRequest(currentCustomer, loanRequests);
                break;
            case '3':
                deposit(currentCustomer);
                break;
            case '4':
                withdrawMoney(currentCustomer);
                break;
            case '5':
                viewTransactions(currentCustomer);
                break;
            case '6':
                undotransaction(currentCustomer);
                break;
            }
        }

        system("pause");
    }
}

// ========================================
// EMPLOYEE MENU
// ========================================

char menu_employee_initial() {
    string input;

    cout << CYAN << "\n========================================\n";
    cout << "          EMPLOYEE INTERFACE\n";
    cout << "========================================\n" << RESET;

    cout << GREEN << "1." << RESET << " LOGIN AS EMPLOYEE\n";
    cout << RED << "2." << RESET << " Back to Main Menu\n";

    cout << CYAN << "========================================\n" << RESET;

    while (true) {
        cout << YELLOW << "Enter your choice: " << RESET;
        cin >> input;

        if (input.size() == 1 && (input[0] == '1' || input[0] == '2')) {
            return input[0];
        }

        cout << RED << "Invalid input. Please enter 1 or 2.\n\n" << RESET;
    }
}

char menu_employee() {
    string input;

    cout << CYAN << "\n========================================\n";
    cout << "        EMPLOYEE MANAGEMENT SYSTEM\n";
    cout << "========================================\n" << RESET;

    cout << GREEN << "1." << RESET << " Add Employee\n";
    cout << GREEN << "2." << RESET << " Delete Employee\n";
    cout << GREEN << "3." << RESET << " Modify Employee\n";
    cout << GREEN << "4." << RESET << " Display Alphabetically\n";
    cout << GREEN << "5." << RESET << " Display by Branch\n";
    cout << GREEN << "6." << RESET << " Display Recent/Earliest Hired\n";
    cout << GREEN << "7." << RESET << " Add a Customer Account\n";
    cout << GREEN << "8." << RESET << " Display List of Customers\n";
    cout << GREEN << "9." << RESET << " Change Status of an Account\n";

    cout << MAGENTA << "a." << RESET << " Delete all closed accounts\n";
    cout << MAGENTA << "b." << RESET << " Display loans of a customer\n";
    cout << MAGENTA << "c." << RESET << " Archive completed loans\n";
    cout << MAGENTA << "d." << RESET << " Change loan status\n";
    cout << MAGENTA << "e." << RESET << " Manage loan requests (FIFO)\n";
    cout << MAGENTA << "f." << RESET << " Finalize daily transactions\n";
    cout << MAGENTA << "g." << RESET << " Statistics Menu\n";

    cout << RED << "0. Back to Main Menu\n";
    cout << CYAN << "========================================\n" << RESET;

    while (true) {
        cout << YELLOW << "Enter your choice: " << RESET;
        cin >> input;

        if (input.size() == 1) {
            char c = input[0];
            if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'g'))
                return c;
        }

        cout << RED << "Invalid choice! Please enter 0–9 or a–g.\n" << RESET;
    }
}

void EmployeeInterface2(EmployeeArray* employees,
    CustomerArray& customers,
    CustomerArray& archivedCustomers,
    CompletedLoanList& completedLoans,
    Queue* loanRequests,
    List1& history)
{
    // Initial menu - login or back
    char initialChoice = menu_employee_initial();

    if (initialChoice == '2') {
        cout << CYAN << "========================================\n";
        cout << "Returning to Main Menu...\n";
        cout << "========================================\n" << RESET;
        system("pause");
        system("cls");
        return; // Return to main menu
    }

    // Clear screen for clean login interface
    system("cls");

    // LOGIN with clean interface
    cout << CYAN << "\n+----------------------------------------+\n";
    cout << "|         EMPLOYEE LOGIN PORTAL          |\n";
    cout << "+----------------------------------------+\n" << RESET;
    cout << "\n";

    int employeeIndex = loginEmployee(employees);

    if (employeeIndex == -1) {
        cout << RED << "\n========================================\n";
        cout << "  LOGIN FAILED - RETURNING TO MAIN MENU\n";
        cout << "========================================\n" << RESET;
        system("pause");
        system("cls");
        return; // Return to main menu on failed login
    }

    cout << GREEN << "\n========================================\n";
    cout << "      LOGIN SUCCESSFUL! WELCOME!\n";
    cout << "========================================\n" << RESET;
    system("pause");

    // Main employee management loop
    while (true) {
        system("cls");

        char choice = menu_employee();

        if (choice == '0') {
            cout << CYAN << "\n========================================\n";
            cout << "  LOGGING OUT - RETURNING TO MAIN MENU\n";
            cout << "========================================\n" << RESET;
            system("pause");
            system("cls");
            return; // Return to main menu
        }

        system("cls");

        switch (choice) {
        case '1': addEmployee(employees); break;
        case '2': deleteEmployee(employees); break;
        case '3': modifyEmployee(employees); break;
        case '4': displayEmployeesAlphabetically(employees); break;
        case '5': displayEmployeesByBranch(employees); break;
        case '6': displayEmployeesRecentEarliest(employees); break;

        case '7': addCustomerAccount(customers); break;
        case '8': displayAccounts(customers); break;
        case '9': changeStatus(customers); break;

        case 'a': deleteClosed(customers, archivedCustomers); break;
        case 'b': displayLoans(customers); break;
        case 'c': moveCompletedLoansToArchive(customers, completedLoans); break;
        case 'd': changeloanstatus(customers); break;
        case 'e': manageLoanRequests(customers, loanRequests); break;
        case 'f': finalizeDailyTransactions(customers, history); break;

        case 'g':
            // Enter Statistics Interface
            statisticsinterface2(customers, *employees);
            // After returning from statistics, continue the loop
            continue; // Skip the "press any key" at the bottom
        }

        system("pause");
    }
}

// ========================================
// STATISTICS MENU
// ========================================

char menu_statistics() {
    string input;

    cout << CYAN << "\n========================================\n";
    cout << "            STATISTICS MENU\n";
    cout << "========================================\n" << RESET;

    cout << GREEN << "1." << RESET << " Total Loans\n";
    cout << GREEN << "2." << RESET << " Loans by Type\n";
    cout << GREEN << "3." << RESET << " Loans by Status\n";
    cout << GREEN << "4." << RESET << " Active Loans in Date Range\n";
    cout << GREEN << "5." << RESET << " Customers with Most Loans\n";
    cout << GREEN << "6." << RESET << " Highest Balance\n";
    cout << GREEN << "7." << RESET << " Lowest Balance\n";
    cout << GREEN << "8." << RESET << " Total Employees\n";
    cout << GREEN << "9." << RESET << " Employees by Branch\n";
    cout << RED << "0. Back to Employee Menu\n";
    cout << CYAN << "========================================\n" << RESET;

    while (true) {
        cout << YELLOW << "Enter your choice: " << RESET;
        cin >> input;

        if (input.size() == 1 && input[0] >= '0' && input[0] <= '9')
            return input[0];

        cout << RED << "Invalid input. Please enter 0–9.\n" << RESET;
    }
}

void statisticsinterface2(CustomerArray& customers, EmployeeArray& employees) {
    while (true) {
        system("cls");

        char choice = menu_statistics();

        if (choice == '0') {
            cout << CYAN << "========================================\n";
            cout << "Returning to Employee Menu...\n";
            cout << "========================================\n" << RESET;
            system("pause");
            system("cls");
            return; // Return to employee menu
        }

        system("cls");

        switch (choice) {
        case '1':
            totalloans(customers);
            break;
        case '2':
            numberofloansbytype(customers);
            break;
        case '3':
            numberofloansbystatus(customers);
            break;
        case '4':
            activeloansdaterange(customers);
            break;
        case '5':
            highestnumberofloans(customers);
            break;
        case '6':
            highestaccountbalance(customers);
            break;
        case '7':
            lowestaccountbalance(customers);
            break;
        case '8':
            totalemployees(employees);
            break;
        case '9':
            numberemployeesbranch(employees);
            break;
        }

        system("pause");
    }
}
