#include <iostream>
#include <iomanip>
#include <vector>
#include "Account.h"
#include "SavingsAccount.h"
#include "ChequingAccount.h"
#include "Transaction.h"
#include "DepositTransaction.h"
#include "WithdrawTransaction.h"
#include "TransferTransaction.h"
#include "Timestamp.h"

int main() {
    std::cout << "=== Transaction System Test ===" << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    try {
        // Create some accounts
        SavingsAccount savings("SAV-001", "USER-123", 1000.0, 0.05);
        ChequingAccount chequing("CHQ-001", "USER-123", 500.0, 200.0);

        std::cout << "Initial Account Balances:" << std::endl;
        std::cout << "  Savings:  $" << savings.getBalance() << std::endl;
        std::cout << "  Chequing: $" << chequing.getBalance() << std::endl;
        std::cout << std::endl;

        // Store executed transactions for undo demo
        std::vector<Transaction*> transactions;

        // Test 1: Deposit Transaction
        std::cout << "=== Test 1: Deposit Transaction ===" << std::endl;
        DepositTransaction* deposit = new DepositTransaction(
            savings, 500.0, Timestamp::now(), "Paycheck deposit"
        );

        std::cout << "Executing deposit of $500..." << std::endl;
        if (deposit->execute()) {
            std::cout << "New savings balance: $" << savings.getBalance() << std::endl;
            transactions.push_back(deposit);
        }
        std::cout << std::endl;

        // Test 2: Withdrawal Transaction
        std::cout << "=== Test 2: Withdrawal Transaction ===" << std::endl;
        WithdrawTransaction* withdrawal = new WithdrawTransaction(
            chequing, 200.0, Timestamp::now(), "ATM withdrawal"
        );

        std::cout << "Executing withdrawal of $200..." << std::endl;
        if (withdrawal->execute()) {
            std::cout << "New chequing balance: $" << chequing.getBalance() << std::endl;
            transactions.push_back(withdrawal);
        }
        std::cout << std::endl;

        // Test 3: Transfer Transaction
        std::cout << "=== Test 3: Transfer Transaction ===" << std::endl;
        TransferTransaction* transfer = new TransferTransaction(
            savings, chequing, 300.0, Timestamp::now(),
            "Transfer to chequing for bills"
        );

        std::cout << "Executing transfer of $300 from savings to chequing..." << std::endl;
        if (transfer->execute()) {
            std::cout << "New savings balance:  $" << savings.getBalance() << std::endl;
            std::cout << "New chequing balance: $" << chequing.getBalance() << std::endl;
            transactions.push_back(transfer);
        }
        std::cout << std::endl;

        // Test 4: Display Transaction Records
        std::cout << "=== Test 4: Transaction Records ===" << std::endl;
        for (size_t i = 0; i < transactions.size(); ++i) {
            std::cout << "\nTransaction " << (i + 1) << ":" << std::endl;
            std::cout << transactions[i]->record() << std::endl;
        }
        std::cout << std::endl;

        // Test 5: Undo Transactions
        std::cout << "=== Test 5: Undo Transactions ===" << std::endl;
        std::cout << "\nCurrent balances:" << std::endl;
        std::cout << "  Savings:  $" << savings.getBalance() << std::endl;
        std::cout << "  Chequing: $" << chequing.getBalance() << std::endl;
        std::cout << std::endl;

        std::cout << "Undoing last transaction (transfer)..." << std::endl;
        if (transfer->undo()) {
            std::cout << "After undo:" << std::endl;
            std::cout << "  Savings:  $" << savings.getBalance() << std::endl;
            std::cout << "  Chequing: $" << chequing.getBalance() << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Undoing withdrawal..." << std::endl;
        if (withdrawal->undo()) {
            std::cout << "After undo:" << std::endl;
            std::cout << "  Chequing: $" << chequing.getBalance() << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Undoing deposit..." << std::endl;
        if (deposit->undo()) {
            std::cout << "After undo:" << std::endl;
            std::cout << "  Savings: $" << savings.getBalance() << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Final balances (should match initial):" << std::endl;
        std::cout << "  Savings:  $" << savings.getBalance() << std::endl;
        std::cout << "  Chequing: $" << chequing.getBalance() << std::endl;
        std::cout << std::endl;

        // Test 6: Failed Transaction
        std::cout << "=== Test 6: Failed Transaction ===" << std::endl;
        WithdrawTransaction* failedWithdraw = new WithdrawTransaction(
            savings, 5000.0, Timestamp::now(), "Attempt large withdrawal"
        );

        std::cout << "Attempting to withdraw $5000 (should fail)..." << std::endl;
        if (!failedWithdraw->execute()) {
            std::cout << "Transaction correctly failed!" << std::endl;
        }
        std::cout << std::endl;

        // Test 7: Double Execute Prevention
        std::cout << "=== Test 7: Double Execute Prevention ===" << std::endl;
        DepositTransaction* deposit2 = new DepositTransaction(
            savings, 100.0, Timestamp::now(), "Test deposit"
        );

        std::cout << "First execute..." << std::endl;
        deposit2->execute();
        std::cout << "Balance: $" << savings.getBalance() << std::endl;

        std::cout << "Attempting second execute (should fail)..." << std::endl;
        deposit2->execute();
        std::cout << "Balance unchanged: $" << savings.getBalance() << std::endl;
        std::cout << std::endl;

        // Cleanup
        for (Transaction* t : transactions) {
            delete t;
        }
        delete failedWithdraw;
        delete deposit2;

        std::cout << "=== All tests completed ===" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}