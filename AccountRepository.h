#pragma once

#include <string>
#include <vector>
#include <map>
#include <optional>
#include "Account.h"

/**
 * AccountRepository - Repository Pattern for account storage and retrieval
 * Manages the collection of accounts and provides query methods
 */
class AccountRepository {
private:
    // Storage: map of accountNo -> Account*
    std::map<std::string, Account*> accounts;

public:
    // Constructor
    AccountRepository();

    // Destructor - cleanup all accounts
    ~AccountRepository();

    // Get account by account number
    // Returns std::optional containing Account* if found, empty optional if not found
    std::optional<Account*> getByAccountNo(const std::string& accountNo);

    // Save (add or update) an account
    // Returns true if successful
    bool save(Account* account);

    // Remove account by account number
    // Returns true if account was found and removed
    bool remove(const std::string& accountNo);

    // Find all account numbers owned by a specific owner
    std::vector<std::string> findByOwnerId(const std::string& ownerId);

    // Check if account number exists
    bool existsAccountNo(const std::string& accountNo) const;

    // Get balance of specific account
    // Returns 0.0 if account not found
    double getBalance(const std::string& accountNo) const;

    // Get minimum balance (for savings accounts, typically)
    // Returns 0.0 if account not found or not applicable
    double getMinBalance(const std::string& accountNo) const;

    // Get overdraft limit (for chequing accounts)
    // Returns 0.0 if account not found or not applicable
    double getOverdraftLimit(const std::string& accountNo) const;

    // Get all accounts (useful for reporting)
    std::vector<Account*> getAllAccounts() const;

    // Get count of accounts
    size_t getAccountCount() const;

    // Clear all accounts
    void clear();
};
