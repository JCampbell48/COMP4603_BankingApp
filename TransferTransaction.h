#pragma once

#include "Transaction.h"
#include "Account.h"

/**
 * TransferTransaction - Handles transfer operations between two accounts
 * Can be executed and undone
 */
class TransferTransaction : public Transaction {
private:
    Account& fromAccount;
    Account& toAccount;
    double amount;
    bool executed;  // Track if transaction has been executed

public:
    // Constructor
    TransferTransaction(Account& fromAccount, Account& toAccount, double amount,
                       const Timestamp& timestamp, const std::string& description);
    
    // Implementation of pure virtual methods
    bool execute() override;
    bool undo() override;
    
    // Override record to include transfer-specific details
    std::string record() const override;
    
    // Getters
    double getAmount() const;
    std::string getFromAccountNo() const;
    std::string getToAccountNo() const;
};
