# Banking Management System

A console based banking simulation written in C++ for a data structures project. It manages customer accounts, employees, loans, transactions, and summary statistics using manually implemented arrays, linked lists, stacks, and queues. Records are loaded from CSV files at startup and saved back to CSV when the application exits or a user leaves an interface.

> **Educational project:** This is a simulation, not software for real banking or real customer data. Login uses details from the sample records; it does not provide password based security.

## Features

### Customer interface

- Sign in with an active account number and account holder name.
- View loans and their principal, interest, payment, dates, and status.
- Submit a loan request for employee review.
- Deposit or withdraw Tunisian dinars (TND), view the current transaction stack, and undo the latest unfinalized transaction.

### Employee interface

- Add, edit, delete, sort, and group employees by branch; view earliest and latest hire dates.
- Add accounts, list accounts, change account status, and move closed accounts to an archive.
- View a customer's loans, change loan status, and archive completed loans.
- Accept or decline loan requests in first in, first out order.
- Finalize daily transactions into a transaction history that can no longer be undone.

### Statistics

- Total loans, loans by type and status, and active loans within a chosen date range.
- Customer with the most loans and accounts with the highest and lowest balances.
- Employee count and employee count by branch.

## Data structures

| Structure | Used for | Reason |
| --- | --- | --- |
| Fixed arrays | Customers, archived customers, employees | Direct indexed access with explicit capacity limits |
| Doubly linked list | Loans belonging to each customer | Traversal and removal of loan records |
| Stack | Unfinalized transactions for each account | Undo the most recent transaction first |
| Queue | Pending loan requests | Review requests in arrival order |
| Singly linked lists | Completed loans and finalized transaction history | Sequential archives |

The project implements these structures directly rather than using STL containers for its domain records.

## Project layout

```text
banking-management-system-cpp/
├── README.md
├── banking management system.sln
├── banking management system.vcxproj
├── banking management system.vcxproj.filters
├── src/                 C++ implementation and headers
│   ├── main(in progress).cpp
│   ├── customer.cpp
│   ├── EmployeeMethods.cpp
│   ├── statisticsmeth.cpp
│   └── ...
└── data/                Sample and persisted CSV records
    ├── customers.csv
    ├── employees.csv
    ├── loans.csv
    ├── loan_requests.csv
    ├── transactions.csv
    ├── archived_customers.csv
    ├── completed_loans.csv
    └── transaction_history.csv
```

The Visual Studio filters retain the feature grouping shown in the original solution: customer features, employee features, the statistics module, and their supporting data structures.

The `tests/` folder contains a small smoke check for loading, persistence, transaction undo, closed account archiving, and queue behavior.

## Build and run

### Visual Studio on Windows

1. Open `banking management system.sln` in Visual Studio with the **Desktop development with C++** workload installed.
2. Select an `x64` Debug or Release configuration and build the solution.
3. Start the application from Visual Studio. The project sets its working directory to the repository root so it can find `data/*.csv`.

### g++ on Windows

From the repository root in PowerShell:

```powershell
g++ -std=c++17 -o banking-management-system.exe src\*.cpp
.\banking-management-system.exe
```

Run the program from the repository root. Its relative CSV paths are `data/*.csv`. The console menus use Windows `pause` and `cls` commands, so Windows is the supported interactive environment.

To run the smoke check with g++, use `powershell -File tests/run-smoke.ps1` from the repository root. It tests on a copy of the CSV files under `tests/run/` so the sample data is preserved.

The included CSVs provide example data. For a quick demonstration, sign in as customer account `1001` with the name `Ahmed Ben Ali`, or as employee ID `2001` with first name `Mohamed` and last name `Ksouri`. These are sample records, not secure credentials.

## Data persistence

The application loads customers, employees, loans, loan requests, pending transactions, and archives from `data/`. It writes updated records to those files on exit and after leaving the customer or employee interface. Pending transactions stay on each customer's stack until they are undone or an employee finalizes the day. Finalized transactions move to `transaction_history.csv`.

Because running the application changes the CSV files, make a copy of `data/` if you want to keep the initial sample records. CSV parsing expects the provided column order and simple comma separated fields; values containing commas are not supported. Arrays and transaction stacks have fixed capacities.

## Technical notes

The code is organized around separate menu functions and hand written data structure operations. It practices pointer manipulation, file handling, date comparison, and serialization across sessions. It is intentionally a learning project and does not include production features such as encrypted credentials, database transactions, or multiuser access.
