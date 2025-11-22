#pragma once
#include "Account.h"
#include "Account.h"

/**
 * Concrete implementation of Account for savings accounts
 * This is a simple example to test the Account base class
 */
class SavingsAccount : public Account {
private:
    double interestRate; // Annual interest rate (e.g., 0.02 for 2%)

public:
    SavingsAccount(const std::string& accountNo, const std::string& ownerId,
                   double balance, double interestRate = 0.02);

    // Implementation of pure virtual methods
    bool applyInterest(const Timestamp& now) override;

    std::string getAccountType() const override;

    // Savings-specific methods
    double getInterestRate() const;
    void setInterestRate(double rate);
};
