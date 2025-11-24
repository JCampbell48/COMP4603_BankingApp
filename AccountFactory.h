#pragma once

#include <string>
#include <memory>
#include "AccountType.h"
#include "Account.h"

/**
 * AccountFactory - Factory Pattern for creating accounts
 * Centralizes account creation logic and ensures consistent account number generation
 */
class AccountFactory {
private:
    static int accountCounter;  // Static counter for generating unique account numbers

    // Generate unique account number based on type
    static std::string generateAccountNumber(AccountType type);

public:
    // Constructor
    AccountFactory();

    // Create account of specified type
    // Returns pointer to newly created account (caller takes ownership)
    Account* create(AccountType type, const std::string& ownerId);

    // Overloaded create with initial balance
    Account* create(AccountType type, const std::string& ownerId, double initialBalance);

    // Helper method to convert AccountType to string
    static std::string accountTypeToString(AccountType type);
};
