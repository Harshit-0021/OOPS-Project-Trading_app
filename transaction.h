#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    enum class Type { DEPOSIT, BUY, SELL };

private:
    std::string accountID;
    Type type;
    std::string symbol;
    float amount;  // Use float for the transaction amount
    std::string date;
    std::string status;  // New member to store the status (Success or Failed)

public:
    Transaction(std::string accountID, Type type, std::string symbol, float amount, std::string date, std::string status);
    void displayTransaction() const;
};

#endif // TRANSACTION_H
