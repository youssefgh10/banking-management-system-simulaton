#include <iostream>
#include <string>
#include "menues.h"
#include "datamethods.h"
#include "colors.h"
#include "completedloanlistmeth.h"

using namespace std;

// Function prototypes for main menu
void displayMainMenu();
char getMainMenuChoice();
void saveAllData(CustomerArray& customers, CustomerArray& archivedCustomers,
    EmployeeArray& employees, CompletedLoanList& completedLoans,
    Queue* loanRequests, List1& transactionHistory);

int main() {

    // ========================================
    // INITIALIZE DATA STRUCTURES (use heap for big arrays)
    // ========================================

    CustomerArray* customers = new (nothrow) CustomerArray();
    CustomerArray* archivedCustomers = new (nothrow) CustomerArray();
    EmployeeArray* employees = new (nothrow) EmployeeArray();
    CompletedLoanList completedLoans = createList2();
    Queue* loanRequests = CreateQueue();
    List1 transactionHistory = createList3();

    if (!customers || !archivedCustomers || !employees) {
        cerr << RED << "\n[ERROR] Unable to allocate memory for core structures.\n" << RESET;
        return 1;
    }

    customers->size = 0;
    archivedCustomers->size = 0;
    employees->size = 0;


    // ========================================
    // LOAD DATA FROM CSV FILES
    // ========================================

    cout << CYAN << "\n========================================\n";
    cout << "    BANKING MANAGEMENT SYSTEM v1.0\n";
    cout << "========================================\n" << RESET;

    cout << YELLOW << "\nLoading data from files...\n" << RESET;
    cout << "----------------------------------------\n";


    loadCustomers(*customers);
    loadEmployees(*employees);
    loadLoans(*customers);
    loadTransactions(*customers);        //  Load today's work
    loadLoanRequests(*loanRequests);
    loadArchivedCustomers(*archivedCustomers);
    loadCompletedLoans(completedLoans);
    loadTransactionHistory(transactionHistory);
    initializeIds(*customers, *loanRequests, completedLoans, transactionHistory);
    cout << "----------------------------------------\n";
    cout << GREEN << "Data loaded successfully!\n" << RESET;

    system("pause");
    system("cls");

    // ========================================
    // MAIN PROGRAM LOOP
    // ========================================

    bool exitProgram = false;

    while (!exitProgram) {
        displayMainMenu();
        char mainChoice = getMainMenuChoice();

        system("cls");

        switch (mainChoice) {

        case '1': {
            // Customer Interface - returns when user exits
            CustomerInterface2(*customers, loanRequests);

            // Save data after exiting customer interface
            cout << YELLOW << "\nSaving customer data...\n" << RESET;
            saveAllData(*customers, *archivedCustomers, *employees, completedLoans,
                loanRequests, transactionHistory);
            cout << GREEN << "Data saved successfully!\n" << RESET;
            system("pause");
            system("cls");
            break;
        }

        case '2': {
            // Employee Interface - returns when user exits
            EmployeeInterface2(employees, *customers, *archivedCustomers, completedLoans,
                loanRequests, transactionHistory);

            // Save data after exiting employee interface
            cout << YELLOW << "\nSaving employee data...\n" << RESET;
            saveAllData(*customers, *archivedCustomers, *employees, completedLoans,
                loanRequests, transactionHistory);
            cout << GREEN << "Data saved successfully!\n" << RESET;
            system("pause");
            system("cls");
            break;
        }

        case '3': {
            // Final save and exit
            cout << CYAN << "\n========================================\n";
            cout << "       SAVING DATA AND EXITING...\n";
            cout << "========================================\n" << RESET;

            cout << YELLOW << "\nSaving data to files...\n" << RESET;
            cout << "----------------------------------------\n";

            saveAllData(*customers, *archivedCustomers, *employees, completedLoans,
                loanRequests, transactionHistory);

            cout << "----------------------------------------\n";
            cout << GREEN << "All data saved successfully!\n" << RESET;

            cout << CYAN << "\n========================================\n";
            cout << "   Thank you for using our system!\n";
            cout << "         Goodbye and have a great day!\n";
            cout << "========================================\n" << RESET;

            exitProgram = true;
            break;
        }

        default: {
            cout << RED << "Invalid choice. Please try again.\n" << RESET;
            system("pause");
            system("cls");
            break;
        }
        }
    }

    // ========================================
    // CLEANUP MEMORY
    // ========================================

    destroyList2(&completedLoans);
    DestroyQueue(loanRequests);
    destroyList3(&transactionHistory);

    delete customers;
    delete archivedCustomers;
    delete employees;

    return 0;
}

// ========================================
// SAVE ALL DATA FUNCTION
// ========================================
void saveAllData(CustomerArray& customers, CustomerArray& archivedCustomers,
    EmployeeArray& employees, CompletedLoanList& completedLoans,
    Queue* loanRequests, List1& transactionHistory) {
    saveCustomers(customers);
    saveEmployees(employees);
    saveLoans(customers);
    saveTransactions(customers);
    saveLoanRequests(*loanRequests);
    saveArchivedCustomers(archivedCustomers);
    saveCompletedLoans(completedLoans);
    saveTransactionHistory(transactionHistory);
}

// ========================================
// DISPLAY MAIN MENU
// ========================================
void displayMainMenu() {
    cout << CYAN << "\n+----------------------------------------+\n";
    cout << "|   BANKING MANAGEMENT SYSTEM - MAIN     |\n";
    cout << "+----------------------------------------+\n" << RESET;

    cout << "\n";
    cout << GREEN << "  1. " << RESET << WHITE << "Customer Interface\n" << RESET;
    cout << BLUE << "  2. " << RESET << WHITE << "Employee Interface\n" << RESET;
    cout << RED << "  3. " << RESET << WHITE << "Exit Program\n" << RESET;

    cout << CYAN << "\n========================================\n" << RESET;
}

// ========================================
// GET MAIN MENU CHOICE WITH VALIDATION
// ========================================
char getMainMenuChoice() {
    string input;

    while (true) {
        cout << YELLOW << "Enter your choice (1-3): " << RESET;
        if (!(cin >> input)) return '3';

        // Validate input
        if (input.size() == 1 && input[0] >= '1' && input[0] <= '3') {
            return input[0];
        }

        cout << RED << "\n[ERROR] Invalid input! Please enter 1, 2, or 3.\n\n" << RESET;
    }
}
