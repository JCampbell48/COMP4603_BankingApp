#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <string>
#include <map>
#include <vector>
#include "User.h"

/**
 * UserRepository - Repository Pattern for user storage and retrieval
 * Manages the collection of users and provides query methods
 */
class UserRepository {
private:
    // Storage: map of userId -> User
    std::map<std::string, User> users;

public:
    // Constructor
    UserRepository();

    // Destructor
    ~UserRepository();

    // Get user by user ID (returns nullptr if not found)
    User* getByUserId(const std::string& userId);

    // Get user by user ID (const version, returns nullptr if not found)
    const User* getByUserId(const std::string& userId) const;

    // Save (add or update) a user
    bool save(const User& user);

    // Remove user by user ID
    bool remove(const std::string& userId);

    // Check if user ID exists
    bool existsUserId(const std::string& userId) const;

    // Get all users
    std::vector<User> getAllUsers() const;

    // Get count of users
    size_t getUserCount() const;

    // Clear all users
    void clear();
};

#endif // USERREPOSITORY_H