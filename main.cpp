#include <iostream>
#include "BankUI.h"
#include "BankSystem.h"
#include "AccountRepository.h"
#include "AccountFactory.h"

/**
 * Banking System - Main Entry Point
 *
 * This is a complete console-based banking system with:
 * - Account management (create, delete, view)
 * - Banking operations (deposit, withdraw, transfer)
 * - Multiple account types (Savings, Chequing)
 * - Interest calculation
 * - Transaction history
 * - User-friendly console interface
 */

int main() {
    try {
        // Initialize core components
        AccountRepository repository;
        AccountFactory factory;
        BankSystem bank(repository, factory);

        // Create some demo accounts for testing
        // Uncomment for pre-populated data

        bank.createAccount("demo_user", AccountType::Savings, 1000.0);
        bank.createAccount("demo_user", AccountType::Chequing, 500.0);
        bank.createAccount("alice", AccountType::Savings, 2000.0);
        bank.createAccount("bob", AccountType::Chequing, 1500.0);


        // Create and run the UI
        BankUI ui(bank);
        ui.run();

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}