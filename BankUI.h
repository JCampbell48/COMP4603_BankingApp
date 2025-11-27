#ifndef BANKUI_H
#define BANKUI_H

#include <string>
#include "BankSystem.h"
#include "AccountType.h"
#include "AuthService.h"
#include "User.h"

/**
 * BankUI - Console User Interface for Banking System
 * Provides interactive menu-driven interface for banking operations
 * Now with authentication support
 */
class BankUI {
private:
    BankSystem& bank;
    AuthService& auth;
    User* currentUser;  // Currently logged-in user (nullptr if not logged in)
    bool running;

    // Display functions
    void displayMainMenu() const;
    void displayLoginMenu() const;
    void displayHeader(const std::string& title) const;
    void displaySuccess(const std::string& message) const;
    void displayError(const std::string& message) const;
    void pressEnterToContinue() const;
    void clearScreen() const;

    // Input helpers
    int getIntInput(const std::string& prompt) const;
    double getDoubleInput(const std::string& prompt) const;
    std::string getStringInput(const std::string& prompt) const;
    std::string getPasswordInput(const std::string& prompt) const;
    AccountType getAccountTypeInput() const;

    // Authentication handlers
    void handleLogin();
    void handleRegister();
    void handleLogout();

    // Menu handlers
    void handleCreateAccount();
    void handleDeposit();
    void handleWithdraw();
    void handleTransfer();
    void handleCheckBalance();
    void handleViewMyAccounts();
    void handleViewAccountSummary();
    void handleViewAllAccounts();
    void handleDeleteAccount();
    void handleApplyInterest();
    void handleChangePassword();
    void handleExit();

    // Helper to check if user is logged in
    bool requireLogin();

public:
    // Constructor
    BankUI(BankSystem& bank, AuthService& auth);

    // Main UI loop
    void run();
};

#endif // BANKUI_H