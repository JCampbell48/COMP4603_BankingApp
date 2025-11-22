#include "Transaction.h"
#include <iostream>
#include <sstream>

// Constructor
Transaction::Transaction(const std::string& transactionId, const Timestamp& timestamp,
                         const std::string& description)
    : transactionId(transactionId), timestamp(timestamp), description(description) {
}

// Getters
std::string Transaction::getId() const {
    return transactionId;
}

Timestamp Transaction::getTimestamp() const {
    return timestamp;
}

std::string Transaction::getDescription() const {
    return description;
}

// Create a record of the transaction
std::string Transaction::record() const {
    std::stringstream ss;
    ss << "Transaction ID: " << transactionId << "\n";
    ss << "Timestamp: " << timestamp.toString() << "\n";
    ss << "Description: " << description;
    return ss.str();
}

// Display transaction details
void Transaction::display() const {
    std::cout << "=== Transaction ===" << std::endl;
    std::cout << record() << std::endl;
}