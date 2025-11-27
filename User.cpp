#include "User.h"
#include <iostream>
#include <iomanip>

// Default constructor
User::User() : userId(""), name(""), email(""), passwordHash(""),
               createdAt(Timestamp::now()), lastLogin(Timestamp::now()) {
}

// Parameterized constructor
User::User(const std::string& userId, const std::string& name,
           const std::string& email, const std::string& passwordHash)
    : userId(userId), name(name), email(email), passwordHash(passwordHash),
      createdAt(Timestamp::now()), lastLogin(Timestamp::now()) {
}

// Getters
std::string User::getUserId() const {
    return userId;
}

std::string User::getName() const {
    return name;
}

std::string User::getEmail() const {
    return email;
}

std::string User::getPasswordHash() const {
    return passwordHash;
}

Timestamp User::getCreatedAt() const {
    return createdAt;
}

Timestamp User::getLastLogin() const {
    return lastLogin;
}

// Setters
void User::setName(const std::string& name) {
    this->name = name;
}

void User::setEmail(const std::string& email) {
    this->email = email;
}

void User::setPasswordHash(const std::string& hash) {
    this->passwordHash = hash;
}

void User::updateLastLogin() {
    this->lastLogin = Timestamp::now();
}

// Display info
void User::display() const {
    std::cout << "\n=== User Information ===" << std::endl;
    std::cout << "User ID: " << userId << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Created: " << createdAt.toString() << std::endl;
    std::cout << "Last Login: " << lastLogin.toString() << std::endl;
    std::cout << "======================\n" << std::endl;
}