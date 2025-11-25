#include "BankUI.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include "Timestamp.h"

using namespace std;

// Constructor
BankUI::BankUI(BankSystem& bank) : bank(bank), running(true) {
}

// Clear screen (platform independent)
void BankUI::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Display header
void BankUI::displayHeader(const string& title) const {
    cout << "\n";
    cout << string(60, '=') << endl;
    cout << "   " << title << endl;
    cout << string(60, '=') << endl;
}

// Display main menu
void BankUI::displayMainMenu() const {
    displayHeader("BANKING SYSTEM - MAIN MENU");
    cout << "\n";
    cout << "  1.  Create New Account" << endl;
    cout << "  2.  Deposit Money" << endl;
    cout << "  3.  Withdraw Money" << endl;
    cout << "  4.  Transfer Money" << endl;
    cout << "  5.  Check Balance" << endl;
    cout << "  6.  View My Accounts" << endl;
    cout << "  7.  View Account Summary" << endl;
    cout << "  8.  View All Accounts (Admin)" << endl;
    cout << "  9.  Delete Account" << endl;
    cout << "  10. Apply Interest" << endl;
    cout << "  0.  Exit" << endl;
    cout << "\n";
    cout << string(60, '-') << endl;
}

// Display success message
void BankUI::displaySuccess(const string& message) const {
    cout << "\n✓ SUCCESS: " << message << endl;
}

// Display error message
void BankUI::displayError(const string& message) const {
    cout << "\n✗ ERROR: " << message << endl;
}

// Press enter to continue
void BankUI::pressEnterToContinue() const {
    cout << "\nPress ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Get integer input with validation
int BankUI::getIntInput(const string& prompt) const {
    int value;
    cout << prompt;

    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Get double input with validation
double BankUI::getDoubleInput(const string& prompt) const {
    double value;
    cout << prompt;

    while (!(cin >> value) || value < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (value < 0) {
            cout << "Amount cannot be negative. Please try again: ";
        } else {
            cout << "Invalid input. Please enter a number: ";
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Get string input
string BankUI::getStringInput(const string& prompt) const {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

// Get account type from user
AccountType BankUI::getAccountTypeInput() const {
    cout << "\nAccount Types:" << endl;
    cout << "  1. Savings Account (2% interest, no overdraft)" << endl;
    cout << "  2. Chequing Account ($500 overdraft, no interest)" << endl;

    int choice = getIntInput("\nSelect account type (1-2): ");

    switch (choice) {
        case 1:
            return AccountType::Savings;
        case 2:
            return AccountType::Chequing;
        default:
            cout << "Invalid choice. Defaulting to Savings." << endl;
            return AccountType::Savings;
    }
}

// Handler: Create Account
void BankUI::handleCreateAccount() {
    clearScreen();
    displayHeader("CREATE NEW ACCOUNT");

    string ownerId = getStringInput("\nEnter your User ID: ");

    if (ownerId.empty()) {
        displayError("User ID cannot be empty.");
        pressEnterToContinue();
        return;
    }

    AccountType type = getAccountTypeInput();
    double initialBalance = getDoubleInput("\nEnter initial deposit amount: $");

    Account* account = bank.createAccount(ownerId, type, initialBalance);

    if (account) {
        displaySuccess("Account created successfully!");
        cout << "\n  Account Number: " << account->getAccountNo() << endl;
        cout << "  Account Type: " << account->getAccountType() << endl;
        cout << "  Initial Balance: $" << fixed << setprecision(2)
             << account->getBalance() << endl;
    } else {
        displayError("Failed to create account. Please try again.");
    }

    pressEnterToContinue();
}

// Handler: Deposit
void BankUI::handleDeposit() {
    clearScreen();
    displayHeader("DEPOSIT MONEY");

    string accountNo = getStringInput("\nEnter account number: ");

    if (!bank.accountExists(accountNo)) {
        displayError("Account not found.");
        pressEnterToContinue();
        return;
    }

    cout << "\nCurrent balance: $" << fixed << setprecision(2)
         << bank.getBalance(accountNo) << endl;

    double amount = getDoubleInput("\nEnter deposit amount: $");

    if (amount <= 0) {
        displayError("Deposit amount must be greater than zero.");
        pressEnterToContinue();
        return;
    }

    if (bank.deposit(accountNo, amount)) {
        displaySuccess("Deposit completed successfully!");
        cout << "  New balance: $" << fixed << setprecision(2)
             << bank.getBalance(accountNo) << endl;
    } else {
        displayError("Deposit failed. Please try again.");
    }

    pressEnterToContinue();
}

// Handler: Withdraw
void BankUI::handleWithdraw() {
    clearScreen();
    displayHeader("WITHDRAW MONEY");

    string accountNo = getStringInput("\nEnter account number: ");

    if (!bank.accountExists(accountNo)) {
        displayError("Account not found.");
        pressEnterToContinue();
        return;
    }

    cout << "\nCurrent balance: $" << fixed << setprecision(2)
         << bank.getBalance(accountNo) << endl;

    double amount = getDoubleInput("\nEnter withdrawal amount: $");

    if (amount <= 0) {
        displayError("Withdrawal amount must be greater than zero.");
        pressEnterToContinue();
        return;
    }

    if (bank.withdraw(accountNo, amount)) {
        displaySuccess("Withdrawal completed successfully!");
        cout << "  New balance: $" << fixed << setprecision(2)
             << bank.getBalance(accountNo) << endl;
    } else {
        displayError("Withdrawal failed. Insufficient funds or invalid amount.");
    }

    pressEnterToContinue();
}

// Handler: Transfer
void BankUI::handleTransfer() {
    clearScreen();
    displayHeader("TRANSFER MONEY");

    string fromAccount = getStringInput("\nFrom account number: ");

    if (!bank.accountExists(fromAccount)) {
        displayError("Source account not found.");
        pressEnterToContinue();
        return;
    }

    cout << "\nSource account balance: $" << fixed << setprecision(2)
         << bank.getBalance(fromAccount) << endl;

    string toAccount = getStringInput("\nTo account number: ");

    if (!bank.accountExists(toAccount)) {
        displayError("Destination account not found.");
        pressEnterToContinue();
        return;
    }

    if (fromAccount == toAccount) {
        displayError("Cannot transfer to the same account.");
        pressEnterToContinue();
        return;
    }

    double amount = getDoubleInput("\nEnter transfer amount: $");

    if (amount <= 0) {
        displayError("Transfer amount must be greater than zero.");
        pressEnterToContinue();
        return;
    }

    if (bank.transfer(fromAccount, toAccount, amount)) {
        displaySuccess("Transfer completed successfully!");
        cout << "  " << fromAccount << " balance: $" << fixed << setprecision(2)
             << bank.getBalance(fromAccount) << endl;
        cout << "  " << toAccount << " balance: $" << fixed << setprecision(2)
             << bank.getBalance(toAccount) << endl;
    } else {
        displayError("Transfer failed. Please check account balances.");
    }

    pressEnterToContinue();
}

// Handler: Check Balance
void BankUI::handleCheckBalance() {
    clearScreen();
    displayHeader("CHECK BALANCE");

    string accountNo = getStringInput("\nEnter account number: ");

    if (!bank.accountExists(accountNo)) {
        displayError("Account not found.");
        pressEnterToContinue();
        return;
    }

    double balance = bank.getBalance(accountNo);

    cout << "\n";
    cout << "  Account: " << accountNo << endl;
    cout << "  Type: " << bank.getAccountType(accountNo) << endl;
    cout << "  Owner: " << bank.getOwnerId(accountNo) << endl;
    cout << "  Balance: $" << fixed << setprecision(2) << balance << endl;

    pressEnterToContinue();
}

// Handler: View My Accounts
void BankUI::handleViewMyAccounts() {
    clearScreen();
    displayHeader("MY ACCOUNTS");

    string ownerId = getStringInput("\nEnter your User ID: ");

    vector<string> accounts = bank.getAccountsByOwner(ownerId);

    if (accounts.empty()) {
        cout << "\nNo accounts found for user: " << ownerId << endl;
    } else {
        cout << "\nAccounts for " << ownerId << ":" << endl;
        cout << string(60, '-') << endl;

        for (const auto& accountNo : accounts) {
            cout << "\n  Account: " << accountNo << endl;
            cout << "    Type: " << bank.getAccountType(accountNo) << endl;
            cout << "    Balance: $" << fixed << setprecision(2)
                 << bank.getBalance(accountNo) << endl;
        }

        cout << string(60, '-') << endl;
        cout << "Total accounts: " << accounts.size() << endl;
    }

    pressEnterToContinue();
}

// Handler: View Account Summary
void BankUI::handleViewAccountSummary() {
    clearScreen();
    displayHeader("ACCOUNT SUMMARY");

    string accountNo = getStringInput("\nEnter account number: ");

    if (!bank.accountExists(accountNo)) {
        displayError("Account not found.");
        pressEnterToContinue();
        return;
    }

    bank.displayAccountSummary(accountNo);

    pressEnterToContinue();
}

// Handler: View All Accounts (Admin)
void BankUI::handleViewAllAccounts() {
    clearScreen();
    displayHeader("ALL ACCOUNTS (ADMIN VIEW)");

    cout << "\n";
    bank.displayAllAccounts();

    pressEnterToContinue();
}

// Handler: Delete Account
void BankUI::handleDeleteAccount() {
    clearScreen();
    displayHeader("DELETE ACCOUNT");

    string accountNo = getStringInput("\nEnter account number to delete: ");

    if (!bank.accountExists(accountNo)) {
        displayError("Account not found.");
        pressEnterToContinue();
        return;
    }

    // Show account details
    cout << "\nAccount to delete:" << endl;
    cout << "  Account: " << accountNo << endl;
    cout << "  Type: " << bank.getAccountType(accountNo) << endl;
    cout << "  Balance: $" << fixed << setprecision(2)
         << bank.getBalance(accountNo) << endl;

    string confirm = getStringInput("\nAre you sure you want to delete this account? (yes/no): ");

    if (confirm == "yes" || confirm == "YES" || confirm == "Yes") {
        if (bank.deleteAccount(accountNo)) {
            displaySuccess("Account deleted successfully!");
        } else {
            displayError("Cannot delete account. Please ensure balance is zero.");
        }
    } else {
        cout << "\nAccount deletion cancelled." << endl;
    }

    pressEnterToContinue();
}

// Handler: Apply Interest
void BankUI::handleApplyInterest() {
    clearScreen();
    displayHeader("APPLY INTEREST");

    string accountNo = getStringInput("\nEnter account number: ");

    if (!bank.accountExists(accountNo)) {
        displayError("Account not found.");
        pressEnterToContinue();
        return;
    }

    string accountType = bank.getAccountType(accountNo);

    if (accountType != "Savings") {
        displayError("Interest can only be applied to Savings accounts.");
        pressEnterToContinue();
        return;
    }

    double oldBalance = bank.getBalance(accountNo);

    if (bank.applyInterest(accountNo, Timestamp::now())) {
        double newBalance = bank.getBalance(accountNo);
        double interest = newBalance - oldBalance;

        displaySuccess("Interest applied successfully!");
        cout << "  Interest earned: $" << fixed << setprecision(2) << interest << endl;
        cout << "  New balance: $" << newBalance << endl;
    } else {
        cout << "\nNo interest applied (account updated recently or no balance)." << endl;
    }

    pressEnterToContinue();
}

// Handler: Exit
void BankUI::handleExit() {
    clearScreen();
    displayHeader("EXIT");

    cout << "\nThank you for using the Banking System!" << endl;
    cout << "Goodbye!\n" << endl;

    running = false;
}

// Main UI loop
void BankUI::run() {
    clearScreen();

    cout << "\n";
    cout << string(60, '=') << endl;
    cout << "       WELCOME TO THE BANKING SYSTEM" << endl;
    cout << string(60, '=') << endl;
    cout << "\n";

    pressEnterToContinue();

    while (running) {
        clearScreen();
        displayMainMenu();

        int choice = getIntInput("Enter your choice (0-10): ");

        switch (choice) {
            case 1:
                handleCreateAccount();
                break;
            case 2:
                handleDeposit();
                break;
            case 3:
                handleWithdraw();
                break;
            case 4:
                handleTransfer();
                break;
            case 5:
                handleCheckBalance();
                break;
            case 6:
                handleViewMyAccounts();
                break;
            case 7:
                handleViewAccountSummary();
                break;
            case 8:
                handleViewAllAccounts();
                break;
            case 9:
                handleDeleteAccount();
                break;
            case 10:
                handleApplyInterest();
                break;
            case 0:
                handleExit();
                break;
            default:
                displayError("Invalid choice. Please select 0-10.");
                pressEnterToContinue();
                break;
        }
    }
}