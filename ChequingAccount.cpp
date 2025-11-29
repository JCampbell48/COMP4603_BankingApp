#include "ChequingAccount.h"
#include <iostream>

// Constructor
ChequingAccount::ChequingAccount(const std::string& accountNo, const std::string& ownerId,
                                 double balance, double overdraftLimit)
    : Account(accountNo, ownerId, balance), overdraftLimit(overdraftLimit) {

    if (overdraftLimit < 0) {
        throw std::invalid_argument("Overdraft limit cannot be negative");
    }
}

// Get overdraft limit
double ChequingAccount::getOverdraftLimit() const {
    return overdraftLimit;
}

// Set overdraft limit
void ChequingAccount::setOverdraftLimit(double limit) {
    if (limit < 0) {
        throw std::invalid_argument("Overdraft limit cannot be negative");
    }
    overdraftLimit = limit;
}

// Override withdraw to support overdraft
bool ChequingAccount::withdraw(double amount) {
    if (amount <= 0) {
        std::cerr << "Withdrawal amount must be positive" << std::endl;
        return false;
    }

    // Check if withdrawal exceeds balance + overdraft limit
    if (amount > balance + overdraftLimit) {
        std::cerr << "Insufficient funds. Exceeds overdraft limit." << std::endl;
        std::cerr << "Available: $" << balance << " + $" << overdraftLimit
                  << " overdraft = $" << (balance + overdraftLimit) << std::endl;
        return false;
    }

    balance -= amount;

    // Warn if account is now overdrawn
    if (balance < 0) {
        std::cout << "WARNING: Account overdrawn by $" << (-balance) << std::endl;
    }

    return true;
}

// chequing accounts typically have no interest
bool ChequingAccount::applyInterest(const Timestamp& now) {

    // For now just update the timestamp without applying interest
    lastInterestApplied = now;

    // If adding minimal interest:
    // double days = now.daysSince(lastInterestApplied);
    // double minimalRate = 0.0001; // 0.01%
    // double interest = balance * (minimalRate / 365.0) * days;
    // if (interest > 0) {
    //     balance += interest;
    //     return true;
    // }

    return false;  // No interest applied for chequing accounts
}

// Get account type
std::string ChequingAccount::getAccountType() const {
    return "Chequing";
}