#pragma once

#include <string>
#include "BankSystem.h"
#include "AccountType.h"

/**
 * BankUI - Console User Interface for Banking System
 * Provides interactive menu-driven interface for banking operations
 */
class BankUI {
private:
    BankSystem& bank;
    bool running;

    // Display functions
    void displayMainMenu() const;
    void displayHeader(const std::string& title) const;
    void displaySuccess(const std::string& message) const;
    void displayError(const std::string& message) const;
    void pressEnterToContinue() const;
    void clearScreen() const;

    // Input helpers
    int getIntInput(const std::string& prompt) const;
    double getDoubleInput(const std::string& prompt) const;
    std::string getStringInput(const std::string& prompt) const;
    AccountType getAccountTypeInput() const;

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
    void handleExit();

public:
    // Constructor
    BankUI(BankSystem& bank);

    // Main UI loop
    void run();
};
