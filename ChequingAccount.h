#pragma once
#include "Account.h"

class ChequingAccount : public Account {
private:
    doubtl overdraftLimit;

public:
    ChequingAccount(std::string accountNo, string ownerId, double balance, double overdraftLimit);
    double getOverdraftLimit();
    setOverdraftLimit(double limit);
    bool deposit(double amount);
    bool withdraw(double amount);

};
