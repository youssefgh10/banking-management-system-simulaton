#include <iostream>
#include "datamethods.h"
#include <string>
using namespace std;
void loadCustomers(CustomerArray& customers) {
	ifstream file("data/customers.csv");//ifstream open this file mech nejmou nakraweh
	// check if the file exists makenchi nebdew b arrat taa customers feragh(yaani ahna ndakhlou data)
	if (!file.is_open()) {
		cout << "Warning: customers.csv not found. Starting with empty data.\n";
		customers.size = 0;
		return;
	}
	string line;// mech nakraw el file line by line
	getline(file, line);//Read one line from the file and store it in line
	//mech naamlou skip el awel line khater howa fih el headers mouch el data
	customers.size = 0;// We'll increment this as we add each customer
	while (getline(file, line) && customers.size < MAX_CUSTOMERS) {//Stops when No more lines to read OR Array is full
		stringstream ss(line);//puisque kol star fih data mabinethom ",",stringstream kol matelka ","tofsol el data heki
		string temp;//temp will hold each piece of data we extract
		customer& c = customers.data[customers.size];
		getline(ss, temp, ',');//Read from ss until you hit a comma , ou nhotohom fi temp
		c.accountnumber = stoi(temp);//convert string to int
		getline(ss, c.accounttype, ',');// mech nhotouha direct fi c.accounttype puisque string betbi3etha
		getline(ss, c.IBAN, ',');
		getline(ss, temp, ',');
		c.branchcode = stoi(temp);
		getline(ss, c.accountholdername, ',');
		getline(ss, c.openingdate, ',');
		getline(ss, c.Status, ',');
		getline(ss, temp, ',');
		c.balance = stod(temp); //nhawlouh el double
		c.loans = createList();//emptydoublylinkedlist
		c.dailytransaction.Top = 0;//empty stack
		customers.size++;
	}
	file.close();
	cout << "Loaded " << customers.size << " customers.\n"; //Tell user how many customers were loaded


}
//el be9i el kol fard principe benesba lel load
void loadLoans(CustomerArray& customers) {
	ifstream file("data/loans.csv");
	if (!file.is_open()) {
		cout << "Warning: loan.csv not found. Starting with empty data.\n";
		return;
	}
	string line;
	getline(file, line);
	int count = 0;
	while (getline(file, line)) {
		if (line.empty()) continue;
		stringstream ss(line);
		string temp;
		loan newloan;
		int accountnum;
		getline(ss, temp, ',');
		newloan.loanID = stoi(temp);
		getline(ss, temp, ',');
		accountnum = stoi(temp);
		newloan.accountnumber = accountnum;
		getline(ss, newloan.loantype, ',');
		getline(ss, temp, ',');
		newloan.principalamount = stod(temp);
		getline(ss, temp, ',');
		newloan.interestrate = stod(temp);
		getline(ss, temp, ',');
		newloan.amountpaid = stod(temp);
		getline(ss, temp, ',');
		newloan.remainingbalance = stod(temp);
		getline(ss, newloan.startdate, ',');
		getline(ss, newloan.enddate, ',');
		getline(ss, newloan.loanstatus, ',');
		for (int i = 0; i < customers.size; i++) {
			if (customers.data[i].accountnumber == accountnum) {
				insert(&customers.data[i].loans, newloan, customers.data[i].loans.size + 1);;
				count++;
				break;
			}
		}
	}
	file.close();
	cout << "Loaded " << count << " loans.\n";
}


void loadEmployees(EmployeeArray& employees) {
	ifstream file("data/employees.csv");
	if (!file.is_open()) {
		cout << "Warning: employees.csv not found. Starting with empty data.\n";
		employees.size = 0;
		return;
	}
	string line;
	getline(file, line);  // Skip header

	employees.size = 0;

	while (getline(file, line) && employees.size < MAX_EMPLOYEES) {
		stringstream ss(line);
		string temp;
		Employee& e = employees.data[employees.size];
		getline(ss, temp, ',');
		e.id = stoi(temp);
		getline(ss, e.name, ',');
		getline(ss, e.lastName, ',');
		getline(ss, e.address, ',');
		getline(ss, temp, ',');
		e.salary = stod(temp);
		getline(ss, e.hireDate, ',');
		getline(ss, temp, ',');
		e.bankbranch = stoi(temp);
		employees.size++;
	}
	file.close();
	cout << "Loaded " << employees.size << " employees.\n";
}
void loadTransactions(CustomerArray& customers) {
	ifstream file("data/transactions.csv");
	if (!file.is_open()) {
		cout << "Warning: transactions.csv not found.Starting with empty data.\n";
		return;
	}
	string line;
	getline(file, line);
	int transCount = 0;
	while (getline(file, line)) {
		stringstream ss(line);
		string token;
		transaction newTrans;
		int accountNum;
		getline(ss, token, ',');
		newTrans.transactionID = stoi(token);
		getline(ss, token, ',');
		accountNum = stoi(token);
		getline(ss, newTrans.type, ',');
		getline(ss, token, ',');
		newTrans.amount = stod(token);
		getline(ss, newTrans.Date, ',');
		// Find customer and add to their stack
		for (int i = 0; i < customers.size; i++) {
			if (customers.data[i].accountnumber == accountNum) {
				newTrans.accountnumber = accountNum;
				stack& daily = customers.data[i].dailytransaction;
				if (daily.Top < Max - 1) {
					// The CSV is saved newest first; insert each row at the bottom.
					for (int j = daily.Top; j >= 1; --j) daily.data[j + 1] = daily.data[j];
					daily.data[1] = newTrans;
					++daily.Top;
					++transCount;
				}
				break;
			}
		}
	}
	file.close();
	cout << "Loaded " << transCount << " transactions.\n";
}
void loadLoanRequests(Queue& loanRequestQueue) {
	ifstream file("data/loan_requests.csv");
	if (!file.is_open()) {
		cout << "Warning: loan_requests_queue.csv not found. Starting with empty data.\n";
		return;
	}
	string line;
	getline(file, line); // Skip header
	loanRequestQueue.Front = 0;
	loanRequestQueue.Tail = 0;
	int count = 0;
	while (getline(file, line)) {
		stringstream ss(line);
		string temp;
		Loanrequest newloan;
		getline(ss, temp, ',');
		newloan.requestID = stoi(temp);
		getline(ss, temp, ',');
		newloan.accountNumber = stoi(temp);
		getline(ss, newloan.customerName, ',');
		getline(ss, newloan.loanType, ',');
		getline(ss, temp, ',');
		newloan.requestedAmount = stod(temp);
		getline(ss, newloan.requestDate, ',');
		getline(ss, newloan.status, ',');
		getline(ss, temp, ',');
		newloan.durationYears = stoi(temp);
		Enqueue(&loanRequestQueue,newloan,true);
		count++;
	}
	file.close();
	cout << "Loaded " << count << " loan requests.\n";
}
void loadArchivedCustomers(CustomerArray& archivedCustomers) {
	ifstream file("data/archived_customers.csv");
	if (!file.is_open()) {
		cout << "Warning: archived_customers.csv not found.\n";
		archivedCustomers.size = 0;
		return;
	}
	string line;
	getline(file, line);  // Skip header
	archivedCustomers.size = 0;
	while (getline(file, line) && archivedCustomers.size < MAX_CUSTOMERS) {
		stringstream ss(line);
		string token;
		customer& c = archivedCustomers.data[archivedCustomers.size];
		// Same format as customers.csv
		getline(ss, token, ',');
		c.accountnumber = stoi(token);
		getline(ss, c.accounttype, ',');
		getline(ss, c.IBAN, ',');
		getline(ss, token, ',');
		c.branchcode = stoi(token);
		getline(ss, c.accountholdername, ',');
		getline(ss, c.openingdate, ',');
		getline(ss, c.Status, ',');
		getline(ss, token, ',');
		c.balance = stod(token);
		c.loans = createList();
		c.dailytransaction.Top = 0;
		archivedCustomers.size++;
	}
	file.close();
	cout << "Loaded " << archivedCustomers.size << " archived customers.\n";
}
void loadCompletedLoans(CompletedLoanList& completedLoans) {
	ifstream file("data/completed_loans.csv");
	if (!file.is_open()) {
		cout << "Warning: completed_loans.csv not found.\n";
		return;
	}
	string line;
	getline(file, line);  // Skip header
	int count = 1;
	while (getline(file, line)) {
		stringstream ss(line);
		string token;
		loan completedLoan;
		// Parse same as loans.csv
		getline(ss, token, ',');
		completedLoan.loanID = stoi(token);
		getline(ss, token, ',');
		completedLoan.accountnumber = stoi(token);
		getline(ss, completedLoan.loantype, ',');
		getline(ss, token, ',');
		completedLoan.principalamount = stod(token);
		getline(ss, token, ',');
		completedLoan.interestrate = stod(token);
		getline(ss, token, ',');
		completedLoan.amountpaid = stod(token);
		getline(ss, token, ',');
		completedLoan.remainingbalance = stod(token);
		getline(ss, completedLoan.startdate, ',');
		getline(ss, completedLoan.enddate, ',');
		getline(ss, completedLoan.loanstatus, ',');
		insert2(&completedLoans, completedLoan, count);
		count++;
	}
	file.close();
	cout << "Loaded " << count-1 << " completed loans.\n";
}
void loadTransactionHistory(List1& transactionHistory) {
	ifstream file("data/transaction_history.csv");
	if (!file.is_open()) {
		cout << "Warning: transaction_history.csv not found.\n";
		return;
	}
	string line;
	getline(file, line);  // Skip header
	int count = 0;
	while (getline(file, line)) {
		stringstream ss(line);
		string token;
		transaction trans;
		// Parse CSV: transactionID,accountNumber,type,amount,date
		getline(ss, token, ',');
		trans.transactionID = stoi(token);
		getline(ss, token, ',');
		trans.accountnumber = stoi(token);
		getline(ss, trans.type, ',');
		getline(ss, token, ',');
		trans.amount = stod(token);
		getline(ss, trans.Date, ',');
		insertAtEnd3(&transactionHistory, trans);
		count++;
	}

	file.close();
	cout << "Loaded " << count << " archived transactions.\n";
}
// tawa save customers eli aandna ki naamlou functions that modify data
void saveCustomers(const CustomerArray& customers) {
	ofstream file("data/customers.csv"); // writing to a file (output)
	if (!file.is_open()) {
		cout << "Error: Cannot save customers.csv\n";
		return;
	}
	// tawa tkoulchi alina mech naamlou file jdid (ken fama wehed kdim i3awdhou)
	file << "accountNumber,accountType,iban,branchCode,accountHolderName,openingDate,status,balance\n";
	for (int i = 0; i < customers.size; i++) {
		const customer& c = customers.data[i];
		file << c.accountnumber << ","  //write each customer s data
			<< c.accounttype << ","
			<< c.IBAN << ","
			<< c.branchcode << ","
			<< c.accountholdername << ","
			<< c.openingdate << ","
			<< c.Status << ","
			<< c.balance << "\n";
	}
	file.close();
	cout << "Saved " << customers.size << " customers.\n";
}
void saveLoans(const CustomerArray& customers) {
	ofstream file("data/loans.csv");  // writing to a file (output)

	if (!file.is_open()) {
		cout << "Error: Cannot save loans.csv\n";
		return;
	}
	file << "loanID,accountNumber,loanType,principalAmount,interestRate,amountPaid,remainingBalance,startDate,endDate,loanStatus\n";
	for (int i = 0; i < customers.size; i++) {
		const customer& c = customers.data[i];
		Node* current = c.loans.head;
		while (current) {
			const loan& l = current->data;
			file << l.loanID << ","
				<< c.accountnumber << ","
				<< l.loantype << ","
				<< l.principalamount << ","
				<< l.interestrate << ","
				<< l.amountpaid << ","
				<< l.remainingbalance << ","
				<< l.startdate << ","
				<< l.enddate << ","
				<< l.loanstatus << "\n";
			current = current->next;
		}
	}
	file.close();
	cout << "Saved loans to file.\n";
}
void saveEmployees(const EmployeeArray& employees) {
	ofstream file("data/employees.csv"); // writing to a file (output)
	if (!file.is_open()) {
		cout << "Error: Cannot save employees.csv\n";
		return;
	}
	file << "id,name,lastName,address,salary,hireDate,branchCode\n";
	for (int i = 0; i < employees.size; i++) {
		const Employee& e = employees.data[i];
		file << e.id << ","
			<< e.name << ","
			<< e.lastName << ","
			<< e.address << ","
			<< e.salary << ","
			<< e.hireDate << ","
			<< e.bankbranch << "\n";
	}

	file.close();
	cout << "Saved " << employees.size << " employees.\n";
}
void saveTransactions(const CustomerArray& customers) {
	ofstream file("data/transactions.csv"); // writing to a file (output)
	if (!file.is_open()) {
		cout << "Error: Cannot save transactions.csv\n";
		return;
	}
	file << "transactionID,accountNumber,type,amount,date\n";
	int totalTransactions = 0;
	for (int i = 0; i < customers.size; i++) {
		const customer& c = customers.data[i];
		stack S = c.dailytransaction;
		while (!isEmpty(S)) {
			transaction t = pop(&S);
			file << t.transactionID << ","
				<< t.accountnumber << ","
				<< t.type << ","
				<< t.amount << ","
				<< t.Date << "\n";
			totalTransactions++;
		}
	}
	file.close();
	cout << "Saved " << totalTransactions << " transactions to file.\n";
}
void saveLoanRequests(const Queue& loanrequestQueue) {
	ofstream file("data/loan_requests.csv"); // writing to a file (output)
	if (!file.is_open()) {
		cout << "Error: Cannot save loan_requests.csv\n";
		return;
	}
	file << "requestID,accountNumber,customerName,loanType,requestedAmount,requestDate,status,durationYears\n";
	int loanRequestCount = 0;
	for (int i = loanrequestQueue.Front; i <= loanrequestQueue.Tail; i++) {
		const Loanrequest& r = loanrequestQueue.elements[i];
		file << r.requestID << ","
			<< r.accountNumber << ","
			<< r.customerName << ","
			<< r.loanType << ","
			<< r.requestedAmount << ","
			<< r.requestDate << ","
			<< r.status << ","
			<< r.durationYears << "\n";
		loanRequestCount++;
	}
	file.close();
	cout << "Saved " << loanRequestCount << " loan requests to file.\n";
}
void saveArchivedCustomers(const CustomerArray& archivedCustomers) {
	ofstream file("data/archived_customers.csv"); // writing to a file (output)
	if (!file.is_open()) {
		cout << "Error: Cannot save archived_customers.csv\n";
		return;
	}
	// Write header (same as customers.csv)
	file << "accountNumber,accountType,iban,branchCode,accountHolderName,openingDate,status,balance\n";
	// Write all archived customers
	for (int i = 0; i < archivedCustomers.size; i++) {
		const customer& c = archivedCustomers.data[i];

		file << c.accountnumber << ","
			<< c.accounttype << ","
			<< c.IBAN << ","
			<< c.branchcode << ","
			<< c.accountholdername << ","
			<< c.openingdate << ","
			<< c.Status << ","
			<< c.balance << "\n";
	}
	file.close();
	cout << "Saved " << archivedCustomers.size << " archived customers.\n";
}
void saveCompletedLoans(const CompletedLoanList& completedLoans) {
	ofstream file("data/completed_loans.csv"); // writing to a file (output)
	if (!file.is_open()) {
		cout << "Error: Cannot save completed_loans.csv\n";
		return;
	}
	file << "loanID,accountNumber,loanType,principalAmount,interestRate,amountPaid,remainingBalance,startDate,endDate,loanStatus\n";
	CompletedLoanNode* current = completedLoans.head;
	int count = 0;
	while (current) {
		const loan& l = current->data;
		file << l.loanID << ","
			<< l.accountnumber << ","
			<< l.loantype << ","
			<< l.principalamount << ","
			<< l.interestrate << ","
			<< l.amountpaid << ","
			<< l.remainingbalance << ","
			<< l.startdate << ","
			<< l.enddate << ","
			<< l.loanstatus << "\n";
		current = current->next;
		count++;
	}
	file.close();
	cout << "Saved " << count << " completed loans.\n";
}
void saveTransactionHistory(const List1& transactionHistory) {
	ofstream file("data/transaction_history.csv"); // writing to a file (output)
	if (!file.is_open()) {
		cout << "Error: Cannot save transaction_history.csv\n";
		return;
	}
	// Write header
	file << "transactionID,accountNumber,type,amount,date\n";
	// Traverse singly linked list
	Node1* current = transactionHistory.head;
	int count = 0;
	while (current) {
		const transaction& t = current->data;
		file << t.transactionID << ","
			<< t.accountnumber << ","
			<< t.type << ","
			<< t.amount << ","
			<< t.Date << "\n";
		current = current->next;
		count++;
	}
	file.close();
	cout << "Saved " << count << " archived transactions.\n";
}