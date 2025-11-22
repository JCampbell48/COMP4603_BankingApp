#include <iostream>
#include <iomanip>
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#include "Timestamp.h"

int main() {
    std::cout << "=== ChequingAccount Test ===" << std::endl << std::endl;

    try {
        // Create a chequing account with $500 balance and $200 overdraft
        ChequingAccount chequing("CHQ-001", "USER-789", 500.0, 200.0);

        std::cout << "Chequing Account created:" << std::endl;
        std::cout << "  Account No: " << chequing.getAccountNo() << std::endl;
        std::cout << "  Type: " << chequing.getAccountType() << std::endl;
        std::cout << "  Balance: $" << std::fixed << std::setprecision(2)
                  << chequing.getBalance() << std::endl;
        std::cout << "  Overdraft Limit: $" << chequing.getOverdraftLimit() << std::endl;
        std::cout << "  Total Available: $"
                  << (chequing.getBalance() + chequing.getOverdraftLimit()) << std::endl;
        std::cout << std::endl;

        // Test normal withdrawal
        std::cout << "Test 1: Withdraw $300 (within balance)..." << std::endl;
        if (chequing.withdraw(300.0)) {
            std::cout << "  Success! New balance: $" << chequing.getBalance() << std::endl;
        }
        std::cout << std::endl;

        // Test overdraft withdrawal
        std::cout << "Test 2: Withdraw $300 (will use overdraft)..." << std::endl;
        if (chequing.withdraw(300.0)) {
            std::cout << "  Success! New balance: $" << chequing.getBalance() << std::endl;
            std::cout << "  Overdraft used: $" << (-chequing.getBalance()) << std::endl;
            std::cout << "  Remaining overdraft: $"
                      << (chequing.getOverdraftLimit() + chequing.getBalance()) << std::endl;
        }
        std::cout << std::endl;

        // Test exceeding overdraft limit
        std::cout << "Test 3: Try to withdraw $300 (exceeds overdraft limit)..." << std::endl;
        if (!chequing.withdraw(300.0)) {
            std::cout << "  Failed as expected!" << std::endl;
        }
        std::cout << std::endl;

        // Deposit to recover
        std::cout << "Test 4: Deposit $500 to recover..." << std::endl;
        if (chequing.deposit(500.0)) {
            std::cout << "  Success! New balance: $" << chequing.getBalance() << std::endl;
        }
        std::cout << std::endl;

        // Compare with SavingsAccount (no overdraft)
        std::cout << "=== Comparison with SavingsAccount ===" << std::endl << std::endl;
        SavingsAccount savings("SAV-001", "USER-789", 200.0, 0.05);

        std::cout << "Savings Account: $" << savings.getBalance() << std::endl;
        std::cout << "Try to withdraw $300 (no overdraft allowed)..." << std::endl;
        if (!savings.withdraw(300.0)) {
            std::cout << "  Failed as expected - savings accounts have no overdraft!" << std::endl;
        }
        std::cout << std::endl;

        // Test interest application (chequing typically has none)
        std::cout << "=== Interest Test ===" << std::endl << std::endl;
        std::cout << "Apply interest to chequing account..." << std::endl;
        if (chequing.applyInterest(Timestamp::now())) {
            std::cout << "  Interest applied" << std::endl;
        } else {
            std::cout << "  No interest on chequing accounts (as expected)" << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Apply interest to savings account..." << std::endl;
        if (savings.applyInterest(Timestamp::now())) {
            std::cout << "  Interest applied!" << std::endl;
        }
        std::cout << std::endl;

        std::cout << "=== All tests completed ===" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}