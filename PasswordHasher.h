#pragma once
#include <string>

/**
 * PasswordHasher - Handles password hashing and verification
 * Uses SHA-256-based hashing with salt for security
 */
class PasswordHasher {
private:
    // Generate a random salt
    static std::string generateSalt();

    // Compute SHA-256 hash of a string
    static std::string sha256(const std::string& input);

public:
    // Hash a password with salt (returns salt:hash format)
    static std::string hash(const std::string& password);

    // Verify a password against a stored hash
    static bool verify(const std::string& password, const std::string& storedHash);
};
