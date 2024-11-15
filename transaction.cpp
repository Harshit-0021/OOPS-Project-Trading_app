#include "Transaction.h"
#include <iostream>
#include <iomanip>

Transaction::Transaction(std::string accountID, Type type, std::string symbol, float amount, std::string date, std::string status)
    : accountID(accountID), type(type), symbol(symbol), amount(amount), date(date), status(status) {}

void Transaction::displayTransaction() const {
    std::cout << "--------------------------------------------------\n";
    std::cout << std::left << std::setw(20) << "Transaction Type" 
         << std::setw(20) << "Account ID" 
         << std::setw(15) << "Symbol" 
         << std::setw(15) << "Amount"
         << std::setw(10) << "Status"
         << "Date\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << std::left << std::setw(20) << (type == Type::DEPOSIT ? "Deposit" : (type == Type::BUY ? "Buy" : "Sell"))
         << std::setw(20) << accountID 
         << std::setw(15) << symbol
         << "$" << std::setw(14) << std::fixed << std::setprecision(2) << amount
         << std::setw(10) << status
         << date << "\n";
    std::cout << "--------------------------------------------------\n";
}
