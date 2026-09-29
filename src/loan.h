#ifndef LOAN_H
#define LOAN_H
#include <string>
#include "colors.h"
using namespace std;
struct loan {
	int loanID;
	int accountnumber;  // Original account, including after archival
	string loantype;
	double principalamount;
	double interestrate;
	double amountpaid;
	double remainingbalance;
	string startdate;
	string enddate;
	string loanstatus;
};
#endif
