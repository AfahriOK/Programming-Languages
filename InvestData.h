#ifndef INVESTDATA_H
#define INVESTDATA_H

class InvestData {
public:
	InvestData(double t_investAmt = 0.00, double t_annualInterest = 0.00, int t_numYears = 0, double t_monthlyDeposit = 0.00);
	void printScreen();
	void gatherData();
	void resetData();
	void printData();
private:
	double m_investAmt;
	double m_monthlyDeposit;
	double m_annualInterest;
	int m_numYears;
};

#endif
