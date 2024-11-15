#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include <string>
#include "Stock.h"

class Account {
private:
    std::string accountID;
    float balance;  // Use float for account balance
    std::vector<std::pair<Stock, float>> holdings;  // Store stock and quantity as a pair
    std::vector<std::pair<Stock, float>> purchasePrices; // Store purchase price and quantity for profit/loss calculation

public:
    Account(std::string accountID, float initialBalance);
    std::string getAccountID();
    float getBalance();
    std::vector<std::pair<Stock, float>> getHoldings();
    void deposit(float amount);
    bool canBuyStock(const Stock& stock, float quantity);
    bool canSellStock(const Stock& stock, float quantity);
    void buyStock(const Stock& stock, float quantity, std::string& transactionStatus);
    void sellStock(const Stock& stock, float quantity, std::string& transactionStatus);
    float calculateTotalStockWorth();
    void displayAccountInfo();
};

#endif // ACCOUNT_H
