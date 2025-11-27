#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <string>
#include "User.h"
#include "UserRepository.h"
#include "PasswordHasher.h"

/**
 * AuthService - Handles user authentication
 * Provides login and registration functionality
 */
class AuthService {
private:
    UserRepository& users;
    PasswordHasher& hasher;

public:
    // Constructor
    AuthService(UserRepository& users, PasswordHasher& hasher);

    // Register a new user
    bool registerUser(const std::string& userId, const std::string& name,
                     const std::string& email, const std::string& password);

    // Login a user (returns nullptr if login fails)
    User* login(const std::string& userId, const std::string& password);

    // Change password
    bool changePassword(const std::string& userId, const std::string& oldPassword,
                       const std::string& newPassword);

    // Check if user exists
    bool userExists(const std::string& userId) const;

    // Get user count
    size_t getUserCount() const;
};

#endif // AUTHSERVICE_H