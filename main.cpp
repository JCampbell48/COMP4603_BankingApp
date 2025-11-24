#include <iostream>
#include <iomanip>
#include "AccountFactory.h"
#include "AccountRepository.h"
#include "AccountType.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "ChequingAccount.h"
#include "Timestamp.h"

int main() {
    std::cout << "=== AccountFactory and AccountRepository Test ===" << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    try {
        // Create factory and repository
        AccountFactory factory;
        AccountRepository repository;

        // ===== Test 1: AccountFactory - Create different account types =====
        std::cout << "=== Test 1: AccountFactory - Create Accounts ===" << std::endl;

        Account* savings1 = factory.create(AccountType::Savings, "USER-001", 1000.0);
        std::cout << "Created: " << savings1->getAccountType() << " account "
                  << savings1->getAccountNo() << " for " << savings1->getOwnerId()
                  << " with balance $" << savings1->getBalance() << std::endl;

        Account* chequing1 = factory.create(AccountType::Chequing, "USER-001", 500.0);
        std::cout << "Created: " << chequing1->getAccountType() << " account "
                  << chequing1->getAccountNo() << " for " << chequing1->getOwnerId()
                  << " with balance $" << chequing1->getBalance() << std::endl;

        Account* savings2 = factory.create(AccountType::Savings, "USER-002", 2000.0);
        std::cout << "Created: " << savings2->getAccountType() << " account "
                  << savings2->getAccountNo() << " for " << savings2->getOwnerId()
                  << " with balance $" << savings2->getBalance() << std::endl;

        std::cout << std::endl;

        // ===== Test 2: AccountRepository - Save accounts =====
        std::cout << "=== Test 2: AccountRepository - Save Accounts ===" << std::endl;

        repository.save(savings1);
        repository.save(chequing1);
        repository.save(savings2);

        std::cout << "Total accounts in repository: " << repository.getAccountCount() << std::endl;
        std::cout << std::endl;

        // ===== Test 3: Retrieve account by account number =====
        std::cout << "=== Test 3: Retrieve Account by Number ===" << std::endl;

        std::string lookupAccountNo = savings1->getAccountNo();
        auto optAccount = repository.getByAccountNo(lookupAccountNo);

        if (optAccount.has_value()) {
            Account* acc = optAccount.value();
            std::cout << "Found account: " << acc->getAccountNo() << std::endl;
            std::cout << "  Type: " << acc->getAccountType() << std::endl;
            std::cout << "  Owner: " << acc->getOwnerId() << std::endl;
            std::cout << "  Balance: $" << acc->getBalance() << std::endl;
        } else {
            std::cout << "Account not found!" << std::endl;
        }
        std::cout << std::endl;

        // ===== Test 4: Find accounts by owner ID =====
        std::cout << "=== Test 4: Find Accounts by Owner ID ===" << std::endl;

        std::vector<std::string> user001Accounts = repository.findByOwnerId("USER-001");
        std::cout << "Accounts owned by USER-001: " << user001Accounts.size() << std::endl;
        for (const auto& accountNo : user001Accounts) {
            auto acc = repository.getByAccountNo(accountNo);
            if (acc.has_value()) {
                std::cout << "  - " << accountNo << " ("
                          << acc.value()->getAccountType() << ") - $"
                          << acc.value()->getBalance() << std::endl;
            }
        }
        std::cout << std::endl;

        // ===== Test 5: Check account existence =====
        std::cout << "=== Test 5: Check Account Existence ===" << std::endl;

        std::cout << "Does " << savings1->getAccountNo() << " exist? "
                  << (repository.existsAccountNo(savings1->getAccountNo()) ? "Yes" : "No")
                  << std::endl;
        std::cout << "Does ACC-999999 exist? "
                  << (repository.existsAccountNo("ACC-999999") ? "Yes" : "No")
                  << std::endl;
        std::cout << std::endl;

        // ===== Test 6: Get account balance =====
        std::cout << "=== Test 6: Get Account Balance ===" << std::endl;

        double balance = repository.getBalance(savings1->getAccountNo());
        std::cout << "Balance of " << savings1->getAccountNo() << ": $" << balance << std::endl;
        std::cout << std::endl;

        // ===== Test 7: Get overdraft limit =====
        std::cout << "=== Test 7: Get Overdraft Limit ===" << std::endl;

        double overdraft = repository.getOverdraftLimit(chequing1->getAccountNo());
        std::cout << "Overdraft limit of " << chequing1->getAccountNo()
                  << ": $" << overdraft << std::endl;

        double savingsOverdraft = repository.getOverdraftLimit(savings1->getAccountNo());
        std::cout << "Overdraft limit of " << savings1->getAccountNo()
                  << ": $" << savingsOverdraft << " (savings have no overdraft)" << std::endl;
        std::cout << std::endl;

        // ===== Test 8: Get all accounts =====
        std::cout << "=== Test 8: Get All Accounts ===" << std::endl;

        std::vector<Account*> allAccounts = repository.getAllAccounts();
        std::cout << "All accounts in repository:" << std::endl;
        for (Account* acc : allAccounts) {
            std::cout << "  " << acc->getAccountNo() << " - "
                      << acc->getAccountType() << " - Owner: "
                      << acc->getOwnerId() << " - Balance: $"
                      << acc->getBalance() << std::endl;
        }
        std::cout << std::endl;

        // ===== Test 9: Remove account =====
        std::cout << "=== Test 9: Remove Account ===" << std::endl;

        std::string accountToRemove = savings2->getAccountNo();
        std::cout << "Accounts before removal: " << repository.getAccountCount() << std::endl;

        bool removed = repository.remove(accountToRemove);
        std::cout << "Removal " << (removed ? "successful" : "failed") << std::endl;
        std::cout << "Accounts after removal: " << repository.getAccountCount() << std::endl;
        std::cout << std::endl;

        // ===== Test 10: Create account with default balance =====
        std::cout << "=== Test 10: Create Account with Default Balance ===" << std::endl;

        Account* defaultAccount = factory.create(AccountType::Savings, "USER-003");
        std::cout << "Created account with default balance: "
                  << defaultAccount->getAccountNo()
                  << " - Balance: $" << defaultAccount->getBalance() << std::endl;
        repository.save(defaultAccount);
        std::cout << std::endl;

        // ===== Test 11: AccountType to String conversion =====
        std::cout << "=== Test 11: AccountType to String ===" << std::endl;

        std::cout << "AccountType::Savings = "
                  << AccountFactory::accountTypeToString(AccountType::Savings) << std::endl;
        std::cout << "AccountType::Chequing = "
                  << AccountFactory::accountTypeToString(AccountType::Chequing) << std::endl;
        std::cout << "AccountType::TFSA = "
                  << AccountFactory::accountTypeToString(AccountType::TFSA) << std::endl;
        std::cout << std::endl;

        // ===== Test 12: Account number generation sequence =====
        std::cout << "=== Test 12: Account Number Generation Sequence ===" << std::endl;

        std::cout << "Creating 3 savings accounts to test sequential numbering:" << std::endl;
        Account* seq1 = factory.create(AccountType::Savings, "USER-004", 100.0);
        Account* seq2 = factory.create(AccountType::Savings, "USER-004", 200.0);
        Account* seq3 = factory.create(AccountType::Savings, "USER-004", 300.0);

        std::cout << "  1. " << seq1->getAccountNo() << std::endl;
        std::cout << "  2. " << seq2->getAccountNo() << std::endl;
        std::cout << "  3. " << seq3->getAccountNo() << std::endl;
        std::cout << "Note: Numbers are sequential!" << std::endl;

        repository.save(seq1);
        repository.save(seq2);
        repository.save(seq3);
        std::cout << std::endl;

        // ===== Final Summary =====
        std::cout << "=== Final Summary ===" << std::endl;
        std::cout << "Total accounts in repository: " << repository.getAccountCount() << std::endl;
        std::cout << std::endl;

        std::cout << "=== All tests completed successfully! ===" << std::endl;

        // Repository destructor will automatically clean up all accounts

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}