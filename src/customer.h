#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include "doublylinkedlistmethods.h"
#include "stackarraytrmeth.h"
using namespace std;
struct customer {
	int accountnumber;
	string accounttype;
	string IBAN;
	int branchcode;
	string accountholdername;
	string openingdate;
	string Status;
	double balance;
	List loans;
	stack dailytransaction;
};
#endif

