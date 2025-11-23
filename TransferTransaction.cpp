#include "TransferTransaction.h"
#include <iostream>
#include <sstream>

// Constructor
TransferTransaction::TransferTransaction(Account& fromAccount, Account& toAccount,
    double amount, const Timestamp& timestamp, const std::string& description) :
        Transaction("TRF-" + fromAccount.getAccountNo() + "-" + toAccount.getAccountNo()
            + "-" + timestamp.toString(), timestamp, description), fromAccount(fromAccount),
                toAccount(toAccount), amount(amount), executed(false) {
}

// Execute the transfer
bool TransferTransaction::execute() {
    if (executed) {
        std::cerr << "Transaction already executed!" << std::endl;
        return false;
    }

    if (fromAccount.transferTo(toAccount, amount)) {
        executed = true;
        std::cout << "Transfer executed: $" << amount
                  << " from " << fromAccount.getAccountNo()
                  << " to " << toAccount.getAccountNo() << std::endl;
        return true;
    }

    return false;
}

// Undo the transfer (transfer back)
bool TransferTransaction::undo() {
    if (!executed) {
        std::cerr << "Cannot undo: Transaction not executed!" << std::endl;
        return false;
    }

    // Transfer back from toAccount to fromAccount
    if (toAccount.transferTo(fromAccount, amount)) {
        executed = false;
        std::cout << "Transfer undone: $" << amount
                  << " transferred back from " << toAccount.getAccountNo()
                  << " to " << fromAccount.getAccountNo() << std::endl;
        return true;
    }

    std::cerr << "Failed to undo transfer - insufficient funds in target account" << std::endl;
    return false;
}

// Create detailed record
std::string TransferTransaction::record() const {
    std::stringstream ss;
    ss << Transaction::record() << "\n";
    ss << "Type: Transfer\n";
    ss << "From Account: " << fromAccount.getAccountNo() << "\n";
    ss << "To Account: " << toAccount.getAccountNo() << "\n";
    ss << "Amount: $" << amount << "\n";
    ss << "Status: " << (executed ? "Executed" : "Not Executed");
    return ss.str();
}

// Getters
double TransferTransaction::getAmount() const {
    return amount;
}

std::string TransferTransaction::getFromAccountNo() const {
    return fromAccount.getAccountNo();
}

std::string TransferTransaction::getToAccountNo() const {
    return toAccount.getAccountNo();
}