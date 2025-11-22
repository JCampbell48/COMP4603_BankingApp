#pragma once
#include "Account.h"

class ChequingAccount : public Account {
private:
    double overdraftLimit;

public:
    // constructor
    ChequingAccount(const std::string& accountNo, const std::string& ownerId, double balance, double overdraftLimit);

    //overdraft logic
    double getOverdraftLimit() const;
    void setOverdraftLimit(double limit);

    //override withdraw to allow overdraft
    bool withdraw(double amount) override;


    bool applyInterest(const Timestamp& now) override = 0;
    std::string getAccountType() const override;

};
