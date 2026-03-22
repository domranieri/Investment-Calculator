// main.cpp
#include <iostream>
#include <limits>
#include <stdexcept>
#include "BankingApp.h"

// getPositiveDouble
//   Prompts the user for a non negative double, loops until valid input

static double getPositiveDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= 0.0) {
            return value;
        }
        std::cout << "  Invalid input. Please enter a non negative number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// getPositiveInt
//   Prompts the user for a positive integer, loops until valid input

static int getPositiveInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value > 0) {
            return value;
        }
        std::cout << "  Invalid input. Please enter a whole number greater than zero.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// getInterestRate
//   Like getPositiveDouble but also enforces the 0–100 range.

static double getInterestRate(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= 0.0 && value <= 100.0) {
            return value;
        }
        std::cout << "  Invalid input. Please enter a rate between 0 and 100.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// main

int main() {
    std::cout << "================================================\n";
    std::cout << "     Banking Investment Calculator\n";
    std::cout << "================================================\n";

    char userChoice = 'Y';

    while (userChoice == 'Y' || userChoice == 'y') {

        // Collect inputs
        double initialInvestment = getPositiveDouble("\nInitial Investment Amount ($): ");
        double monthlyDeposit    = getPositiveDouble("Monthly Deposit ($):           ");
        double annualInterest    = getInterestRate  ("Annual Interest Rate (%):      ");
        int    numYears          = getPositiveInt   ("Number of Years:               ");

        // Pause before showing results
        std::cout << "\nPress Enter to see your results...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

        // Build and display
        try {
            BankingApp investment(initialInvestment, monthlyDeposit,
                                  annualInterest, numYears);
            investment.displayInputSummary();
            investment.displayReportWithoutMonthlyDeposits();
            investment.displayReportWithMonthlyDeposits();
        }
        catch (const std::invalid_argument& e) {
            // Error handling
            std::cerr << "\nError creating investment: " << e.what() << '\n';
        }

        // Ask to repeat
        std::cout << "\nWould you like to run another scenario? (Y/N): ";
        std::cin >> userChoice;
    }

    std::cout << "\nThank you for using the Banking Investment Calculator!\n";
    return 0;
}
