#ifndef TRADINGAPP_H
#define TRADINGAPP_H

#include <vector>
#include "Account.h"
#include "Transaction.h"

class TradingApp {
private:
    Account* currentAccount;
    std::vector<Transaction> transactionHistory;

public:
    TradingApp();
    void createAccount(const std::string& accountID, float initialBalance);
    void logTransaction(const Transaction& transaction);
    std::string getCurrentDate();
    void run();
};

#endif // TRADINGAPP_H
