#include "AccountFactory.h"
#include "AccountRepository.h"
#include "SavingsAccount.h"
#include "ChequingAccount.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

// Initialize static counter
int AccountFactory::accountCounter = 1000;

// Constructor
AccountFactory::AccountFactory() {
    // Nothing special needed for now
}

// Generate unique account number
std::string AccountFactory::generateAccountNumber(AccountType type) {
    std::stringstream ss;

    // Prefix based on account type
    switch (type) {
        case AccountType::Savings:
            ss << "SAV-";
            break;
        case AccountType::Chequing:
            ss << "CHQ-";
            break;
        case AccountType::TFSA:
            ss << "TFSA-";
            break;
        default:
            ss << "ACC-";
            break;
    }

    // Add sequential number with leading zeros
    ss << std::setfill('0') << std::setw(6) << accountCounter++;

    return ss.str();
}

// Updates the static counter from all the loaded accounts
void AccountFactory::updateCounterFromLoadedAccounts(const AccountRepository& repo)
{
    int maxNumeric = 0;

    std::vector<Account*> accounts = repo.getAllAccounts();

    for (Account* acc : accounts) {
        std::string accNo = acc->getAccountNo();

        std::size_t pos = accNo.find_last_not_of("0123456789");
        if (pos == std::string::npos || pos + 1 >= accNo.size()) {
            continue;
        }

        std::string numPart = accNo.substr(pos + 1);
        try {
            int value = std::stoi(numPart);
            if (value > maxNumeric) {
                maxNumeric = value;
            }
        } catch (...) {
            // ignore malformed IDs
        }
    }

    if (maxNumeric >= accountCounter) {
        accountCounter = maxNumeric + 1;
    }
}

// Create account with default balance (0.0)
Account* AccountFactory::create(AccountType type, const std::string& ownerId) {
    return create(type, ownerId, 0.0);
}

// Create account with specified initial balance
Account* AccountFactory::create(AccountType type, const std::string& ownerId,
                                double initialBalance) {
    std::string accountNo = generateAccountNumber(type);

    switch (type) {
        case AccountType::Savings:
            // Create savings account with default 2% interest rate
            return new SavingsAccount(accountNo, ownerId, initialBalance, 0.02);

        case AccountType::Chequing:
            // Create chequing account with default $500 overdraft
            return new ChequingAccount(accountNo, ownerId, initialBalance, 500.0);

        case AccountType::TFSA:
            // TFSA not implemented yet - throw error for now
            throw std::runtime_error("TFSA account type not yet implemented");

        default:
            throw std::invalid_argument("Unknown account type");
    }
}

// Convert AccountType to string
std::string AccountFactory::accountTypeToString(AccountType type) {
    switch (type) {
        case AccountType::Savings:
            return "Savings";
        case AccountType::Chequing:
            return "Chequing";
        case AccountType::TFSA:
            return "TFSA";
        default:
            return "Unknown";
    }
}