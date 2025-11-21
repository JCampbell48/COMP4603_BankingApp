#include "SavingsAccount.h"
#include <iostream>

SavingsAccount::SavingsAccount(const std::string& accountNo, const std::string& ownerId,
                               double balance, double interestRate)
    : Account(accountNo, ownerId, balance), interestRate(interestRate) {

    if (interestRate < 0) {
        throw std::invalid_argument("Interest rate cannot be negative");
    }
}

bool SavingsAccount::applyInterest(std::chrono::system_clock::time_point now) {
    // Simple interest calculation
    // TODO: Can integrate InterestPolicy pattern later if needed

    // Calculate time difference since last interest application
    auto duration = std::chrono::duration_cast<std::chrono::hours>(now - lastInterestApplied);
    double days = duration.count() / 24.0;

    // Apply simple daily interest
    double interest = balance * (interestRate / 365.0) * days;

    if (interest > 0) {
        balance += interest;
        lastInterestApplied = now;

        std::cout << "Applied interest: $" << interest
                  << " (New balance: $" << balance << ")" << std::endl;

        // TODO: Create and record interest transaction
        return true;
    }

    return false;
}

std::string SavingsAccount::getAccountType() const {
    return "Savings";
}

double SavingsAccount::getInterestRate() const {
    return interestRate;
}

void SavingsAccount::setInterestRate(double rate) {
    if (rate < 0) {
        throw std::invalid_argument("Interest rate cannot be negative");
    }
    interestRate = rate;
}