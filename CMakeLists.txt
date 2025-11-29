cmake_minimum_required(VERSION 3.26)
project(BankingApp CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(BankingApp
        main.cpp
        Account.cpp
        Account.h
        SavingsAccount.cpp
        SavingsAccount.h
        Timestamp.cpp
        Timestamp.h
        ChequingAccount.cpp
        ChequingAccount.h
        Transaction.cpp
        Transaction.h
        DepositTransaction.cpp
        DepositTransaction.h
        WithdrawTransaction.cpp
        WithdrawTransaction.h
        TransferTransaction.cpp
        TransferTransaction.h
        AccountType.h
        AccountFactory.cpp
        AccountFactory.h
        AccountRepository.cpp
        AccountRepository.h
        BankSystem.cpp
        BankSystem.h
        BankUI.cpp
        BankUI.h
        User.cpp
        User.h
        UserRepository.cpp
        UserRepository.h
        PasswordHasher.cpp
        PasswordHasher.h
        AuthService.cpp
        AuthService.h
        DataPersistence.cpp
        DataPersistence.h
)