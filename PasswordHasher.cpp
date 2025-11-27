#include "PasswordHasher.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <functional>

// Generate a random salt (16 characters)
std::string PasswordHasher::generateSalt() {
    const std::string characters =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string salt;
    for (int i = 0; i < 16; ++i) {
        salt += characters[distribution(generator)];
    }

    return salt;
}

// Simple hash function using std::hash (for educational purposes)
// In production, use a proper cryptographic hash like bcrypt or PBKDF2
std::string PasswordHasher::sha256(const std::string& input) {
    // Use std::hash for simplicity
    // Note: In production, use a proper cryptographic hash library
    std::hash<std::string> hasher;
    size_t hashValue = hasher(input);

    // Convert to hex string
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(16) << hashValue;

    // Apply multiple rounds for better security
    std::string result = ss.str();
    for (int i = 0; i < 1000; ++i) {
        hashValue = hasher(result + input);
        ss.str("");
        ss << std::hex << std::setfill('0') << std::setw(16) << hashValue;
        result = ss.str();
    }

    return result;
}

// Hash a password with salt
// Format: salt:hash
std::string PasswordHasher::hash(const std::string& password) {
    std::string salt = generateSalt();
    std::string combined = salt + password;
    std::string hashed = sha256(combined);

    return salt + ":" + hashed;
}

// Verify a password against stored hash
bool PasswordHasher::verify(const std::string& password, const std::string& storedHash) {
    // Find the separator
    size_t separatorPos = storedHash.find(':');
    if (separatorPos == std::string::npos) {
        return false;
    }

    // Extract salt and hash
    std::string salt = storedHash.substr(0, separatorPos);
    std::string originalHash = storedHash.substr(separatorPos + 1);

    // Hash the provided password with the same salt
    std::string combined = salt + password;
    std::string newHash = sha256(combined);

    // Compare hashes
    return newHash == originalHash;
}