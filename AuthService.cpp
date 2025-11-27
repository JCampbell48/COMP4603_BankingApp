#include "AuthService.h"
#include <iostream>

// Constructor
AuthService::AuthService(UserRepository& users, PasswordHasher& hasher)
    : users(users), hasher(hasher) {
}

// Register a new user
bool AuthService::registerUser(const std::string& userId, const std::string& name,
                               const std::string& email, const std::string& password) {
    // Validate inputs
    if (userId.empty()) {
        std::cerr << "User ID cannot be empty" << std::endl;
        return false;
    }

    if (name.empty()) {
        std::cerr << "Name cannot be empty" << std::endl;
        return false;
    }

    if (password.length() < 4) {
        std::cerr << "Password must be at least 4 characters" << std::endl;
        return false;
    }

    // Check if user already exists
    if (users.existsUserId(userId)) {
        std::cerr << "User ID already exists: " << userId << std::endl;
        return false;
    }

    // Hash the password
    std::string passwordHash = hasher.hash(password);

    // Create new user
    User newUser(userId, name, email, passwordHash);

    // Save to repository
    if (users.save(newUser)) {
        std::cout << "User registered successfully: " << userId << std::endl;
        return true;
    }

    return false;
}

// Login a user
User* AuthService::login(const std::string& userId,
                         const std::string& password) {
    // Check if user exists
    if (!users.existsUserId(userId)) {
        std::cerr << "User not found: " << userId << std::endl;
        return nullptr;
    }

    // Get user
    User* user = users.getByUserId(userId);
    if (user == nullptr) {
        return nullptr;
    }

    // Verify password
    if (!hasher.verify(password, user->getPasswordHash())) {
        std::cerr << "Invalid password for user: " << userId << std::endl;
        return nullptr;
    }

    // Update last login time
    user->updateLastLogin();
    users.save(*user);

    std::cout << "Login successful: " << userId << std::endl;
    return user;
}

// Change password
bool AuthService::changePassword(const std::string& userId,
                                const std::string& oldPassword,
                                const std::string& newPassword) {
    // Verify old password first
    User* user = login(userId, oldPassword);
    if (user == nullptr) {
        std::cerr << "Cannot change password: authentication failed" << std::endl;
        return false;
    }

    if (newPassword.length() < 4) {
        std::cerr << "New password must be at least 4 characters" << std::endl;
        return false;
    }

    // Hash new password
    std::string newPasswordHash = hasher.hash(newPassword);

    // Update user
    user->setPasswordHash(newPasswordHash);
    users.save(*user);

    std::cout << "Password changed successfully for user: " << userId << std::endl;
    return true;
}

// Check if user exists
bool AuthService::userExists(const std::string& userId) const {
    return users.existsUserId(userId);
}

// Get user count
size_t AuthService::getUserCount() const {
    return users.getUserCount();
}