#include <iostream>
#include <cmath>
#include <iomanip>
#include "product.h"
#include "quotient.h"
#include "globals.h"

using namespace std;

enum Amortizegram
{
	Loan_principal = 1,
	Int_rate = 2,
	Maturity = 3  
};
enum AmortEnum 
{
	yr_out = 2,
	mn_out = 2,
	cum_mn_out = 2,
	pmt_out = 12,
	int_out = 12,
	princ_out = 12,
	bal_out = 16
};

string AmortHeader [] = 
{
	"YR",
	"MN",
	"CuMn",
	"PMT" ,
	"Interest" ,
	"Principal",
	"Balance"
};

void printAmortHeader() 
{
	cout <<
		endl <<
		setw(yr_out) << AmortHeader[0] << " " <<
		setw(mn_out) << AmortHeader[1] << " " <<
		setw(cum_mn_out) << AmortHeader[2] << " " <<
		setw(pmt_out) << AmortHeader[3] << " " <<
		setw(int_out) << AmortHeader[4] << " " <<
		setw(princ_out) << AmortHeader[5] << " " <<
		setw(bal_out) << AmortHeader[6] << " " <<
		endl <<
		endl;
}

int main(int argc, char* argv[])
{	
	double principal = 0.0;
	double irate = 0.0;
	double term = 0;

	if (argc == 1)
	{
		cout << "Enter principal amount: ";
		cin >> principal;

		cout << "Enter the interest rate: ";
		cin >> irate;

		cout << "Enter the maturity of the mortgage: ";
		cin >> term;
	}
	else
	{
		principal = atof(argv[Loan_principal]); 
		irate = atof(argv[Int_rate]);
		term = atoi(argv[Maturity]);
	}

	cout << "Loan Principal: " << principal << endl;
	cout << "Interest Rate: " << irate << "%" << endl;
	cout << "Time Period: " << term <<" year(s)" << endl;

	double interest = quotient(irate, gpercentDenom);

	double monthlyRate = quotient(irate, gmonthsInYear);
	double monthsOfLoan = product(term, gmonthsInYear);

	double payment = 0.0;

	payment = principal *
		(monthlyRate /
		(1 - (pow((double)1 + monthlyRate,
			(double)-monthsOfLoan))));

	cout << "Payment: " << setiosflags(ios::fixed) <<
		setprecision(2) << payment << endl;

	double currIntPmt = 0.0;
	double currPriPmt = 0.0;
	double currBalance = 0.0;

	currBalance = principal;

	long currLoanMonth = 1;

	int year = 1;
	int switchyear = 0;
	int yr_month = 1;

	while (currLoanMonth <= monthsOfLoan) {
		
		if (switchyear != year) {
			switchyear = year;
			printAmortHeader();
		}

		gAmortizeMonth amortMonth;

		currIntPmt = currBalance * monthlyRate;
		currPriPmt = payment - currIntPmt;
		currBalance = abs(currBalance - currPriPmt);
		 
		amortMonth.year = year;
		amortMonth.yearMonth = yr_month;
		amortMonth.loanMonth = currLoanMonth;
		amortMonth.payment = payment;
		amortMonth.pureInterest = currIntPmt;
		amortMonth.paidDownPrincipal = currPriPmt;
		amortMonth.principalBalance = currBalance;

		cout <<
			setw(yr_out) << amortMonth.year << " " <<
			setw(mn_out) << amortMonth.yearMonth << " " <<
			setw(cum_mn_out) << amortMonth.loanMonth << " " <<
			setw(pmt_out) << amortMonth.payment << " " <<
			setw(int_out) << amortMonth.pureInterest << " " <<
			setw(princ_out) << amortMonth.paidDownPrincipal << " " <<
			setw(bal_out) << amortMonth.principalBalance << " " <<
			endl;

		yr_month++;
		if (yr_month > gmonthsInYear)
		{
			yr_month = 1;
			year++;
		}

		currLoanMonth++;
	}
	cout << 
		endl<<
		"Loan payments complete." << 
		endl <<
		endl;

	return 0;
}