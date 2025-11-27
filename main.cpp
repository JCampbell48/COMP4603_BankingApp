#include <iostream>
#include "BankUI.h"
#include "BankSystem.h"
#include "AccountRepository.h"
#include "AccountFactory.h"
#include "AuthService.h"
#include "UserRepository.h"
#include "PasswordHasher.h"
#include "DataPersistence.h"

/**
 * Banking System - Main Entry Point
 *
 * This is a complete console-based banking system with:
 * - User authentication (login/register)
 * - Account management (create, delete, view)
 * - Banking operations (deposit, withdraw, transfer)
 * - Multiple account types (Savings, Chequing)
 * - Interest calculation
 * - Transaction history
 * - Password security
 * - Data persistence (save/load)
 * - User-friendly console interface
 */

int main() {
    try {
        // Initialize core components
        AccountRepository repository;
        AccountFactory factory;
        BankSystem bank(repository, factory);

        // Initialize authentication components
        UserRepository userRepository;
        PasswordHasher hasher;
        AuthService auth(userRepository, hasher);

        // Initialize data persistence
        DataPersistence persistence("accounts.dat", "users.dat");

        // Load existing data
        std::cout << "Loading existing data..." << std::endl;
        persistence.loadAll(repository, userRepository, factory);
        std::cout << std::endl;

        // Optional: Create a demo user for testing (only if no users exist)
        // Uncomment to create a test user (user: demo, password: demo123)

        // if (auth.getUserCount() == 0) {
        //     std::cout << "Creating demo user..." << std::endl;
        //     auth.registerUser("demo", "Demo User", "demo@example.com", "demo123");
        //     bank.createAccount("demo", AccountType::Savings, 1000.0);
        //     bank.createAccount("demo", AccountType::Chequing, 500.0);
        //     persistence.saveAll(repository, userRepository);
        //     std::cout << std::endl;
        // }


        // Create and run the UI
        BankUI ui(bank, auth);
        ui.run();

        // Save data on exit
        std::cout << "\nSaving data..." << std::endl;
        persistence.saveAll(repository, userRepository);
        std::cout << "Data saved successfully." << std::endl;

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}