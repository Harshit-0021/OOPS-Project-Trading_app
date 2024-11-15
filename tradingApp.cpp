#include "TradingApp.h"
#include <iostream>
#include <ctime>

TradingApp::TradingApp() : currentAccount(nullptr) {}

void TradingApp::createAccount(const std::string& accountID, float initialBalance) {
    currentAccount = new Account(accountID, initialBalance);
    std::cout << "===========================================\n";
    std::cout << "Account created successfully for " << accountID << " with initial balance: $" << std::fixed << std::setprecision(2) << initialBalance << "\n";
    std::cout << "===========================================\n";
}

void TradingApp::logTransaction(const Transaction& transaction) {
    transactionHistory.push_back(transaction);
}

std::string TradingApp::getCurrentDate() {
    time_t t = time(0);
    struct tm* now = gmtime(&t);
    now->tm_hour += 5;  // Adjust for IST
    now->tm_min += 30;

    if (now->tm_min >= 60) {
        now->tm_min -= 60;
        now->tm_hour++;
    }
    if (now->tm_hour >= 24) {
        now->tm_hour -= 24;
        now->tm_mday++;
    }

    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", now);
    return std::string(buf);
}

void TradingApp::run() {
    bool exit = false;
    while (!exit) {
        int choice;
        std::cout << "\n===========================================\n";
        std::cout << "             Trading App Menu             \n";
        std::cout << "===========================================\n";
        std::cout << "1. View Account Info\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Buy Stock\n";
        std::cout << "4. Sell Stock\n";
        std::cout << "5. View Transaction History\n";
        std::cout << "6. Exit\n";
        std::cout << "===========================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                currentAccount->displayAccountInfo();
                break;
            case 2: {
                float amount;
                std::cout << "Enter deposit amount: $";
                std::cin >> amount;
                currentAccount->deposit(amount);
                logTransaction(Transaction(currentAccount->getAccountID(), Transaction::Type::DEPOSIT, "", amount, getCurrentDate(), "Success"));
                break;
            }
            case 3: {
                std::string symbol;
                float price;
                float quantity;
                std::cout << "Enter stock symbol: ";
                std::cin >> symbol;
                std::cout << "Enter stock price: $";
                std::cin >> price;
                std::cout << "Enter quantity (can be fractional): ";
                std::cin >> quantity;
                Stock stock(symbol, price);

                std::string transactionStatus;
                currentAccount->buyStock(stock, quantity, transactionStatus);
                logTransaction(Transaction(currentAccount->getAccountID(), Transaction::Type::BUY, symbol, price * quantity, getCurrentDate(), transactionStatus));
                break;
            }
            case 4: {
                std::string symbol;
                float price;
                float quantity;
                std::cout << "Enter stock symbol: ";
                std::cin >> symbol;
                std::cout << "Enter stock price: $";
                std::cin >> price;
                std::cout << "Enter quantity (can be fractional): ";
                std::cin >> quantity;
                Stock stock(symbol, price);

                std::string transactionStatus;
                currentAccount->sellStock(stock, quantity, transactionStatus);
                logTransaction(Transaction(currentAccount->getAccountID(), Transaction::Type::SELL, symbol, price * quantity, getCurrentDate(), transactionStatus));
                break;
            }
            case 5:
                std::cout << "\nTransaction History:\n";
                for (const auto& transaction : transactionHistory) {
                    transaction.displayTransaction();
                }
                break;
            case 6:
                exit = true;
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    }
}
