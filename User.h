#pragma once

#include <string>
#include "Timestamp.h"

/**
 * User - Represents a user in the banking system
 * Used for authentication and account ownership
 */
class User {
private:
    std::string userId;
    std::string name;
    std::string email;
    std::string passwordHash;
    Timestamp createdAt;
    Timestamp lastLogin;

public:
    // Constructors
    User();
    User(const std::string& userId, const std::string& name,
         const std::string& email, const std::string& passwordHash);

    // Getters
    std::string getUserId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPasswordHash() const;
    Timestamp getCreatedAt() const;
    Timestamp getLastLogin() const;

    // Setters
    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setPasswordHash(const std::string& hash);
    void updateLastLogin();

    // Display
    void display() const;
};
