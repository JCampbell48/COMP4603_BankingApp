#pragma once
#include "Account.h"

/**
 * Concrete implementation of Account for savings accounts
 * Using this to test the Account base class
 */
class SavingsAccount : public Account {
private:
    double interestRate; // Annual interest rate (e.g., 0.02 for 2%)

public:
    SavingsAccount(const std::string& accountNo, const std::string& ownerId,
                   double balance, double interestRate = 0.02);

    // Implementation of pure virtual methods
    bool applyInterest(std::chrono::system_clock::time_point now) override;

    std::string getAccountType() const override;

    // Savings-specific methods
    double getInterestRate() const;
    void setInterestRate(double rate);
};
