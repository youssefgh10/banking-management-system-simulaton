

#include <iostream>
#include <string>
#include <cstring>
#include "EmployeeMethods.h"
#include "completedloanlistmeth.h"
#include <iomanip>

using namespace std;


// =============================
//   Utility Functions (Colored)
// =============================

// Convert DD/MM/YYYY → YYYYMMDD
string convertDate2(const string& d) {
    return d.substr(6, 4) + d.substr(3, 2) + d.substr(0, 2);
}

bool isNumeric(const string& str) {
    for (int i = 0; i < str.size();i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

bool isAlphabetic(const string& str) {
    for (int i = 0; i < str.size(); i++) {
        if (!isalpha(str[i])) return false;
    }
    return true;
}

// Swap employees (used in sorting)
void swapEmployees(Employee& a, Employee& b) {
    Employee tmp = a;
    a = b;
    b = tmp;
}
int findEmployeeById(const EmployeeArray* employees, int id) {
    if (!employees) return -1;
    for (int i = 0; i < employees->size; i++) {
        if (employees->data[i].id == id) {
            return i;
        }
    }
    return -1;
}
void sortEmployeesByLastName(EmployeeArray* employees) {
    if (!employees) return;
    for (int i = 0; i < employees->size - 1; i++) {
        for (int j = 0; j < employees->size - i - 1; j++) {
            if (employees->data[j].lastName > employees->data[j + 1].lastName) {
                swapEmployees(employees->data[j], employees->data[j + 1]);
            }
        }
    }
}
string calculateEndDate(const string& startDate, int durationYears) {
    int day = stoi(startDate.substr(0, 2));
    int month = stoi(startDate.substr(3, 2));
    int year = stoi(startDate.substr(6, 4)) + durationYears;
    // Simple date adjustment (not accounting for month lengths/leap years)
    return (day < 10 ? "0" : "") + to_string(day) + "/" +
           (month < 10 ? "0" : "") + to_string(month) + "/" +
           to_string(year);
}
// ============================================================
//                     ADD EMPLOYEE
// ============================================================

void addEmployee(EmployeeArray* employees) {

    if (!employees) return;

    if (employees->size >= MAX_EMPLOYEES) {
        cout << RED << "\n[ERROR] Cannot add more employees. Maximum capacity reached ("
            << MAX_EMPLOYEES << ").\n" << RESET;
        return;
    }

    Employee newEmployee;

    cout << CYAN << "\n========== ADD NEW EMPLOYEE ==========\n" << RESET;

    // ---------- Employee ID ----------
    bool idExists;
    do {
        idExists = false;
        cout << BLUE << "Enter Employee ID: " << RESET;
        cin >> newEmployee.id;

        if (cin.fail() || newEmployee.id < 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << RED << "[ERROR] Employee ID must be a positive number!\n" << RESET;
            idExists = true;
            continue;
        }

        for (int i = 0; i < employees->size; i++) {
            if (employees->data[i].id == newEmployee.id) {
                cout << RED << "[ERROR] ID already exists! Try again.\n" << RESET;
                idExists = true;
                break;
            }
        }
    } while (idExists);

    // ---------- First Name ----------
    do {
        cout << BLUE << "Enter First Name: " << RESET;
        cin >> newEmployee.name;

        if (!isAlphabetic(newEmployee.name)) {
            cout << RED << "[ERROR] Name must contain only letters!\n" << RESET;
        }
    } while (!isAlphabetic(newEmployee.name));

    // ---------- Last Name ----------
    do {
        cout << BLUE << "Enter Last Name: " << RESET;
        cin >> newEmployee.lastName;

        if (!isAlphabetic(newEmployee.lastName)) {
            cout << RED << "[ERROR] Last Name must contain only letters!\n" << RESET;
        }
    } while (!isAlphabetic(newEmployee.lastName));

    // ---------- Address ----------
    cin.ignore();
    bool badAddress;
    do {
        cout << BLUE << "Enter Address: " << RESET;
        getline(cin, newEmployee.address);

        badAddress = false;
        for (int i = 0; i < newEmployee.address.size();i++) {
            if (!isalnum(newEmployee.address[i]) && newEmployee.address[i] != ' ') {   // only letters, numbers, spaces
                badAddress = true;
                break;
            }
        }

        if (badAddress)
            cout << RED << "[ERROR] Address can only contain letters, digits, and spaces.\n" << RESET;

    } while (badAddress);

    // ---------- Salary ----------
    do {
        cout << BLUE << "Enter Salary (TND): " << RESET;
        cin >> newEmployee.salary;

        if (newEmployee.salary < 0) {
            cout << RED << "[ERROR] Salary cannot be negative! (and must be numeric)\n" << RESET;
        }
    } while (newEmployee.salary < 0);

    // ---------- Hire Date ----------
    bool badDate;
    do {
        cout << BLUE << "Enter Hire Date (DD/MM/YYYY): " << RESET;
        cin >> newEmployee.hireDate;

        badDate =
            newEmployee.hireDate.length() != 10 ||
            newEmployee.hireDate[2] != '/' ||
            newEmployee.hireDate[5] != '/' ||
            !isNumeric(newEmployee.hireDate.substr(0, 2)) ||
            !isNumeric(newEmployee.hireDate.substr(3, 2)) ||
            !isNumeric(newEmployee.hireDate.substr(6, 4)) ||
            newEmployee.hireDate.substr(0, 2) > "31" ||
            newEmployee.hireDate.substr(3, 2) > "12" ||
            newEmployee.hireDate.substr(6, 4) > "2025";

        if (badDate)
            cout << RED << "[ERROR] Invalid date format! Use DD/MM/YYYY.\n" << RESET;

    } while (badDate);


    // ---------- Branch Code ----------
    do {
        cout << BLUE << "Enter Branch Code: " << RESET;
        cin >> newEmployee.bankbranch;

        if ( newEmployee.bankbranch < 0) {
            cout << RED << "[ERROR] Branch code must be a NON-negative number!\n" << RESET;
        }

    } while ( newEmployee.bankbranch < 0);

    // Save employee
    employees->data[employees->size] = newEmployee;
    employees->size++;

    cout << GREEN << "\n[SUCCESS] Employee added!\n" << RESET;
}




// ============================================================
//                     DELETE EMPLOYEE
// ============================================================

void deleteEmployee(EmployeeArray* employees) {

    if (!employees) return;

    if (employees->size == 0) {
        cout << RED << "[ERROR] No employees to delete!\n" << RESET;
        return;
    }

    int id;
    cout << CYAN << "\n========== DELETE EMPLOYEE ==========\n" << RESET;
    cout << BLUE << "Enter Employee ID to delete: " << RESET;
    cin >> id;

    int index = findEmployeeById(employees, id);

    if (index == -1) {
        cout << RED << "[ERROR] Employee with ID " << id << " not found!\n" << RESET;
        return;
    }

    cout << YELLOW << "\nEmployee Found:\n" << RESET;
    cout << "Name: " << YELLOW << employees->data[index].name << " "
        << employees->data[index].lastName << RESET << "\n";
    cout << "Salary: " << YELLOW << employees->data[index].salary << RESET << " TND\n";

    char confirm;
    do {
        cout << BLUE << "\nAre you sure you want to delete this employee? (Y/N): " << RESET;
        cin >> confirm;
    } while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');

    if (confirm == 'Y' || confirm == 'y') {
        for (int i = index; i < employees->size - 1; i++) {
            employees->data[i] = employees->data[i + 1];
        }
        employees->size--;

        cout << GREEN << "\n[SUCCESS] Employee deleted successfully!\n" << RESET;
    }
    else {
        cout << YELLOW << "\n[CANCELLED] Deletion cancelled.\n" << RESET;
    }
}



// ============================================================
//                     MODIFY EMPLOYEE
// ============================================================

void modifyEmployee(EmployeeArray* employees) {

    if (!employees) return;

    if (employees->size == 0) {
        cout << RED << "\n[ERROR] No employees to modify!\n" << RESET;
        return;
    }

    int id;
    cout << CYAN << "\n========== MODIFY EMPLOYEE ==========\n" << RESET;
    cout << BLUE << "Enter Employee ID to modify: " << RESET;
    cin >> id;

    int index = findEmployeeById(employees, id);

    if (index == -1) {
        cout << RED << "[ERROR] Employee with ID " << id << " not found!\n" << RESET;
        return;
    }

    cout << YELLOW << "\nCurrent Employee Details:\n" << RESET;
    cout << "1. Name:        " << YELLOW << employees->data[index].name << RESET << "\n";
    cout << "2. Last Name:   " << YELLOW << employees->data[index].lastName << RESET << "\n";
    cout << "3. Address:     " << YELLOW << employees->data[index].address << RESET << "\n";
    cout << "4. Salary:      " << YELLOW << employees->data[index].salary << RESET << " TND\n";
    cout << "5. Hire Date:   " << YELLOW << employees->data[index].hireDate << RESET << "\n";
    cout << "6. Branch Code: " << YELLOW << employees->data[index].bankbranch << RESET << "\n";

    int choice;
    cout << BLUE << "\nWhat would you like to modify? (1–6, 0 to cancel): " << RESET;
    cin >> choice;

    switch (choice) {

    case 1: { // Modify Name
        string newName;
        do {
            cout << BLUE << "Enter new Name: " << RESET;
            cin >> newName;

            if (!isAlphabetic(newName))
                cout << RED << "[ERROR] Only letters allowed!\n" << RESET;

        } while (!isAlphabetic(newName));

        employees->data[index].name = newName;
        break;
    }

    case 2: { // Modify Last Name
        string newLast;
        do {
            cout << BLUE << "Enter new Last Name: " << RESET;
            cin >> newLast;

            if (!isAlphabetic(newLast))
                cout << RED << "[ERROR] Only letters allowed!\n" << RESET;

        } while (!isAlphabetic(newLast));

        employees->data[index].lastName = newLast;
        break;
    }

    case 3: // Modify Address
        cin.ignore();
        bool badAddress;
        do {
            cout << BLUE << "Enter Address: " << RESET;
            getline(cin, employees->data[index].address);

            badAddress = false;
            for (int i = 0; i < employees->data[index].address.size(); i++) {
                if (!isalnum(employees->data[index].address[i]) && employees->data[index].address[i] != ' ') {   // only letters, numbers, spaces
                    badAddress = true;
                    break;
                }
            }

            if (badAddress)
                cout << RED << "[ERROR] Address can only contain letters, digits, and spaces.\n" << RESET;

        } while (badAddress);
		break;

    case 4: { // Modify Salary
        double newSalary;
        do {
            cout << BLUE << "Enter new Salary (TND): " << RESET;
            cin >> newSalary;

            if (newSalary < 0)
                cout << RED << "[ERROR] Salary cannot be negative!\n" << RESET;

        } while (newSalary < 0);

        employees->data[index].salary = newSalary;
        break;
    }

    case 5: { // Modify Hire Date
        string newHire;
        bool bad;

        do {
            cout << BLUE << "Enter new Hire Date (DD/MM/YYYY): " << RESET;
            cin >> newHire;

            bad =
                newHire.length() != 10 ||
                newHire[2] != '/' ||
                newHire[5] != '/' ||
                !isNumeric(newHire.substr(0, 2)) ||
                !isNumeric(newHire.substr(3, 2)) ||
                !isNumeric(newHire.substr(6, 4));

            if (bad)
                cout << RED << "[ERROR] Invalid date format!\n" << RESET;

        } while (bad);

        employees->data[index].hireDate = newHire;
        break;
    }

    case 6: { // Modify Branch
        do {
            cout << BLUE << "Enter Branch Code: " << RESET;
            cin >> employees->data[index].bankbranch;

            if (employees->data[index].bankbranch < 0) {
                cout << RED << "[ERROR] Branch code must be a NON-negative number!\n" << RESET;
            }

        } while (employees->data[index].bankbranch < 0);
		break;
    }

    case 0:
        cout << YELLOW << "[CANCELLED] Modification cancelled.\n" << RESET;
        return;

    default:
        cout << RED << "[ERROR] Invalid choice!\n" << RESET;
        return;
    }

    cout << GREEN << "\n[SUCCESS] Employee modified successfully!\n" << RESET;
}
// ============================================================
//      DISPLAY EMPLOYEES ALPHABETICALLY (BY LAST NAME)
// ============================================================

void displayEmployeesAlphabetically(EmployeeArray* employees) {

    if (!employees) return;

    if (employees->size == 0) {
        cout << RED << "\n[INFO] No employees to display!\n" << RESET;
        return;
    }

    sortEmployeesByLastName(employees);

    cout << CYAN << "\n========== EMPLOYEES (ALPHABETICAL ORDER) ==========\n" << RESET;

    cout << YELLOW
        << "ID\tName\t\t\tSalary\t\tBranch\tHire Date\n"
        << "----------------------------------------------------------------\n"
        << RESET;

    for (int i = 0; i < employees->size; i++) {
        cout << GREEN << employees->data[i].id << RESET << "\t";

        cout << BLUE << employees->data[i].name << " "
            << employees->data[i].lastName << RESET << "\t\t";

        cout << YELLOW << employees->data[i].salary << " TND" << RESET << "\t";

        cout << MAGENTA << employees->data[i].bankbranch << RESET << "\t";

        cout << WHITE << employees->data[i].hireDate << RESET << "\n";
    }
}



// ============================================================
//               DISPLAY EMPLOYEES BY BRANCH
// ============================================================

void displayEmployeesByBranch(const EmployeeArray* employees) {

    if (!employees) return;

    if (employees->size == 0) {
        cout << RED << "\n[INFO] No employees to display!\n" << RESET;
        return;
    }

    cout << CYAN << "\n========== EMPLOYEES BY BRANCH ==========\n" << RESET;

    int* branches = new int[employees->size];
    int branchCount = 0;

    // Collect unique branch codes
    for (int i = 0; i < employees->size; i++) {

        bool found = false;

        for (int j = 0; j < branchCount; j++) {
            if (branches[j] == employees->data[i].bankbranch) {
                found = true;
                break;
            }
        }

        if (!found) {
            branches[branchCount] = employees->data[i].bankbranch;
            branchCount++;
        }
    }

    // Sort branch codes ascending
    for (int i = 0; i < branchCount - 1; i++) {
        for (int j = 0; j < branchCount - i - 1; j++) {
            if (branches[j] > branches[j + 1]) {
                int temp = branches[j];
                branches[j] = branches[j + 1];
                branches[j + 1] = temp;
            }
        }
    }

    // Display branch groups
    for (int i = 0; i < branchCount; i++) {

        cout << MAGENTA << "\n--- Branch " << branches[i];

        if (branches[i] == 1)
            cout << " (Head Office)";

        cout << " ---\n" << RESET;

        for (int j = 0; j < employees->size; j++) {

            if (employees->data[j].bankbranch == branches[i]) {

                cout << BLUE << "ID: " << RESET
                    << YELLOW << employees->data[j].id << RESET << " | ";

                cout << GREEN << employees->data[j].name << " "
                    << employees->data[j].lastName << RESET << " | ";

                cout << WHITE << "Salary: " << employees->data[j].salary
                    << " TND\n" << RESET;
            }
        }
    }

    delete[] branches;
}



// ============================================================
//          DISPLAY MOST RECENT + EARLIEST HIRED EMPLOYEE
// ============================================================

void displayEmployeesRecentEarliest(const EmployeeArray* employees) {

    if (!employees) return;

    if (employees->size == 0) {
        cout << RED << "\n[INFO] No employees to display!\n" << RESET;
        return;
    }

    if (employees->size == 1) {

        cout << CYAN << "\n========== HIRE DATE SUMMARY ==========\n" << RESET;

        cout << YELLOW << "Only one employee in the system:\n" << RESET;

        cout << GREEN << employees->data[0].id << RESET << " | ";
        cout << BLUE << employees->data[0].name << " "
            << employees->data[0].lastName << RESET << " | ";
        cout << WHITE << "Hire Date: " << employees->data[0].hireDate << RESET << "\n";

        return;
    }

    int earliestIdx = 0;
    int recentIdx = 0;

    for (int i = 1; i < employees->size; i++) {

        string dEarliest = convertDate2(employees->data[earliestIdx].hireDate);
        string dRecent = convertDate2(employees->data[recentIdx].hireDate);
        string dCurrent = convertDate2(employees->data[i].hireDate);

        if (dCurrent < dEarliest)
            earliestIdx = i;

        if (dCurrent > dRecent)
            recentIdx = i;
    }

    cout << CYAN << "\n========== HIRE DATE SUMMARY ==========\n" << RESET;

    // -------------------- MOST RECENTLY HIRED --------------------
    cout << GREEN << "\nMost Recently Hired Employee:\n" << RESET;

    cout << YELLOW << "ID: " << RESET << employees->data[recentIdx].id << "\n";
    cout << YELLOW << "Name: " << RESET
        << employees->data[recentIdx].name << " "
        << employees->data[recentIdx].lastName << "\n";
    cout << YELLOW << "Hire Date: " << RESET
        << employees->data[recentIdx].hireDate << "\n";
    cout << YELLOW << "Salary: " << RESET
        << employees->data[recentIdx].salary << " TND\n";
    cout << YELLOW << "Branch: " << RESET
        << employees->data[recentIdx].bankbranch << "\n";

    // -------------------- EARLIEST HIRED -------------------------
    cout << BLUE << "\nEarliest Hired Employee:\n" << RESET;

    cout << YELLOW << "ID: " << RESET << employees->data[earliestIdx].id << "\n";
    cout << YELLOW << "Name: " << RESET
        << employees->data[earliestIdx].name << " "
        << employees->data[earliestIdx].lastName << "\n";
    cout << YELLOW << "Hire Date: " << RESET
        << employees->data[earliestIdx].hireDate << "\n";
    cout << YELLOW << "Salary: " << RESET
        << employees->data[earliestIdx].salary << " TND\n";
    cout << YELLOW << "Branch: " << RESET
        << employees->data[earliestIdx].bankbranch << "\n";
}
// ============================================================
//      ADD CUSTOMER ACCOUNT
// ============================================================

void addCustomerAccount(CustomerArray& customers) {

    cout << CYAN << "\n=== ADD NEW CUSTOMER ACCOUNT ===\n" << RESET;
	char choice;

    customer c;
    do {
        cout << YELLOW << "Enter account number: " << RESET;
        cin >> c.accountnumber;
		cin.ignore();
        if (c.accountnumber < 0) {
            cout << RED << "[ERROR] Account number must be a positive integer!\n" << RESET;
		}
	} while (c.accountnumber < 0);

    // UNIQUE ID VALIDATION
    while (findCustomerByAccountNumber(customers, c.accountnumber) != -1) {
        cout << RED << "[ERROR] This account number already exists. Please enter a unique number.\n"
            << RESET;
		cout << GREEN << "Would you like to try again ? (Y/N): \n" << RESET;
        cin >> choice;
        if (choice == 'N' || choice == 'n') {
            cout << YELLOW << "Account creation cancelled.\n" << RESET;
            return;
		}
        else if (choice == 'Y' || choice == 'y') {
            cout << YELLOW << "Enter account number: " << RESET;
            cin >> c.accountnumber;
            cin.ignore();
		}
        else {
            cout << RED << "Invalid choice. Account creation cancelled.\n" << RESET;
            return;

        }
        
    }

    cout << YELLOW
        << "Enter account type (savings / checking / current / business / student): "
        << RESET;

    cin >> c.accounttype;
    cin.ignore();

    // Convert user input to lowercase using normal for-loop
    for (int i = 0; i < c.accounttype.length(); i++)
        c.accounttype[i] = tolower(c.accounttype[i]);

    // Validate input
    while (c.accounttype != "savings" &&
        c.accounttype != "checking" &&
        c.accounttype != "current" &&
        c.accounttype != "business" &&
        c.accounttype != "student")
    {
        cout << RED
            << "Invalid account type.\n"
            << "Available types are: savings, checking, current, business, student.\n\n"
            << RESET;

        cout << YELLOW
            << "Enter account type (savings / checking / current / business / student): "
            << RESET;

        cin >> c.accounttype;
        cin.ignore();

        for (int i = 0; i < c.accounttype.length(); i++)
            c.accounttype[i] = tolower(c.accounttype[i]);
    }

    string ibanInput;
    bool badIBAN;

    do {
        badIBAN = false;

        cout << YELLOW << "Enter IBAN: " << RESET;
        cin >> ibanInput;

        // Validate: only letters and numbers (index-based loop)
        for (int i = 0; i < ibanInput.length(); i++) {
            if (!isalnum(ibanInput[i])) {   // rejects symbols, spaces, punctuation
                badIBAN = true;
                break;
            }
        }

        if (badIBAN) {
            cout << RED << "[ERROR] IBAN can only contain letters and digits! No spaces or symbols allowed.\n"
                << RESET;
        }

    } while (badIBAN);

    c.IBAN = ibanInput;
    cin.ignore();

    // ---------- Branch Code ----------
    do {
        cout << YELLOW << "Enter branch code: " << RESET;
        cin >> c.branchcode;

        if ( c.branchcode < 0) {
            cout << RED << "[ERROR] Branch code must be a NON-negative number!\n" << RESET;
        }

    } while (c.branchcode < 0);

    cin.ignore();  // clear leftover newline


    // ---------- Account Holder Name ----------
    bool badName;
    do {
        badName = false;
        cout << YELLOW << "Enter account holder name: " << RESET;
        getline(cin, c.accountholdername);

        // Only letters and spaces allowed
        for (int i = 0; i < c.accountholdername.length(); i++) {
            char ch = c.accountholdername[i];
            if (!isalpha(ch) && ch != ' ') {
                badName = true;
                break;
            }
        }

        if (badName)
            cout << RED << "[ERROR] Name must contain only alphabetic characters and spaces!\n" << RESET;

    } while (badName);


    // ---------- Opening Date (DD/MM/YYYY) ----------
    bool badDate;
    do {
        cout << YELLOW << "Enter opening date (DD/MM/YYYY): " << RESET;
        cin >> c.openingdate;

        badDate =
            c.openingdate.length() != 10 ||
            c.openingdate[2] != '/' ||
            c.openingdate[5] != '/' ||
            !isNumeric(c.openingdate.substr(0, 2)) ||
            !isNumeric(c.openingdate.substr(3, 2)) ||
            !isNumeric(c.openingdate.substr(6, 4)) ||
            c.openingdate.substr(0, 2) > "31" ||
            c.openingdate.substr(3, 2) > "12" ||
            c.openingdate.substr(6, 4) > "2025";

        if (badDate)
            cout << RED << "[ERROR] Invalid date! Use DD/MM/YYYY and valid day/month/year.\n" << RESET;

    } while (badDate);

    cin.ignore(); // clear newline


    // ---------- Initial Balance ----------
    do {
        cout << YELLOW << "Enter initial balance: " << RESET;
        cin >> c.balance;

        if ( c.balance < 0) {
  
            cout << RED << "[ERROR] Balance must be a NON-negative number!\n" << RESET;
        }

    } while (c.balance < 0);

    cin.ignore();  // cleanup


    // ⭐⭐ IMPORTANT INITIALIZATION ⭐⭐
    c.Status = "active";
    c.loans = createList();             // initialize empty linked list
    c.dailytransaction.Top = 0;         // initialize empty transaction stack

    if (addCustomer(customers, c)) {
        cout << GREEN << "[SUCCESS] Customer account added.\n" << RESET;
    }
    else {
        cout << RED << "[ERROR] Failed to add customer.\n" << RESET;
    }
}



// ============================================================
//      DISPLAY CUSTOMER ACCOUNTS
// ============================================================

void displayAccounts(const CustomerArray& customers) {

    if (customers.size == 0) {
        cout << RED << "\n[INFO] No accounts to display!\n" << RESET;
        return;
    }

    cout << CYAN << "\n==================== LIST OF ACCOUNTS ====================\n" << RESET;

    // Table Header
    cout << YELLOW
        << left << setw(5) << "No"
        << setw(15) << "Acc Number"
        << setw(12) << "Type"
        << setw(32) << "IBAN"            // wider for readability
        << setw(10) << "Branch"
        << setw(20) << "Holder Name"
        << setw(15) << "Open Date"
        << setw(12) << "Status"
        << setw(10) << "Balance"
        << setw(8) << "Loans"
        << setw(8) << "Trans"
        << RESET << "\n";

    cout << CYAN << string(150, '-') << RESET << "\n";

    // Table Rows
    for (int i = 0; i < customers.size; i++) {

        string statusColor =
            customers.data[i].Status == "active" ? GREEN :
            customers.data[i].Status == "inactive" ? CYAN : RED;

        cout << WHITE
            << left << setw(5) << i + 1
            << setw(15) << customers.data[i].accountnumber
            << setw(12) << customers.data[i].accounttype
            << setw(32) << customers.data[i].IBAN        // wider
            << setw(10) << customers.data[i].branchcode  // now spaced correctly
            << setw(20) << customers.data[i].accountholdername
            << setw(15) << customers.data[i].openingdate
            << statusColor << setw(12) << customers.data[i].Status << RESET
            << WHITE << setw(10) << customers.data[i].balance
            << setw(8) << listSize(customers.data[i].loans)
            << setw(8) << customers.data[i].dailytransaction.Top
            << RESET << "\n";
    }

    cout << CYAN << string(150, '-') << "\n";
    cout << "======================== END OF LIST =======================\n" << RESET;
}




// ============================================================
//      CHANGE ACCOUNT STATUS
// ============================================================

void changeStatus(CustomerArray& customers) {

    if (customers.size == 0) {
        cout << RED << "\n[INFO] No accounts available.\n" << RESET;
        return;
    }

    cout << CYAN << "\nEnter account number to modify status: " << RESET;

    int id;
    cin >> id;

    while (findCustomerByAccountNumber(customers, id) == -1) {
        cout << RED << "[ERROR] Invalid account number." << RESET << "\n";
        cout << YELLOW << "Retry or enter 0 to exit: " << RESET;
        cin >> id;

        if (id == 0) return;
    }

    cout << YELLOW << "Enter new status (active / inactive / closed): " << RESET;

    string newStat;
    cin >> newStat;

    if (newStat == "active" || newStat == "inactive" || newStat == "closed") {

        customers.data[findCustomerByAccountNumber(customers, id)].Status = newStat;

        cout << GREEN << "[SUCCESS] Status updated.\n" << RESET;
    }
    else {
        cout << RED << "[ERROR] Invalid status.\n" << RESET;
    }
}



// ============================================================
//      DELETE CLOSED ACCOUNTS (ARCHIVE THEM)
// ============================================================

void deleteClosed(CustomerArray& customers, CustomerArray& archive) {

    if (customers.size == 0) {
        cout << RED << "No accounts found.\n" << RESET;
        return;
    }

    int i = 0;
    bool foundClosed = false;

    while (i < customers.size) {

        if (customers.data[i].Status == "closed") {

            foundClosed = true;

            // Display the account being archived
            cout << MAGENTA << "\n=== CLOSED ACCOUNT ARCHIVED ===\n" << RESET;
            cout << YELLOW << "Account Number:  " << RESET << customers.data[i].accountnumber << "\n";
            cout << YELLOW << "Account Type:    " << RESET << customers.data[i].accounttype << "\n";
            cout << YELLOW << "IBAN:            " << RESET << customers.data[i].IBAN << "\n";
            cout << YELLOW << "Holder Name:     " << RESET << customers.data[i].accountholdername << "\n";
            cout << YELLOW << "Branch Code:     " << RESET << customers.data[i].branchcode << "\n";
            cout << YELLOW << "Opening Date:    " << RESET << customers.data[i].openingdate << "\n";
            cout << YELLOW << "Balance:         " << RESET << customers.data[i].balance << "\n";

            if (archive.size >= MAX_CUSTOMERS) {
                cout << RED << "[ERROR] Archive is full. Account was not removed.\n" << RESET;
                return;
            }

            // Move to archive
            archive.data[archive.size] = customers.data[i];
            archive.size++;

            // Remove from customer list
            deleteCustomer(customers, customers.data[i]);

            cout << GREEN << "[SUCCESS] Account moved to archive.\n" << RESET;
        }
        else {
            i++;
        }
    }

    if (!foundClosed) {
        cout << BLUE << "No closed accounts found.\n" << RESET;
    }
    else {
        cout << CYAN << "\nAll closed accounts archived successfully.\n" << RESET;
    }
}



// ============================================================
//      DISPLAY LOANS OF ONE CUSTOMER
// ============================================================

void displayLoans(CustomerArray& customers) {

    if (customers.size == 0) {
        cout << RED << "No customer accounts available.\n" << RESET;
        return;
    }

    cout << CYAN << "Enter account number to display loans: " << RESET;

    int id;
    cin >> id;

    while (findCustomerByAccountNumber(customers, id) == -1) {
        cout << RED << "[ERROR] Invalid account number.\n" << RESET;
        cout << YELLOW << "Retry or enter 0 to exit: " << RESET;
        cin >> id;
        if (id == 0) return;
    }

    customer c = customers.data[findCustomerByAccountNumber(customers, id)];
    List L = c.loans;

    if (isEmpty(L)) {
        cout << RED << "\nCustomer has NO loans.\n" << RESET;
        return;
    }

    cout << CYAN << "\n===== LOANS FOR " << c.accountholdername << " =====\n" << RESET;
    displayList(L);
}


// ============================================================
//                  CHANGE LOAN STATUS
// ============================================================

void changeloanstatus(CustomerArray& customers) {
    if (customers.size == 0) {
        cout << RED << "No customers available.\n" << RESET;
        return;
    }

    cout << CYAN << "\n===== CHANGE LOAN STATUS =====\n" << RESET;

    int accountNum;
    cout << YELLOW << "Enter account number: " << RESET;
    cin >> accountNum;

    int idx = findCustomerByAccountNumber(customers, accountNum);
    if (idx == -1) {
        cout << RED << "[ERROR] Account not found.\n" << RESET;
        return;
    }

    customer& c = customers.data[idx];

    if (isEmpty(c.loans)) {
        cout << RED << "This customer has no loans.\n" << RESET;
        return;
    }

    cout << CYAN << "\n--- Loans for " << c.accountholdername << " ---\n" << RESET;
    displayList(c.loans);

    int loanID;
    cout << YELLOW << "\nEnter Loan ID to change status: " << RESET;
    cin >> loanID;

    Node* current = c.loans.head;
    bool found = false;

    while (current) {
        if (current->data.loanID == loanID) {
            found = true;
            cout << YELLOW << "Current status: " << RESET << current->data.loanstatus << "\n";
            cout << YELLOW << "Enter new status (active/completed/overdue): " << RESET;
            string newStatus;
            cin >> newStatus;

            if (newStatus == "active" || newStatus == "completed" || newStatus == "overdue") {
                current->data.loanstatus = newStatus;
                cout << GREEN << "[SUCCESS] Loan status updated to " << newStatus << "\n" << RESET;
            }
            else {
                cout << RED << "[ERROR] Invalid status.\n" << RESET;
            }
            break;
        }
        current = current->next;
    }

    if (!found) {
        cout << RED << "[ERROR] Loan ID not found.\n" << RESET;
    }
}

// ============================================================
//      MOVE COMPLETED LOANS TO ARCHIVE
// ============================================================

void moveCompletedLoansToArchive(CustomerArray& customers, CompletedLoanList& completedLoans) {

    cout << CYAN << "\n========== ARCHIVING COMPLETED LOANS ==========\n" << RESET;

    int movedCount = 0;

    for (int i = 0; i < customers.size; ++i) {

        cout << MAGENTA << "\nChecking customer: "
            << customers.data[i].accountholdername
            << " (Account " << customers.data[i].accountnumber << ")\n" << RESET;

        List& loans = customers.data[i].loans;

        int pos = 1;
        Node* current = loans.head;

        while (current != nullptr) {

            Node* nextNode = current->next;

            if (current->data.loanstatus == "completed") {

                cout << GREEN << "\n--- COMPLETED LOAN FOUND ---\n" << RESET;

                // ⭐ DISPLAY LOAN DETAILS ⭐
                cout << YELLOW << "Loan ID:            " << RESET << current->data.loanID << "\n";
                cout << YELLOW << "Loan Type:          " << RESET << current->data.loantype << "\n";
                cout << YELLOW << "Principal Amount:   " << RESET << current->data.principalamount << "\n";
                cout << YELLOW << "Interest Rate:      " << RESET << current->data.interestrate << "%\n";
                cout << YELLOW << "Amount Paid:        " << RESET << current->data.amountpaid << "\n";
                cout << YELLOW << "Remaining Balance:  " << RESET << current->data.remainingbalance << "\n";
                cout << YELLOW << "Start Date:         " << RESET << current->data.startdate << "\n";
                cout << YELLOW << "End Date:           " << RESET << current->data.enddate << "\n";
                cout << YELLOW << "Status:             " << GREEN << current->data.loanstatus << RESET << "\n";

                cout << BLUE << "[INFO] Archiving this loan...\n" << RESET;

                // Move loan to completed archive
                insert2(&completedLoans, current->data, completedLoans.size + 1);

                // Remove from customer loan list
                removeAt(&loans, pos);
                movedCount++;
            }
            else {
                pos++;
            }

            current = nextNode;
        }
    }

    if (movedCount == 0)
        cout << RED << "\nNo completed loans found.\n" << RESET;
    else
        cout << GREEN << "\nArchived " << movedCount << " completed loan(s).\n" << RESET;
}




// ============================================================
//      MANAGE LOAN REQUEST QUEUE (FIFO)
// ============================================================

void manageLoanRequests(CustomerArray& customers, Queue* loanRequests) {

    if (!loanRequests || IsEmpty(*loanRequests)) {
        cout << RED << "\n[INFO] No pending loan requests.\n" << RESET;
        return;
    }

    cout << CYAN << "\n========== MANAGE LOAN REQUESTS ==========\n" << RESET;

    bool stop = false;

    while (!IsEmpty(*loanRequests) && !stop) {

        Loanrequest current = FrontElement(*loanRequests);

        cout << YELLOW << "\n----- NEXT REQUEST -----\n" << RESET;
        cout << "Request ID:       " << current.requestID << "\n";
        cout << "Account Number:   " << current.accountNumber << "\n";
        cout << "Name:             " << current.customerName << "\n";
        cout << "Loan Type:        " << current.loanType << "\n";
        cout << "Amount:           " << current.requestedAmount << "\n";
        cout << "Duration:         " << current.durationYears << " years\n";
        cout << "Status:           " << current.status << "\n";

        char decision;

        do {
            cout << CYAN << "[A]ccept  [D]ecline  [Q]uit: " << RESET;
            cin >> decision;
            decision = tolower(decision);
        } while (decision != 'a' && decision != 'd' && decision != 'q');

        if (decision == 'q') {
            cout << YELLOW << "[INFO] Stopping. Current request remains.\n" << RESET;
            stop = true;
        }
        else if (decision == 'd') {
            cout << RED << "[DECLINED] Request removed.\n" << RESET;
            Dequeue(loanRequests);
        }
        else {

            int accNumber;
            cout << YELLOW << "Enter customer account number (0 = cancel): " << RESET;
            cin >> accNumber;

            if (accNumber == 0 || accNumber != current.accountNumber) {
                cout << RED << "[CANCELLED] Request remains pending for its original account.\n" << RESET;
                stop = true;
            }
            else {

                int idx = findCustomerByAccountNumber(customers, accNumber);

                if (idx == -1) {
                    cout << RED << "[ERROR] Account not found. Request remains pending.\n" << RESET;
                    stop = true;
                }
                else {

                    loan newLoan;
                    newLoan.loanID = current.requestID;
                    newLoan.accountnumber = current.accountNumber;
                    newLoan.loantype = current.loanType;
                    newLoan.principalamount = current.requestedAmount;
                    newLoan.amountpaid = 0;
                    newLoan.remainingbalance = current.requestedAmount;
                    newLoan.startdate = current.requestDate;
                    newLoan.enddate = calculateEndDate(current.requestDate, current.durationYears);

                    cout << CYAN << "Enter interest rate (%): " << RESET;
                    cin >> newLoan.interestrate;

                    newLoan.loanstatus = "active";

                    List& loans = customers.data[idx].loans;
                    insert(&loans, newLoan, loans.size + 1);

                    cout << GREEN << "[SUCCESS] Loan added to customer.\n" << RESET;

                    Dequeue(loanRequests);
                }
            }
        }
    }

    cout << CYAN << "\n[INFO] Loan request processing complete.\n" << RESET;
}



// ============================================================
//      FINALIZE DAILY TRANSACTIONS
// ============================================================

void finalizeDailyTransactions(CustomerArray& customers, List1& history) {

    if (customers.size == 0) {
        cout << RED << "\nNo customers available.\n" << RESET;
        return;
    }

    cout << CYAN << "\n===== FINALIZING DAILY TRANSACTIONS =====\n" << RESET;

    int totalArchived = 0;

    for (int i = 0; i < customers.size; ++i) {

        customer& c = customers.data[i];

        if (!isEmpty(c.dailytransaction)) {

            cout << MAGENTA << "\nArchiving for Account "
                << c.accountnumber << " (" << c.accountholdername << ")\n" << RESET;

            while (!isEmpty(c.dailytransaction)) {

                transaction t = top(c.dailytransaction);
                if (insertAtEnd3(&history, t)) {
                    pop(&c.dailytransaction);
                    totalArchived++;
                }
                else {
                    cerr << RED << "[ERROR] Failed to archive transaction.\n" << RESET;
                    break;
                }
            }
        }
    }

    if (totalArchived == 0)
        cout << RED << "\nNo transactions recorded today.\n" << RESET;
    else
        cout << GREEN << "\nArchived " << totalArchived << " transactions.\n" << RESET;
}



// ============================================================
//      EMPLOYEE LOGIN
// ============================================================

int loginEmployee(const EmployeeArray* employees) {

    if (!employees) return -1;

    cout << CYAN << "===== EMPLOYEE LOGIN =====\n" << RESET;

    int idTest;
    string nameTest, lastNameTest;

    cout << YELLOW << "Enter Employee ID: " << RESET;
    cin >> idTest;
    cin.ignore();

    cout << YELLOW << "Enter First Name: " << RESET;
    getline(cin, nameTest);

    cout << YELLOW << "Enter Last Name: " << RESET;
    getline(cin, lastNameTest);

    for (int i = 0; i < employees->size; i++) {

        bool match =
            idTest == employees->data[i].id &&
            nameTest == employees->data[i].name &&
            lastNameTest == employees->data[i].lastName;

        if (match) {
            cout << GREEN << "\nLogin SUCCESS! Welcome, "
                << employees->data[i].name << ".\n" << RESET;
            return i;
        }
    }

    cout << RED << "\n[ERROR] Incorrect login details.\n" << RESET;
    return -1;
}
