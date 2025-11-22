#pragma once

#include <string>
#include <vector>
#include "Timestamp.h"

// Forward declaration - we'll implement Transaction class next
class Transaction;

/**
 * Abstract base class for all account types
 * Provides core banking account functionality
 */
class Account {
protected:
    std::string accountNo;
    std::string ownerId;
    double balance;
    std::vector<Transaction*> history;
    Timestamp lastInterestApplied;

    // Protected method to record transactions
    void record(Transaction* transaction);

public:
    // Constructors
    Account();
    Account(const std::string& accountNo, const std::string& ownerId, double balance);

    // Virtual destructor for proper cleanup
    virtual ~Account();

    // Getters
    std::string getAccountNo() const;
    std::string getOwnerId() const;
    double getBalance() const;

    // Balance manipulation
    void setBalance(double amount);

    // Core banking operations
    virtual bool deposit(double amount);
    virtual bool withdraw(double amount);
    virtual bool transferTo(Account& target, double amount);

    // Interest application - simplified for now, can add InterestPolicy later
    virtual bool applyInterest(const Timestamp& now) = 0;

    // Account management
    virtual bool close();

    // Transaction history
    const std::vector<Transaction*>& getHistory() const;

    // Pure virtual method to get account type (for polymorphism)
    virtual std::string getAccountType() const = 0;
};
