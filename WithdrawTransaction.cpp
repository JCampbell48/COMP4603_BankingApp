#include "WithdrawTransaction.h"

#include <iostream>
#include <sstream>

// Constructor
WithdrawTransaction::WithdrawTransaction(Account& account, double amount,
    const Timestamp& timestamp, const std::string& description) :
        Transaction("WTH-" + account.getAccountNo() + "-" + timestamp.toString(),
            timestamp, description), account(account), amount(amount), executed(false) {
}

// Execute the withdrawal
bool WithdrawTransaction::execute() {
    if (executed) {
        std::cerr << "Transaction already executed!" << std::endl;
        return false;
    }

    if (account.withdraw(amount)) {
        executed = true;
        std::cout << "Withdrawal executed: $" << amount
                  << " from account " << account.getAccountNo() << std::endl;
        return true;
    }

    return false;
}

// Undo the withdrawal (deposit the amount back)
bool WithdrawTransaction::undo() {
    if (!executed) {
        std::cerr << "Cannot undo: Transaction not executed!" << std::endl;
        return false;
    }

    if (account.deposit(amount)) {
        executed = false;
        std::cout << "Withdrawal undone: $" << amount
                  << " deposited back to account " << account.getAccountNo() << std::endl;
        return true;
    }

    return false;
}

// Create record of transactions
std::string WithdrawTransaction::record() const {
    std::stringstream ss;
    ss << Transaction::record() << "\n";
    ss << "Type: Withdrawal\n";
    ss << "Account: " << account.getAccountNo() << "\n";
    ss << "Amount: $" << amount << "\n";
    ss << "Status: " << (executed ? "Executed" : "Not Executed");
    return ss.str();
}

// Getters
double WithdrawTransaction::getAmount() const {
    return amount;
}

std::string WithdrawTransaction::getAccountNo() const {
    return account.getAccountNo();
}