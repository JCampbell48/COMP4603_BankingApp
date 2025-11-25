#include "BankSystem.h"
#include "DepositTransaction.h"
#include "WithdrawTransaction.h"
#include "TransferTransaction.h"
#include <iostream>
#include <iomanip>

// Constructor
BankSystem::BankSystem(AccountRepository& accounts, AccountFactory& factory)
    : accounts(accounts), factory(factory) {
    std::cout << "Bank System initialized." << std::endl;
}

// Helper to validate account exists
bool BankSystem::validateAccountExists(const std::string& accountNo) const {
    if (!accounts.existsAccountNo(accountNo)) {
        std::cerr << "Error: Account " << accountNo << " not found." << std::endl;
        return false;
    }
    return true;
}

// Create new account
Account* BankSystem::createAccount(const std::string& ownerId, AccountType type,
                                   double initialBalance, double overdraft) {
    try {
        // Use factory to create account
        Account* account = factory.create(type, ownerId, initialBalance);

        // For chequing accounts, set custom overdraft if provided
        if (type == AccountType::Chequing && overdraft > 0.0) {
            // We'd need to cast and set overdraft here if different from default
            // For now, factory sets default $500 overdraft for chequing
        }

        // Save to repository
        if (accounts.save(account)) {
            std::cout << "Account created successfully: " << account->getAccountNo()
                      << " (" << AccountFactory::accountTypeToString(type) << ")" << std::endl;
            return account;
        } else {
            delete account;
            std::cerr << "Failed to save account to repository." << std::endl;
            return nullptr;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error creating account: " << e.what() << std::endl;
        return nullptr;
    }
}

// Delete account
bool BankSystem::deleteAccount(const std::string& accountNo) {
    if (!validateAccountExists(accountNo)) {
        return false;
    }

    // Check if account has balance
    double balance = accounts.getBalance(accountNo);
    if (balance != 0.0) {
        std::cerr << "Cannot delete account with non-zero balance: $" << balance << std::endl;
        std::cerr << "Please withdraw all funds first." << std::endl;
        return false;
    }

    return accounts.remove(accountNo);
}

// Deposit money
bool BankSystem::deposit(const std::string& accountNo, double amount) {
    if (!validateAccountExists(accountNo)) {
        return false;
    }

    auto optAccount = accounts.getByAccountNo(accountNo);
    if (!optAccount.has_value()) {
        return false;
    }

    Account* account = optAccount.value();

    // Create and execute deposit transaction
    DepositTransaction transaction(*account, amount, Timestamp::now(),
                                  "Deposit via Bank System");

    if (transaction.execute()) {
        std::cout << "Deposit successful: $" << std::fixed << std::setprecision(2)
                  << amount << " to " << accountNo << std::endl;
        std::cout << "New balance: $" << account->getBalance() << std::endl;
        return true;
    }

    return false;
}

// Withdraw money
bool BankSystem::withdraw(const std::string& accountNo, double amount) {
    if (!validateAccountExists(accountNo)) {
        return false;
    }

    auto optAccount = accounts.getByAccountNo(accountNo);
    if (!optAccount.has_value()) {
        return false;
    }

    Account* account = optAccount.value();

    // Create and execute withdrawal transaction
    WithdrawTransaction transaction(*account, amount, Timestamp::now(),
                                   "Withdrawal via Bank System");

    if (transaction.execute()) {
        std::cout << "Withdrawal successful: $" << std::fixed << std::setprecision(2)
                  << amount << " from " << accountNo << std::endl;
        std::cout << "New balance: $" << account->getBalance() << std::endl;
        return true;
    }

    return false;
}

// Transfer money between accounts
bool BankSystem::transfer(const std::string& fromAccountNo,
                         const std::string& toAccountNo, double amount) {
    if (!validateAccountExists(fromAccountNo) || !validateAccountExists(toAccountNo)) {
        return false;
    }

    auto optFromAccount = accounts.getByAccountNo(fromAccountNo);
    auto optToAccount = accounts.getByAccountNo(toAccountNo);

    if (!optFromAccount.has_value() || !optToAccount.has_value()) {
        return false;
    }

    Account* fromAccount = optFromAccount.value();
    Account* toAccount = optToAccount.value();

    // Create and execute transfer transaction
    TransferTransaction transaction(*fromAccount, *toAccount, amount,
                                   Timestamp::now(), "Transfer via Bank System");

    if (transaction.execute()) {
        std::cout << "Transfer successful: $" << std::fixed << std::setprecision(2)
                  << amount << " from " << fromAccountNo
                  << " to " << toAccountNo << std::endl;
        std::cout << fromAccountNo << " balance: $" << fromAccount->getBalance() << std::endl;
        std::cout << toAccountNo << " balance: $" << toAccount->getBalance() << std::endl;
        return true;
    }

    return false;
}

// Get account balance
double BankSystem::getBalance(const std::string& accountNo) const {
    return accounts.getBalance(accountNo);
}

// Get all accounts for a specific owner
std::vector<std::string> BankSystem::getAccountsByOwner(const std::string& ownerId) const {
    return accounts.findByOwnerId(ownerId);
}

// Get transaction history for an account
std::vector<Transaction*> BankSystem::getTransactionHistory(const std::string& accountNo) const {
    auto optAccount = accounts.getByAccountNo(accountNo);
    if (optAccount.has_value()) {
        const std::vector<Transaction*>& history = optAccount.value()->getHistory();
        return history;
    }
    return std::vector<Transaction*>();
}

// Apply interest to account
bool BankSystem::applyInterest(const std::string& accountNo, const Timestamp& now) {
    if (!validateAccountExists(accountNo)) {
        return false;
    }

    auto optAccount = accounts.getByAccountNo(accountNo);
    if (!optAccount.has_value()) {
        return false;
    }

    Account* account = optAccount.value();
    return account->applyInterest(now);
}

// Check if account exists
bool BankSystem::accountExists(const std::string& accountNo) const {
    return accounts.existsAccountNo(accountNo);
}

// Get account type
std::string BankSystem::getAccountType(const std::string& accountNo) const {
    auto optAccount = accounts.getByAccountNo(accountNo);
    if (optAccount.has_value()) {
        return optAccount.value()->getAccountType();
    }
    return "Unknown";
}

// Get owner ID
std::string BankSystem::getOwnerId(const std::string& accountNo) const {
    auto optAccount = accounts.getByAccountNo(accountNo);
    if (optAccount.has_value()) {
        return optAccount.value()->getOwnerId();
    }
    return "";
}

// Get total account count
size_t BankSystem::getTotalAccountCount() const {
    return accounts.getAccountCount();
}

// Get all accounts
std::vector<Account*> BankSystem::getAllAccounts() const {
    return accounts.getAllAccounts();
}

// Display account summary
void BankSystem::displayAccountSummary(const std::string& accountNo) const {
    auto optAccount = accounts.getByAccountNo(accountNo);
    if (!optAccount.has_value()) {
        std::cerr << "Account not found: " << accountNo << std::endl;
        return;
    }

    Account* account = optAccount.value();

    std::cout << "\n=== Account Summary ===" << std::endl;
    std::cout << "Account Number: " << account->getAccountNo() << std::endl;
    std::cout << "Account Type: " << account->getAccountType() << std::endl;
    std::cout << "Owner ID: " << account->getOwnerId() << std::endl;
    std::cout << "Balance: $" << std::fixed << std::setprecision(2)
              << account->getBalance() << std::endl;

    // Show overdraft if chequing account
    double overdraft = accounts.getOverdraftLimit(accountNo);
    if (overdraft > 0) {
        std::cout << "Overdraft Limit: $" << overdraft << std::endl;
        std::cout << "Available Funds: $" << (account->getBalance() + overdraft) << std::endl;
    }

    std::cout << "===================\n" << std::endl;
}

// Display all accounts
void BankSystem::displayAllAccounts() const {
    std::vector<Account*> allAccounts = accounts.getAllAccounts();

    if (allAccounts.empty()) {
        std::cout << "No accounts in the system." << std::endl;
        return;
    }

    std::cout << "\n=== All Accounts ===" << std::endl;
    std::cout << std::left << std::setw(15) << "Account No"
              << std::setw(12) << "Type"
              << std::setw(15) << "Owner"
              << std::right << std::setw(12) << "Balance" << std::endl;
    std::cout << std::string(54, '-') << std::endl;

    for (Account* account : allAccounts) {
        std::cout << std::left << std::setw(15) << account->getAccountNo()
                  << std::setw(12) << account->getAccountType()
                  << std::setw(15) << account->getOwnerId()
                  << std::right << std::setw(12) << std::fixed << std::setprecision(2)
                  << "$" << account->getBalance() << std::endl;
    }

    std::cout << std::string(54, '-') << std::endl;
    std::cout << "Total accounts: " << allAccounts.size() << "\n" << std::endl;
}