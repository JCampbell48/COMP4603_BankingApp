#include "Account.h"
#include <stdexcept>
#include <iostream>
#include "Transaction.h"

// Default constructor
Account::Account()
    : accountNo(""),
      ownerId(""),
      balance(0.0),
      lastInterestApplied(Timestamp::now()) {
}

// Parameterized constructor
Account::Account(const std::string& accountNo, const std::string& ownerId, double balance)
    : accountNo(accountNo),
      ownerId(ownerId),
      balance(balance),
      lastInterestApplied(Timestamp::now()) {

    if (balance < 0) {
        throw std::invalid_argument("Initial balance cannot be negative");
    }
}

// Getters
std::string Account::getAccountNo() const {
    return accountNo;
}

std::string Account::getOwnerId() const {
    return ownerId;
}

double Account::getBalance() const {
    return balance;
}

// Set balance - use with caution, mainly for internal operations
void Account::setBalance(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Balance cannot be negative");
    }
    balance = amount;
}

// Deposit money into account
bool Account::deposit(double amount) {
    if (amount <= 0) {
        std::cerr << "Deposit amount must be positive" << std::endl;
        return false;
    }

    balance += amount;
    // TODO: Create and record deposit transaction
    return true;
}

// Withdraw money from account
bool Account::withdraw(double amount) {
    if (amount <= 0) {
        std::cerr << "Withdrawal amount must be positive" << std::endl;
        return false;
    }

    if (amount > balance) {
        std::cerr << "Insufficient funds for Withdrawal" << std::endl;
        return false;
    }

    balance -= amount;
    // TODO: Create and record withdrawal transaction
    return true;
}

// Transfer money to another account
bool Account::transferTo(Account& target, double amount) {
    if (amount <= 0) {
        std::cerr << "Transfer amount must be positive" << std::endl;
        return false;
    }

    if (amount > balance) {
        std::cerr << "Insufficient funds for transfer" << std::endl;
        return false;
    }

    // Perform the transfer
    balance -= amount;
    target.balance += amount;

    // TODO: Create and record transfer transactions for both accounts
    return true;
}

// Close account
bool Account::close() {
    if (balance > 0) {
        std::cerr << "Cannot close account with positive balance. Please withdraw all funds first." << std::endl;
        return false;
    }

    // TODO: Mark account as closed (might need an 'isClosed' flag)
    return true;
}

// Destructor - clean up transaction history
Account::~Account() {
    for (Transaction* t : history) {
         delete t;
    }
    history.clear();
}

// Protected method to record transactions
void Account::record(Transaction* transaction) {
    history.push_back(transaction);
}

// Get transaction history
const std::vector<Transaction*>& Account::getHistory() const {
    return history;
}