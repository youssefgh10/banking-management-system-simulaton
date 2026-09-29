#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include "customerMethods.h"
#include "QueueMethods.h"

using namespace std;

static int nextLoanID = 1000;
static int nextTransactionID = 1000;

void initializeIds(const CustomerArray& customers, const Queue& requests,
    const CompletedLoanList& completedLoans, const List1& history) {
    for (int i = 0; i < customers.size; ++i) {
        for (Node* n = customers.data[i].loans.head; n; n = n->next)
            nextLoanID = max(nextLoanID, n->data.loanID);
        const stack& daily = customers.data[i].dailytransaction;
        for (int j = 1; j <= daily.Top; ++j)
            nextTransactionID = max(nextTransactionID, daily.data[j].transactionID);
    }
    for (int i = requests.Front; i != 0 && i <= requests.Tail; ++i)
        nextLoanID = max(nextLoanID, requests.elements[i].requestID);
    for (CompletedLoanNode* n = completedLoans.head; n; n = n->next)
        nextLoanID = max(nextLoanID, n->data.loanID);
    for (Node1* n = history.head; n; n = n->next)
        nextTransactionID = max(nextTransactionID, n->data.transactionID);
}

// 1) of part 1:
int login(CustomerArray& customers) {
    int accountnumbertest;
    string accountholdernametest;

    cout << CYAN << "=====LOGIN PAGE=====" << RESET << endl;
    cout << YELLOW << "Enter the account number:" << RESET << endl;
    cin >> accountnumbertest;
    cin.ignore();
    cout << YELLOW << "Enter the account holder name:" << RESET << endl;
    getline(cin, accountholdernametest);

    // Use customers.size and customers.data[i]
    for (int i = 0; i < customers.size; i++) {
        bool numbersmatch = (accountnumbertest == customers.data[i].accountnumber);
        bool namesmatch = (accountholdernametest == customers.data[i].accountholdername);

        if (numbersmatch && namesmatch) {
            bool isactive = (customers.data[i].Status == "active");

            if (isactive) {
                cout << GREEN << "Login SUCCESS , Welcome!" << RESET << endl;
                // Return index inside CustomerArray
                return i;
            }
            else {
                cout << RED << "ERROR: Account status is " << customers.data[i].Status << RESET << endl;
                return -1;
            }
        }
    }

    cout << RED << "ERROR!: The account number or holder name is incorrect, please check your details!" << RESET << endl;
    return -1;
}

//2) of part 1:
void viewloans(customer& Customer) {
    cout << CYAN << "=====LOANS PAGE=====" << RESET << endl;
    if (Customer.loans.size == 0) {
        cout << YELLOW << "You have no loans in your account" << RESET << endl;
        return;
    }
    else  cout << CYAN << "Total loans: " << YELLOW << Customer.loans.size << RESET << endl << endl;//2 endl just for aesthetics
    Node* current = Customer.loans.head;
    int loannumber = 1;
    while (current) {
        loan currentloan = current->data;
        cout << MAGENTA << "Loan number:" << YELLOW << loannumber << RESET << endl;
        cout << WHITE << "ID: " << YELLOW << currentloan.loanID << RESET << endl;
        cout << WHITE << "Type: " << YELLOW << currentloan.loantype << RESET << endl;
        cout << WHITE << "  Principal: " << YELLOW << currentloan.principalamount << " TND" << RESET << endl;
        cout << WHITE << "Interest rate: " << YELLOW << currentloan.interestrate << "%" << RESET << endl;
        cout << WHITE << "  Amount paid: " << YELLOW << currentloan.amountpaid << " TND" << RESET << endl;
        cout << WHITE << "  Remaining: " << YELLOW << currentloan.remainingbalance << " TND" << RESET << endl;
        cout << WHITE << "  Start Date: " << YELLOW << currentloan.startdate << RESET << endl;
        cout << WHITE << "  End Date: " << YELLOW << currentloan.enddate << RESET << endl;
        cout << WHITE << "  Status: " << GREEN << currentloan.loanstatus << RESET << endl << endl;//2 endl just for aesthetics
        current = current->next;
        loannumber++;
    }
    int choice;
    cout << YELLOW << "Press 1 to return to the menu: " << RESET;
    cin >> choice;
    while (choice != 1) {
        cout << RED << "Invalid input. " << YELLOW << "Press 1 to return to the menu: " << RESET;
        cin >> choice;
    }
}
//3)
int generateLoanID() {
    return ++nextLoanID;
}

void submitLoanRequest(customer& Customer, Queue* loanRequests) {
    cout << CYAN << "\n===== SUBMIT LOAN REQUEST =====" << RESET << endl;
    cout << WHITE << "\nLoan Types:" << RESET << endl;
    cout << YELLOW << "1. Car loan" << RESET << endl;
    cout << YELLOW << "2. Home loan" << RESET << endl;
    cout << YELLOW << "3. Student loan" << RESET << endl;
    cout << YELLOW << "4. Business loan" << RESET << endl;
    cout << YELLOW << "Choose loan type (1-4): " << RESET;
    int choice;
    cin >> choice;
    if (choice < 1 || choice > 4) {
        cout << RED << "Invalid choice!" << RESET << endl;
        return;
    }

    string loanType;
    switch (choice) {
    case 1: loanType = "car"; break;
    case 2: loanType = "home"; break;
    case 3: loanType = "student"; break;
    case 4: loanType = "business"; break;
    }
    double amount;
    cout << YELLOW << "Enter requested loan amount in TND: " << RESET;
    cin >> amount;
    if (amount <= 0) {
        cout << RED << "ERROR: Amount must be positive!" << RESET << endl;
        return;
    }
    int duration;
    cout << YELLOW << "Enter loan duration (in years): " << RESET;
    cin >> duration;
    if (duration <= 0) {
        cout << RED << "ERROR: Duration must be positive!" << RESET << endl;
        return;
    }
    Loanrequest newRequest;
    newRequest.requestID = generateLoanID();
    newRequest.accountNumber = Customer.accountnumber;
    newRequest.customerName = Customer.accountholdername;
    newRequest.loanType = loanType;
    newRequest.requestedAmount = amount;
    newRequest.requestDate = getCurrentDate();//ahayka elouta el function
    newRequest.status = "pending";
    newRequest.durationYears = duration;
    Enqueue(loanRequests, newRequest, true);

    cout << GREEN << "\n===== REQUEST SUBMITTED =====" << RESET << endl;
    cout << WHITE << "Loan type: " << YELLOW << loanType << RESET << endl;
    cout << WHITE << "Requested amount: " << YELLOW << amount << " TND" << RESET << endl;
    cout << WHITE << "Duration: " << YELLOW << duration << " years" << RESET << endl;
    cout << WHITE << "Status: " << GREEN << "Pending approval" << RESET << endl;
    cout << GREEN << "\nYour loan request has been submitted!" << RESET << endl;
    cout << WHITE << "The interest rate and start/end dates will be determined by the bank." << RESET << endl;
    cout << WHITE << "An employee will review your request soon.\n" << RESET;
}
//4)
/*struct tm {
    int tm_year;  // years since 1900
    int tm_mon;   // months since January (0-11)
    int tm_mday;  // day of the month (1-31)
    // ... other fields
};*/
string getCurrentDate() { //mech nfaserha fel rapport
    time_t now = time(0); //hedheya kalek trajaalek kadeh men seconds taadew men 1970
    tm ltm; // tm structure feha years ou months oou days ...... ahayka el fouk     
    localtime_s(&ltm, &now);//It breaks it down into year, month, day, hour, minute, second, according to your system’s timezone.
    int year = 1900 + ltm.tm_year;
    int month = 1 + ltm.tm_mon;
    int day = ltm.tm_mday;
    string date = "";
    if (day < 10) date += "0";
    date += to_string(day) + "/";
    if (month < 10) date += "0";
    date += to_string(month) + "/";
    date += to_string(year);
    return date;
}
int generateTransactionID() {
    return ++nextTransactionID;
}

void deposit(customer& Customer) {
    double amount;
    cout << CYAN << "=====DEPOSIT MONEY=====" << RESET << endl;
    cout << WHITE << "Current balence: " << YELLOW << Customer.balance << RESET << endl;
    cout << YELLOW << "Enter amount to deposit in TND:" << RESET << endl;
    cin >> amount;
    if (amount <= 0) {
        cout << RED << "ERROR: Amount must be positive!" << RESET << endl;
        return;
    }
    transaction newtransaction;
    newtransaction.transactionID = generateTransactionID();
    newtransaction.accountnumber = Customer.accountnumber;
    newtransaction.type = "Deposit";
    newtransaction.amount = amount;
    newtransaction.Date = getCurrentDate();
    if (push(&Customer.dailytransaction, newtransaction) != 0) return;
    Customer.balance += amount;
    cout << GREEN << "Amount Deposited successfully" << RESET << endl;
    cout << WHITE << "New balance: " << GREEN << Customer.balance << " TND" << RESET << endl;

}
void withdrawMoney(customer& Customer) {
    double amount;
    cout << CYAN << "===== WITHDRAW MONEY =====" << RESET << endl;
    cout << WHITE << "Current balance: " << YELLOW << Customer.balance << " TND" << RESET << endl;
    cout << WHITE << "Available denominations: " << YELLOW << "10, 20, 50 TND" << RESET << endl;
    cout << YELLOW << "Enter amount to withdraw: " << RESET;
    cin >> amount;
    if (amount <= 0) {
        cout << RED << "ERROR: Amount must be positive!" << RESET << endl;
        return;
    }
    if (amount != 10 && amount != 20 && amount != 50) {
        cout << RED << "ERROR: Amount must be in denominations of 10, 20, or 50 TND!" << RESET << endl;
        return;
    }
    if (amount > Customer.balance) {
        cout << RED << "ERROR: Insufficient balance!" << RESET << endl;
        cout << WHITE << "Your balance: " << YELLOW << Customer.balance << " TND" << RESET << endl;
        return;
    }
    transaction newtransaction;
    newtransaction.transactionID = generateTransactionID();
    newtransaction.accountnumber = Customer.accountnumber;
    newtransaction.type = "Withdrawal";
    newtransaction.amount = amount;
    newtransaction.Date = getCurrentDate();
    if (push(&Customer.dailytransaction, newtransaction) != 0) return;

    Customer.balance -= amount;
    cout << GREEN << "SUCCESS! Withdrew " << amount << " TND" << RESET << endl;
    cout << WHITE << "New balance: " << GREEN << Customer.balance << " TND" << RESET << endl;
}
//5)
void viewTransactions(const customer& Customer) {
    cout << CYAN << "===== DAILY TRANSACTIONS =====" << RESET << endl;
    if (isEmpty(Customer.dailytransaction)) {
        cout << YELLOW << "No transactions for today." << RESET << endl;
        return;
    }
    displaystack(Customer.dailytransaction);
}
//6)
void undotransaction(customer& Customer) {
    if (isEmpty(Customer.dailytransaction)) {
        cout << YELLOW << "No transactions to undo." << RESET << endl;
        return;
    }
    transaction lastTrans = top(Customer.dailytransaction);
    cout << CYAN << "===== LAST TRANSACTION =====" << RESET << endl;
    cout << WHITE << "Transaction ID: " << YELLOW << lastTrans.transactionID << RESET << "\n";
    cout << WHITE << "Account Number: " << YELLOW << lastTrans.accountnumber << RESET << "\n";
    cout << WHITE << "Type: " << YELLOW << lastTrans.type << RESET << "\n";
    cout << WHITE << "Amount: " << YELLOW << lastTrans.amount << " TND" << RESET << "\n";
    cout << WHITE << "Date: " << YELLOW << lastTrans.Date << RESET << "\n";
    cout << MAGENTA << "----------------------------------------" << RESET << "\n";
    if ((lastTrans.type == "Deposit" || lastTrans.type == "deposit")) {
        cout << YELLOW << "Undoing this deposit will decrease your balance by " << lastTrans.amount << " TND." << RESET << endl;
    }
    else if ((lastTrans.type == "Withdrawal" || lastTrans.type == "withdrawal")) {
        cout << YELLOW << "Undoing this withdrawal will increase your balance by " << lastTrans.amount << " TND." << RESET << endl;
    }
    cout << YELLOW << "Do you want to proceed? (1:yes/2:no): " << RESET;
    int choice;
    cin >> choice;
    if (choice == 1) {
        transaction lasttransaction = pop(&Customer.dailytransaction);
        if ((lasttransaction.type == "Deposit" || lasttransaction.type == "deposit")) {
            Customer.balance -= lasttransaction.amount;
        }
        else if ((lasttransaction.type == "Withdrawal" || lasttransaction.type == "withdrawal")) {
            Customer.balance += lasttransaction.amount;
        }
        cout << GREEN << "Transaction undone successfully." << RESET << endl;
        cout << WHITE << "Your new balance is: " << GREEN << Customer.balance << RESET << endl;
        return;
    }
    if (choice == 2) {
        cout << CYAN << "Transaction not undone." << RESET << endl;
        return;
    }
    else {
        cout << RED << "Invalid choice. Transaction not undone." << RESET << endl;
        return;
    }

}
