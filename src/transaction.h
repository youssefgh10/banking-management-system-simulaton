#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include "colors.h"
using namespace std;
struct transaction {
	int transactionID;
	int accountnumber;
	string type;
	double amount;
	string Date;
};
#endif

