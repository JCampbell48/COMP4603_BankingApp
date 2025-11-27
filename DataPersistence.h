#pragma once

#include <string>
#include "AccountRepository.h"
#include "UserRepository.h"
#include "AccountFactory.h"

/**
 * DataPersistence - Handles saving and loading system data
 * Provides file-based persistence for accounts and users
 */
class DataPersistence {
private:
    std::string accountsFile;
    std::string usersFile;

    // Helper methods for JSON-style formatting
    static std::string escapeString(const std::string& str);
    static std::string unescapeString(const std::string& str);

public:
    // Constructor
    DataPersistence(const std::string& accountsFile = "accounts.dat",
                   const std::string& usersFile = "users.dat");

    // Save operations
    bool saveAccounts(const AccountRepository& repository);
    bool saveUsers(const UserRepository& repository);
    bool saveAll(const AccountRepository& accountRepo,
                const UserRepository& userRepo);

    // Load operations
    bool loadAccounts(AccountRepository& repository, AccountFactory& factory);
    bool loadUsers(UserRepository& repository);
    bool loadAll(AccountRepository& accountRepo, UserRepository& userRepo,
                AccountFactory& factory);

    // File management
    bool accountsFileExists() const;
    bool usersFileExists() const;
    bool clearAccountsFile();
    bool clearUsersFile();
};
