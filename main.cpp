#include <iostream>
#include <iomanip>
#include "Account.h"
#include "SavingsAccount.h"
#include "Timestamp.h"

int main() {
    std::cout << "=== Banking System - Account Class Test ===" << std::endl << std::endl;

    try {
        // Create a savings account
        SavingsAccount account1("ACC-001", "USER-123", 1000.0, 0.05);

        std::cout << "Account created:" << std::endl;
        std::cout << "  Account No: " << account1.getAccountNo() << std::endl;
        std::cout << "  Owner ID: " << account1.getOwnerId() << std::endl;
        std::cout << "  Type: " << account1.getAccountType() << std::endl;
        std::cout << "  Initial Balance: $" << std::fixed << std::setprecision(2)
                  << account1.getBalance() << std::endl;
        std::cout << "  Interest Rate: " << (account1.getInterestRate() * 100) << "%" << std::endl;
        std::cout << std::endl;

        // Test deposit
        std::cout << "Testing deposit of $500..." << std::endl;
        if (account1.deposit(500.0)) {
            std::cout << "  Success! New balance: $" << account1.getBalance() << std::endl;
        }
        std::cout << std::endl;

        // Test withdrawal
        std::cout << "Testing withdrawal of $200..." << std::endl;
        if (account1.withdraw(200.0)) {
            std::cout << "  Success! New balance: $" << account1.getBalance() << std::endl;
        }
        std::cout << std::endl;

        // Test insufficient funds
        std::cout << "Testing withdrawal of $5000 (should fail)..." << std::endl;
        if (!account1.withdraw(5000.0)) {
            std::cout << "  Failed as expected. Balance unchanged: $" << account1.getBalance() << std::endl;
        }
        std::cout << std::endl;

        // Create second account for transfer test
        SavingsAccount account2("ACC-002", "USER-456", 500.0);

        std::cout << "Created second account:" << std::endl;
        std::cout << "  Account No: " << account2.getAccountNo() << std::endl;
        std::cout << "  Balance: $" << account2.getBalance() << std::endl;
        std::cout << std::endl;

        // Test transfer
        std::cout << "Testing transfer of $300 from ACC-001 to ACC-002..." << std::endl;
        if (account1.transferTo(account2, 300.0)) {
            std::cout << "  Success!" << std::endl;
            std::cout << "  ACC-001 balance: $" << account1.getBalance() << std::endl;
            std::cout << "  ACC-002 balance: $" << account2.getBalance() << std::endl;
        }
        std::cout << std::endl;

        // Test interest application
        std::cout << "Testing interest application..." << std::endl;
        account1.applyInterest(Timestamp::now());
        std::cout << std::endl;

        std::cout << "=== All tests completed ===" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}