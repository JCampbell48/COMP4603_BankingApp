#include <iostream>
#include <iomanip>
#include "BankSystem.h"
#include "AccountFactory.h"
#include "AccountRepository.h"
#include "AccountType.h"
#include "Timestamp.h"

int main() {
    std::cout << "=== BankSystem Facade Test ===" << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    try {
        // Create repository and factory
        AccountRepository repository;
        AccountFactory factory;

        // Create BankSystem facade
        BankSystem bank(repository, factory);
        std::cout << std::endl;

        // ===== Test 1: Create Accounts =====
        std::cout << "=== Test 1: Create Accounts ===" << std::endl;

        Account* acc1 = bank.createAccount("Alice", AccountType::Savings, 1000.0);
        Account* acc2 = bank.createAccount("Alice", AccountType::Chequing, 500.0);
        Account* acc3 = bank.createAccount("Bob", AccountType::Savings, 2000.0);

        std::cout << "Total accounts created: " << bank.getTotalAccountCount() << std::endl;
        std::cout << std::endl;

        // ===== Test 2: Display All Accounts =====
        std::cout << "=== Test 2: Display All Accounts ===" << std::endl;
        bank.displayAllAccounts();

        // ===== Test 3: Get Accounts by Owner =====
        std::cout << "=== Test 3: Get Accounts by Owner ===" << std::endl;

        std::vector<std::string> aliceAccounts = bank.getAccountsByOwner("Alice");
        std::cout << "Alice has " << aliceAccounts.size() << " account(s):" << std::endl;
        for (const auto& accountNo : aliceAccounts) {
            std::cout << "  - " << accountNo << " (" << bank.getAccountType(accountNo)
                      << ") - $" << bank.getBalance(accountNo) << std::endl;
        }
        std::cout << std::endl;

        // ===== Test 4: Deposit Operation =====
        std::cout << "=== Test 4: Deposit Operation ===" << std::endl;

        std::string aliceSavings = acc1->getAccountNo();
        std::cout << "Before deposit: $" << bank.getBalance(aliceSavings) << std::endl;
        bank.deposit(aliceSavings, 500.0);
        std::cout << std::endl;

        // ===== Test 5: Withdrawal Operation =====
        std::cout << "=== Test 5: Withdrawal Operation ===" << std::endl;

        std::string aliceChequing = acc2->getAccountNo();
        std::cout << "Before withdrawal: $" << bank.getBalance(aliceChequing) << std::endl;
        bank.withdraw(aliceChequing, 200.0);
        std::cout << std::endl;

        // ===== Test 6: Transfer Operation =====
        std::cout << "=== Test 6: Transfer Operation ===" << std::endl;

        std::cout << "Before transfer:" << std::endl;
        std::cout << "  " << aliceSavings << ": $" << bank.getBalance(aliceSavings) << std::endl;
        std::cout << "  " << aliceChequing << ": $" << bank.getBalance(aliceChequing) << std::endl;

        bank.transfer(aliceSavings, aliceChequing, 300.0);
        std::cout << std::endl;

        // ===== Test 7: Display Account Summary =====
        std::cout << "=== Test 7: Display Account Summary ===" << std::endl;
        bank.displayAccountSummary(aliceSavings);
        bank.displayAccountSummary(aliceChequing);

        // ===== Test 8: Check Account Existence =====
        std::cout << "=== Test 8: Check Account Existence ===" << std::endl;

        std::cout << "Does " << aliceSavings << " exist? "
                  << (bank.accountExists(aliceSavings) ? "Yes" : "No") << std::endl;
        std::cout << "Does SAV-999999 exist? "
                  << (bank.accountExists("SAV-999999") ? "Yes" : "No") << std::endl;
        std::cout << std::endl;

        // ===== Test 9: Get Account Information =====
        std::cout << "=== Test 9: Get Account Information ===" << std::endl;

        std::cout << "Account: " << aliceSavings << std::endl;
        std::cout << "  Type: " << bank.getAccountType(aliceSavings) << std::endl;
        std::cout << "  Owner: " << bank.getOwnerId(aliceSavings) << std::endl;
        std::cout << "  Balance: $" << bank.getBalance(aliceSavings) << std::endl;
        std::cout << std::endl;

        // ===== Test 10: Apply Interest =====
        std::cout << "=== Test 10: Apply Interest ===" << std::endl;

        std::string bobSavings = acc3->getAccountNo();
        std::cout << "Applying interest to " << bobSavings << "..." << std::endl;
        std::cout << "Before: $" << bank.getBalance(bobSavings) << std::endl;

        bank.applyInterest(bobSavings, Timestamp::now());
        std::cout << "After: $" << bank.getBalance(bobSavings) << std::endl;
        std::cout << std::endl;

        // ===== Test 11: Invalid Operations =====
        std::cout << "=== Test 11: Invalid Operations ===" << std::endl;

        std::cout << "Attempting to deposit to non-existent account..." << std::endl;
        bank.deposit("SAV-999999", 100.0);
        std::cout << std::endl;

        std::cout << "Attempting to withdraw more than available (savings, no overdraft)..." << std::endl;
        bank.withdraw(bobSavings, 10000.0);
        std::cout << std::endl;

        std::cout << "Attempting to transfer to non-existent account..." << std::endl;
        bank.transfer(bobSavings, "CHQ-999999", 100.0);
        std::cout << std::endl;

        // ===== Test 12: Delete Account =====
        std::cout << "=== Test 12: Delete Account ===" << std::endl;

        // First, try to delete account with balance
        std::cout << "Attempting to delete account with balance..." << std::endl;
        bank.deleteAccount(bobSavings);
        std::cout << std::endl;

        // Withdraw all funds first
        std::cout << "Withdrawing all funds from " << bobSavings << "..." << std::endl;
        double bobBalance = bank.getBalance(bobSavings);
        bank.withdraw(bobSavings, bobBalance);
        std::cout << std::endl;

        // Now delete
        std::cout << "Attempting to delete account with zero balance..." << std::endl;
        if (bank.deleteAccount(bobSavings)) {
            std::cout << "Total accounts after deletion: "
                      << bank.getTotalAccountCount() << std::endl;
        }
        std::cout << std::endl;

        // ===== Test 13: System-wide Statistics =====
        std::cout << "=== Test 13: System-wide Statistics ===" << std::endl;

        std::cout << "Total number of accounts: " << bank.getTotalAccountCount() << std::endl;

        // Calculate total balance across all accounts
        std::vector<Account*> allAccounts = bank.getAllAccounts();
        double totalBalance = 0.0;
        for (Account* acc : allAccounts) {
            totalBalance += acc->getBalance();
        }
        std::cout << "Total system balance: $" << totalBalance << std::endl;
        std::cout << std::endl;

        // ===== Final Summary =====
        std::cout << "=== Final Account Listing ===" << std::endl;
        bank.displayAllAccounts();

        std::cout << "=== All BankSystem tests completed successfully! ===" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}