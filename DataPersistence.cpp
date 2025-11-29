#include "DataPersistence.h"
#include "SavingsAccount.h"
#include "ChequingAccount.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>

// Constructor
DataPersistence::DataPersistence(const std::string& accountsFile,
                                 const std::string& usersFile)
    : accountsFile(accountsFile), usersFile(usersFile) {
}

// Helper: Escape string for storage
std::string DataPersistence::escapeString(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c == '|' || c == '\n' || c == '\r') {
            result += '_';  // Replace special chars with underscore
        } else {
            result += c;
        }
    }
    return result;
}

// Helper: Unescape string after loading
std::string DataPersistence::unescapeString(const std::string& str) {
    return str;  // Simple version - no unescaping needed
}

// Save accounts to file
bool DataPersistence::saveAccounts(const AccountRepository& repository) {
    std::ofstream file(accountsFile);

    if (!file.is_open()) {
        std::cerr << "Failed to open accounts file for writing: "
                  << accountsFile << std::endl;
        return false;
    }

    std::vector<Account*> accounts = repository.getAllAccounts();

    // Write header
    file << "ACCOUNTS_V1" << std::endl;
    file << accounts.size() << std::endl;

    // Write each account
    for (Account* account : accounts) {
        // Format: AccountType|AccountNo|OwnerID|Balance
        file << account->getAccountType() << "|"
             << escapeString(account->getAccountNo()) << "|"
             << escapeString(account->getOwnerId()) << "|"
             << account->getBalance() << std::endl;
    }

    file.close();
    std::cout << "Saved " << accounts.size() << " accounts to " << accountsFile << std::endl;
    return true;
}

// Save users to file
bool DataPersistence::saveUsers(const UserRepository& repository) {
    std::ofstream file(usersFile);

    if (!file.is_open()) {
        std::cerr << "Failed to open users file for writing: "
                  << usersFile << std::endl;
        return false;
    }

    std::vector<User> users = repository.getAllUsers();

    // Write header
    file << "USERS_V1" << std::endl;
    file << users.size() << std::endl;

    // Write each user
    for (const User& user : users) {
        // Format: UserID|Name|Email|PasswordHash
        file << escapeString(user.getUserId()) << "|"
             << escapeString(user.getName()) << "|"
             << escapeString(user.getEmail()) << "|"
             << escapeString(user.getPasswordHash()) << std::endl;
    }

    file.close();
    std::cout << "Saved " << users.size() << " users to " << usersFile << std::endl;
    return true;
}

// Save all data
bool DataPersistence::saveAll(const AccountRepository& accountRepo,
                              const UserRepository& userRepo) {
    bool accountsOk = saveAccounts(accountRepo);
    bool usersOk = saveUsers(userRepo);
    return accountsOk && usersOk;
}

// Load accounts from file
bool DataPersistence::loadAccounts(AccountRepository& repository,
                                   AccountFactory& factory) {
    std::ifstream file(accountsFile);

    if (!file.is_open()) {
        std::cerr << "No existing accounts file found: " << accountsFile << std::endl;
        return false;
    }

    std::string header;
    std::getline(file, header);

    if (header != "ACCOUNTS_V1") {
        std::cerr << "Invalid accounts file format" << std::endl;
        file.close();
        return false;
    }

    int count;
    file >> count;
    file.ignore();  // Skip newline

    int loaded = 0;
    for (int i = 0; i < count; ++i) {
        std::string line;
        std::getline(file, line);

        std::istringstream iss(line);
        std::string accountType, accountNo, ownerId;
        double balance;

        // Parse: AccountType|AccountNo|OwnerID|Balance
        std::getline(iss, accountType, '|');
        std::getline(iss, accountNo, '|');
        std::getline(iss, ownerId, '|');
        iss >> balance;

        // Create appropriate account type
        Account* account = nullptr;

        if (accountType == "Savings") {
            account = new SavingsAccount(unescapeString(accountNo),
                                        unescapeString(ownerId),
                                        balance, 0.02);
        } else if (accountType == "Chequing") {
            account = new ChequingAccount(unescapeString(accountNo),
                                         unescapeString(ownerId),
                                         balance, 500.0);
        }

        if (account) {
            repository.save(account);
            loaded++;
        }
    }

    file.close();
    std::cout << "Loaded " << loaded << " accounts from " << accountsFile << std::endl;
    return true;
}

// Load users from file
bool DataPersistence::loadUsers(UserRepository& repository) {
    std::ifstream file(usersFile);

    if (!file.is_open()) {
        std::cerr << "No existing users file found: " << usersFile << std::endl;
        return false;
    }

    std::string header;
    std::getline(file, header);

    if (header != "USERS_V1") {
        std::cerr << "Invalid users file format" << std::endl;
        file.close();
        return false;
    }

    int count;
    file >> count;
    file.ignore();  // Skip newline

    int loaded = 0;
    for (int i = 0; i < count; ++i) {
        std::string line;
        std::getline(file, line);

        std::istringstream iss(line);
        std::string userId, name, email, passwordHash;

        // Parse: UserID|Name|Email|PasswordHash
        std::getline(iss, userId, '|');
        std::getline(iss, name, '|');
        std::getline(iss, email, '|');
        std::getline(iss, passwordHash, '|');

        User user(unescapeString(userId),
                 unescapeString(name),
                 unescapeString(email),
                 unescapeString(passwordHash));

        repository.save(user);
        loaded++;
    }

    file.close();
    std::cout << "Loaded " << loaded << " users from " << usersFile << std::endl;
    return true;
}

// Load all data
bool DataPersistence::loadAll(AccountRepository& accountRepo,
                              UserRepository& userRepo,
                              AccountFactory& factory) {
    bool usersOk = loadUsers(userRepo);
    bool accountsOk = loadAccounts(accountRepo, factory);

    if (accountsOk) {
        factory.updateCounterFromLoadedAccounts(accountRepo);
    }

    return accountsOk && usersOk;
}

// Check if accounts file exists
bool DataPersistence::accountsFileExists() const {
    struct stat buffer;
    return (stat(accountsFile.c_str(), &buffer) == 0);
}

// Check if users file exists
bool DataPersistence::usersFileExists() const {
    struct stat buffer;
    return (stat(usersFile.c_str(), &buffer) == 0);
}

// Clear accounts file
bool DataPersistence::clearAccountsFile() {
    return (remove(accountsFile.c_str()) == 0);
}

// Clear users file
bool DataPersistence::clearUsersFile() {
    return (remove(usersFile.c_str()) == 0);
}