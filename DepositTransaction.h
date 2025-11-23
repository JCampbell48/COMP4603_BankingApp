#pragma once
#include "Transaction.h"
#include "Account.h"

/**
 * DepositTransaction - Handles deposit operations
 * Can be executed and undone
 */
class DepositTransaction : public Transaction {
private:
    Account& account;
    double amount;
    bool executed;  // Track if transaction has been executed

public:
    // Constructor
    DepositTransaction(Account& account, double amount, const Timestamp& timestamp,
                      const std::string& description);

    // Implementation of pure virtual methods
    bool execute() override;
    bool undo() override;

    // Override recordAll to include deposit-specific details
    std::string record() const override;

    // Getters
    double getAmount() const;
    std::string getAccountNo() const;
};