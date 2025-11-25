#pragma once

#include <string>
#include <vector>
#include "AccountRepository.h"
#include "AccountFactory.h"
#include "AccountType.h"
#include "Account.h"
#include "Transaction.h"
#include "Timestamp.h"

/**
 * BankSystem - Facade Pattern
 * Provides a simplified, high-level interface to the banking system
 * Coordinates operations between AccountFactory, AccountRepository, and Transactions
 */
class BankSystem {
private:
    AccountRepository& accounts;
    AccountFactory& factory;

    // Helper method to validate account existence
    bool validateAccountExists(const std::string& accountNo) const;

public:
    // Constructor - takes references to repository and factory
    BankSystem(AccountRepository& accounts, AccountFactory& factory);

    // Account Management
    Account* createAccount(const std::string& ownerId, AccountType type,
                          double initialBalance = 0.0, double overdraft = 0.0);
    bool deleteAccount(const std::string& accountNo);

    // Banking Operations
    bool deposit(const std::string& accountNo, double amount);
    bool withdraw(const std::string& accountNo, double amount);
    bool transfer(const std::string& fromAccountNo, const std::string& toAccountNo,
                 double amount);

    // Account Queries
    double getBalance(const std::string& accountNo) const;
    std::vector<std::string> getAccountsByOwner(const std::string& ownerId) const;
    std::vector<Transaction*> getTransactionHistory(const std::string& accountNo) const;

    // Interest Operations
    bool applyInterest(const std::string& accountNo, const Timestamp& now);

    // Account Information
    bool accountExists(const std::string& accountNo) const;
    std::string getAccountType(const std::string& accountNo) const;
    std::string getOwnerId(const std::string& accountNo) const;

    // System-wide Operations
    size_t getTotalAccountCount() const;
    std::vector<Account*> getAllAccounts() const;

    // Display/Reporting
    void displayAccountSummary(const std::string& accountNo) const;
    void displayAllAccounts() const;
};
