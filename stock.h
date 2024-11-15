#ifndef STOCK_H
#define STOCK_H

#include <string>

class Stock {
public:
    std::string symbol;
    float price;  // Use float for stock price

    Stock(std::string symbol, float price);
    bool operator==(const Stock& other) const;
};

#endif // STOCK_H
