#pragma once
#include<string>
#include "Timestamp.h"

/**
 * Abstract base class for all banking transactions
 * Uses Command Pattern - transactions can be executed and undone
 */
class Transaction {
protected:
    std::string transactionId;
    Timestamp timestamp;
    std::string description;

public:
    Transaction(const std::string& transactionId, const Timestamp& timestamp,
                const std::string& description);

    // Virtual destructor
    virtual ~Transaction() = default;

    // Getters
    std::string getId() const;
    Timestamp getTimestamp() const;
    std::string getDescription() const;

    // Pure virtual methods - must be implemented by subclasses
    virtual bool execute() = 0;
    virtual bool undo() = 0;

    // Transaction records (for history/logging)
    virtual std::string record() const;

    // Display transaction details
    virtual void display() const;

};
