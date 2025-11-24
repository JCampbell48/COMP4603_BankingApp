#include "AccountRepository.h"
#include "ChequingAccount.h"
#include <iostream>

// Constructor
AccountRepository::AccountRepository() {
    // Nothing special needed
}

// Destructor - cleanup all accounts
AccountRepository::~AccountRepository() {
    clear();
}

// Get account by account number
std::optional<Account*> AccountRepository::getByAccountNo(const std::string& accountNo) {
    auto it = accounts.find(accountNo);
    if (it != accounts.end()) {
        return it->second;
    }
    return std::nullopt;  // Account not found
}

// Save (add or update) an account
bool AccountRepository::save(Account* account) {
    if (account == nullptr) {
        std::cerr << "Cannot save null account" << std::endl;
        return false;
    }

    std::string accountNo = account->getAccountNo();

    // Check if account already exists
    if (accounts.find(accountNo) != accounts.end()) {
        // Update existing account
        std::cout << "Updated existing account: " << accountNo << std::endl;
    } else {
        // Add new account
        std::cout << "Added new account: " << accountNo << std::endl;
    }

    accounts[accountNo] = account;
    return true;
}

// Remove account by account number
bool AccountRepository::remove(const std::string& accountNo) {
    auto it = accounts.find(accountNo);
    if (it != accounts.end()) {
        // Delete the account object
        delete it->second;
        // Remove from map
        accounts.erase(it);
        std::cout << "Removed account: " << accountNo << std::endl;
        return true;
    }

    std::cerr << "Account not found: " << accountNo << std::endl;
    return false;
}

// Find all account numbers owned by a specific owner
std::vector<std::string> AccountRepository::findByOwnerId(const std::string& ownerId) {
    std::vector<std::string> result;

    for (const auto& pair : accounts) {
        if (pair.second->getOwnerId() == ownerId) {
            result.push_back(pair.first);
        }
    }

    return result;
}

// Check if account number exists
bool AccountRepository::existsAccountNo(const std::string& accountNo) const {
    return accounts.find(accountNo) != accounts.end();
}

// Get balance of specific account
double AccountRepository::getBalance(const std::string& accountNo) const {
    auto it = accounts.find(accountNo);
    if (it != accounts.end()) {
        return it->second->getBalance();
    }

    std::cerr << "Account not found: " << accountNo << std::endl;
    return 0.0;
}

// Get minimum balance (for savings accounts)
double AccountRepository::getMinBalance(const std::string& accountNo) const {
    auto it = accounts.find(accountNo);
    if (it != accounts.end()) {
        // For now, return 0.0 as we haven't implemented minimum balance tracking
        // This would be account-type specific
        return 0.0;
    }

    std::cerr << "Account not found: " << accountNo << std::endl;
    return 0.0;
}

// Get overdraft limit (for chequing accounts)
double AccountRepository::getOverdraftLimit(const std::string& accountNo) const {
    auto it = accounts.find(accountNo);
    if (it != accounts.end()) {
        // Try to cast to ChequingAccount
        ChequingAccount* chequing = dynamic_cast<ChequingAccount*>(it->second);
        if (chequing != nullptr) {
            return chequing->getOverdraftLimit();
        }
        // Not a chequing account - no overdraft
        return 0.0;
    }

    std::cerr << "Account not found: " << accountNo << std::endl;
    return 0.0;
}

// Get all accounts
std::vector<Account*> AccountRepository::getAllAccounts() const {
    std::vector<Account*> result;
    for (const auto& pair : accounts) {
        result.push_back(pair.second);
    }
    return result;
}

// Get count of accounts
size_t AccountRepository::getAccountCount() const {
    return accounts.size();
}

// Clear all accounts
void AccountRepository::clear() {
    // Delete all account objects
    for (auto& pair : accounts) {
        delete pair.second;
    }
    // Clear the map
    accounts.clear();
}