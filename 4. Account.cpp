#include "Account.h"
#include <iostream>
#include <iomanip>
#include <algorithm>  // For std::remove

Account::Account(std::string accountID, float initialBalance)
    : accountID(accountID), balance(initialBalance) {}

std::string Account::getAccountID() {
    return accountID;
}

float Account::getBalance() {
    return balance;
}

std::vector<std::pair<Stock, float>> Account::getHoldings() {
    return holdings;
}

void Account::deposit(float amount) {
    balance += amount;
    std::cout << "Deposited $" << std::fixed << std::setprecision(2) << amount << " to your account.\n";
}

bool Account::canBuyStock(const Stock& stock, float quantity) {
    return balance >= stock.price * quantity;  // Check if balance is sufficient for the purchase
}

bool Account::canSellStock(const Stock& stock, float quantity) {
    for (auto& holding : holdings) {
        if (holding.first == stock && holding.second >= quantity) {
            return true;  // User has enough shares to sell
        }
    }
    return false;  // No enough shares in holdings
}

void Account::buyStock(const Stock& stock, float quantity, std::string& transactionStatus) {
    if (!canBuyStock(stock, quantity)) {
        transactionStatus = "Failed";
        std::cout << "Insufficient balance to buy " << quantity << " shares of " << stock.symbol << ".\n";
        return;
    }
    balance -= stock.price * quantity;  // Deduct from balance
    holdings.push_back({stock, quantity});
    purchasePrices.push_back({stock, stock.price});  // Store the purchase price for profit/loss calculation
    transactionStatus = "Success";
    std::cout << "Bought " << quantity << " shares of " << stock.symbol << " at $" << std::fixed << std::setprecision(2) << stock.price << " per share.\n";
}

void Account::sellStock(const Stock& stock, float quantity, std::string& transactionStatus) {
    if (!canSellStock(stock, quantity)) {
        transactionStatus = "Failed";
        std::cout << "You don't have enough shares of " << stock.symbol << " to sell.\n";
        return;
    }

    float totalProfitOrLoss = 0.0f;
    // Iterate over holdings to find the matching stock and calculate profit/loss
    for (auto& holding : holdings) {
        if (holding.first == stock && holding.second >= quantity) {
            // Calculate profit/loss
            float purchasePrice = 0.0f;
            float sellPrice = stock.price;
            float soldQuantity = quantity;

            // Find the matching purchase price
            for (auto& purchase : purchasePrices) {
                if (purchase.first == stock && purchase.second != 0.0f) {
                    purchasePrice = purchase.second;
                    break;
                }
            }

            totalProfitOrLoss = (sellPrice - purchasePrice) * soldQuantity;  // Profit/Loss = (Sell Price - Purchase Price) * Quantity

            // Deduct the sold stock from holdings
            holding.second -= quantity;
            if (holding.second == 0) {
                holdings.erase(std::remove(holdings.begin(), holdings.end(), holding), holdings.end());
            }

            // Remove matching purchase price entry for the sold stock
            for (auto& purchase : purchasePrices) {
                if (purchase.first == stock && purchase.second != 0.0f) {
                    purchase.second = 0.0f;  // Mark it as sold
                    break;
                }
            }

            balance += stock.price * quantity;  // Add to balance
            transactionStatus = "Success";
            std::cout << "Sold " << quantity << " shares of " << stock.symbol << " at $" << std::fixed << std::setprecision(2) << stock.price << " per share.\n";
            break;
        }
    }

    if (totalProfitOrLoss >= 0) {
        std::cout << "You made a profit of $" << std::fixed << std::setprecision(2) << totalProfitOrLoss << " on this transaction.\n";
    } else {
        std::cout << "You made a loss of $" << std::fixed << std::setprecision(2) << -totalProfitOrLoss << " on this transaction.\n";
    }
}

float Account::calculateTotalStockWorth() {
    float totalWorth = 0.0f;
    for (const auto& holding : holdings) {
        totalWorth += holding.first.price * holding.second;  // Price * Quantity
    }
    return totalWorth;
}

void Account::displayAccountInfo() {
    // Pretty headers and spacing
    std::cout << "\n===========================================\n";
    std::cout << "             Account Information           \n";
    std::cout << "===========================================\n";
    std::cout << "Account ID: " << accountID << "\n";
    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";

    float totalStockWorth = calculateTotalStockWorth();
    std::cout << "Total Stock Worth: $" << std::fixed << std::setprecision(2) << totalStockWorth << "\n";  // Display total worth of stocks in portfolio

    std::cout << "\nStock Holdings:\n";
    std::cout << "-------------------------------------------\n";
    if (holdings.empty()) {
        std::cout << "No stocks in your portfolio.\n";
    } else {
        // Display holdings with alignment
        std::cout << std::left << std::setw(10) << "Symbol" 
                 << std::setw(15) << "Quantity"
                 << std::setw(15) << "Price/Share"
                 << std::setw(20) << "Total Worth" << "\n";
        std::cout << "-------------------------------------------\n";
        for (const auto& holding : holdings) {
            std::cout << std::left << std::setw(10) << holding.first.symbol 
                 << std::setw(15) << holding.second
                 << std::setw(15) << std::fixed << std::setprecision(2) << holding.first.price
                 << std::setw(20) << std::fixed << std::setprecision(2) << holding.first.price * holding.second << "\n";
        }
    }
    std::cout << "-------------------------------------------\n";
}
