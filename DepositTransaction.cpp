#include "DepositTransaction.h"
#include <iostream>
#include <sstream>

// Constructor
DepositTransaction::DepositTransaction(Account& account, double amount,
    const Timestamp& timestamp, const std::string& description)
    : Transaction("DEP-" + account.getAccountNo() + "-" + timestamp.toString(),
                  timestamp, description), account(account), amount(amount),
                    executed(false) {
}

// Execute the deposit
bool DepositTransaction::execute() {
    if (executed) {
        std::cerr << "Transaction already executed!" << std::endl;
        return false;
    }

    if (account.deposit(amount)) {
        executed = true;
        std::cout << "Deposit executed: $" << amount
                  << " to account " << account.getAccountNo() << std::endl;
        return true;
    }

    return false;
}

// Undo the deposit (withdraw the amount)
bool DepositTransaction::undo() {
    if (!executed) {
        std::cerr << "Cannot undo: Transaction not executed!" << std::endl;
        return false;
    }

    if (account.withdraw(amount)) {
        executed = false;
        std::cout << "Deposit undone: $" << amount
                  << " withdrawn from account " << account.getAccountNo() << std::endl;
        return true;
    }

    std::cerr << "Failed to undo deposit - insufficient funds" << std::endl;
    return false;
}

// Create detailed record
std::string DepositTransaction::record() const {
    std::stringstream ss;
    ss << Transaction::record() << "\n";
    ss << "Type: Deposit\n";
    ss << "Account: " << account.getAccountNo() << "\n";
    ss << "Amount: $" << amount << "\n";
    ss << "Status: " << (executed ? "Executed" : "Not Executed");
    return ss.str();
}

// Getters
double DepositTransaction::getAmount() const {
    return amount;
}

std::string DepositTransaction::getAccountNo() const {
    return account.getAccountNo();
}