#include "InvestData.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
using namespace std;

//Creates the investment class to hold data
InvestData::InvestData(double t_investAmt, double t_annualInterest, int t_numYears, double t_monthlyDeposit) {
    m_investAmt = t_investAmt;
    m_annualInterest = t_annualInterest;
    m_numYears = t_numYears;
    m_monthlyDeposit = t_monthlyDeposit;
}

//Gathers the investment data
void InvestData::gatherData() {
    cout << fixed << setprecision(2);
    cout << "Enter your investment amount: " << endl;
    cin >> m_investAmt;
    if (!cin || m_investAmt < 0) {
        throw runtime_error("Invalid investment input. Must be a number at or above 0");
    }
    cout << "Enter your monthly deposit: " << endl;
    cin >> m_monthlyDeposit;
    if (!cin || m_monthlyDeposit < 0) {
        throw runtime_error("Invalid monthly deposit input. Must be a number at or above 0");
    }
    cout << "Enter your annual interest rate: " << endl;
    cin >> m_annualInterest;
    if (!cin || m_annualInterest < 0) {
        throw runtime_error("Invalid interest input. Must be a number at or above 0");
    }
    cout << "Enter how many years you will grow your investment: " << endl;
    cin >> m_numYears;
    if (!cin || m_numYears < 0) {
        throw runtime_error("Invalid year input. Must be a number at or above 0");
    }
}

//Prints the user interface
void InvestData::printScreen() {
    cout << string(36, '*') << endl;
    cout << string(12, '*') << " Data Input " << string(12, '*') << endl;
    cout << string(36, '*') << endl;
    cout << "Initial investment amount: $" << m_investAmt << endl;
    cout << "Monthly Deposit: $" << m_monthlyDeposit << endl;
    cout << "Annual Interest: " << m_annualInterest << '%' << endl;
    cout << "Number Of Years: " << m_numYears << endl;
}

//Calculates and prints the balance and interest earned chart by year
void InvestData::printData() {
    double balance = m_investAmt;
    double monthlyInterest = (m_annualInterest / 100) / 12;

    cout << endl;
    cout << string(4, ' ') << "Balance And Interest Earned After Deposits" << string(4, ' ') << endl;
    cout << string(50, '=') << endl;
    cout << " Year  " << "Year End Balance  " << "Year End Earned Interest " << endl;
    cout << string(50, '-') << endl;

    for (int i = 1; i <= m_numYears; ++i) {
        double interestEarned = 0.0;
        for (int j = 1; j <= 12; ++j) {
            balance += m_monthlyDeposit;
            balance += (balance * monthlyInterest);
            interestEarned += (balance * monthlyInterest);
        }
        cout << "  " << i << string(11 - to_string(i).size(), ' ') << balance << string(22 - to_string(balance).size(), ' ') << interestEarned << endl;
    }
}

void InvestData::resetData() {
    m_investAmt = 0.00;
    m_annualInterest = 0.00;
    m_numYears = 0;
    m_monthlyDeposit = 0.00;
}