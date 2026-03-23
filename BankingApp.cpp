// BankingApp.cpp
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "BankingApp.h"

// Column widths for report formatting
static const int COL_YEAR     = 6;
static const int COL_BALANCE  = 20;
static const int COL_INTEREST = 24;
static const int REPORT_WIDTH = COL_YEAR + COL_BALANCE + COL_INTEREST; // ~50 chars

// Constructor
// Validates inputs so the object is always in a usable state

BankingApp::BankingApp(double initialInvestment, double monthlyDeposit,
                       double annualInterest, int numYears)
    : m_initialInvestment(initialInvestment),
      m_monthlyDeposit(monthlyDeposit),
      m_annualInterest(annualInterest),
      m_numYears(numYears)
{
    if (initialInvestment < 0.0)
        throw std::invalid_argument("Initial investment cannot be negative.");
    if (monthlyDeposit < 0.0)
        throw std::invalid_argument("Monthly deposit cannot be negative.");
    if (annualInterest < 0.0 || annualInterest > 100.0)
        throw std::invalid_argument("Annual interest must be between 0 and 100.");
    if (numYears <= 0)
        throw std::invalid_argument("Number of years must be greater than zero.");
}

// displayInputSummary
// Prints the stored parameters, no I/O side effects

void BankingApp::displayInputSummary() const {
    std::cout << "\n" << std::string(REPORT_WIDTH, '-') << '\n';
    std::cout << "  Investment Parameters\n";
    std::cout << std::string(REPORT_WIDTH, '-') << '\n';
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Initial Investment:  $" << std::setw(10) << m_initialInvestment << '\n';
    std::cout << "  Monthly Deposit:     $" << std::setw(10) << m_monthlyDeposit    << '\n';
    std::cout << "  Annual Interest:      " << std::setw(9)  << m_annualInterest << "%\n";
    std::cout << "  Number of Years:      " << std::setw(9)  << m_numYears        << '\n';
    std::cout << std::string(REPORT_WIDTH, '-') << '\n';
}

// printReportHeader
// Shared column header for both report methods

void BankingApp::printReportHeader() const {
    std::cout << std::left
              << std::setw(COL_YEAR)     << "Year"
              << std::setw(COL_BALANCE)  << "Year End Balance"
              << std::setw(COL_INTEREST) << "Year End Earned Interest"
              << '\n';
    std::cout << std::string(REPORT_WIDTH, '-') << '\n';
}

// displayReportWithoutMonthlyDeposits
// Uses simple annual compounding: balance *= (1 + rate)

void BankingApp::displayReportWithoutMonthlyDeposits() const {
    std::cout << "\n  Balance and Interest Without Monthly Deposits\n";
    std::cout << std::string(REPORT_WIDTH, '=') << '\n';
    printReportHeader();

    double balance = m_initialInvestment;
    const double annualRate = m_annualInterest / 100.0;

    std::cout << std::fixed << std::setprecision(2);

    for (int year = 1; year <= m_numYears; ++year) {
        double interest = balance * annualRate;
        balance += interest;

        std::cout << std::left  << std::setw(COL_YEAR) << year
                  << std::right << "$" << std::setw(COL_BALANCE  - 1) << balance
                  << "  $"      << std::setw(COL_INTEREST - 3)        << interest
                  << '\n';
    }
}

// displayReportWithMonthlyDeposits
//   Compounds monthly: deposit is added each month before interest accrues

void BankingApp::displayReportWithMonthlyDeposits() const {
    std::cout << "\n  Balance and Interest With Monthly Deposits\n";
    std::cout << std::string(REPORT_WIDTH, '=') << '\n';
    printReportHeader();

    double balance = m_initialInvestment;
    const double monthlyRate = (m_annualInterest / 100.0) / 12.0;

    std::cout << std::fixed << std::setprecision(2);

    for (int year = 1; year <= m_numYears; ++year) {
        double yearlyInterest = 0.0;

        for (int month = 1; month <= 12; ++month) {
            balance += m_monthlyDeposit;
            double monthlyInterest = balance * monthlyRate;
            yearlyInterest += monthlyInterest;
            balance += monthlyInterest;
        }

        std::cout << std::left  << std::setw(COL_YEAR) << year
                  << std::right << "$" << std::setw(COL_BALANCE  - 1) << balance
                  << "  $"      << std::setw(COL_INTEREST - 3)        << yearlyInterest
                  << '\n';
    }
}
