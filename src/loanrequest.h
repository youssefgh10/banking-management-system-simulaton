#ifndef LOANREQUEST_H
#define LOANREQUEST_H
#include <string>
#include "colors.h"
using namespace std;
struct Loanrequest {
	int requestID;
	int accountNumber;
	string customerName;
	string loanType;
	double requestedAmount;
	string requestDate;
	string status;
	int durationYears;

};
#endif

