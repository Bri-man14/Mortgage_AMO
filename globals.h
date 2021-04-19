#pragma once
const int gmonthsInYear = 12;
const int gpercentDenom = 100;

struct gAmortizeMonth
{
	int year;
	int yearMonth;
	double loanMonth;
	double payment;
	double pureInterest;
	double paidDownPrincipal;
	double principalBalance;
};

