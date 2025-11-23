#pragma once

#include "Transaction.h"
#include "Account.h"

/**
 * WithdrawTransaction - Handles withdrawal operations
 * Can be executed and undone
 */
class WithdrawTransaction : public Transaction {
private:
    Account& account;
    double amount;
    bool executed;  // Track if transaction has been executed

public:
    // Constructor
    WithdrawTransaction(Account& account, double amount, const Timestamp& timestamp,
                       const std::string& description);

    // Implementation of pure virtual methods
    bool execute() override;
    bool undo() override;

    // Override record to include withdrawal-specific details
    std::string record() const override;

    // Getters
    double getAmount() const;
    std::string getAccountNo() const;
};