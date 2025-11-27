#include "UserRepository.h"
#include <iostream>

// Constructor
UserRepository::UserRepository() {
}

// Destructor
UserRepository::~UserRepository() {
    clear();
}

User* UserRepository::getByUserId(const std::string& userId) {
    auto it = users.find(userId);
    if (it != users.end()) {
        return &(it->second);
    }
    return nullptr;  // Return null if not found
}

const User* UserRepository::getByUserId(const std::string& userId) const {
    auto it = users.find(userId);
    if (it != users.end()) {
        return &(it->second);
    }
    return nullptr;
}

// Save (add or update) a user
bool UserRepository::save(const User& user) {
    std::string userId = user.getUserId();

    if (userId.empty()) {
        std::cerr << "Cannot save user with empty user ID" << std::endl;
        return false;
    }

    // Check if user already exists
    if (users.find(userId) != users.end()) {
        // Update existing user
        users[userId] = user;
        std::cout << "Updated existing user: " << userId << std::endl;
    } else {
        // Add new user
        users[userId] = user;
        std::cout << "Added new user: " << userId << std::endl;
    }

    return true;
}

// Remove user by user ID
bool UserRepository::remove(const std::string& userId) {
    auto it = users.find(userId);
    if (it != users.end()) {
        users.erase(it);
        std::cout << "Removed user: " << userId << std::endl;
        return true;
    }

    std::cerr << "User not found: " << userId << std::endl;
    return false;
}

// Check if user ID exists
bool UserRepository::existsUserId(const std::string& userId) const {
    return users.find(userId) != users.end();
}

// Get all users
std::vector<User> UserRepository::getAllUsers() const {
    std::vector<User> result;
    for (const auto& pair : users) {
        result.push_back(pair.second);
    }
    return result;
}

// Get count of users
size_t UserRepository::getUserCount() const {
    return users.size();
}

// Clear all users
void UserRepository::clear() {
    users.clear();
}