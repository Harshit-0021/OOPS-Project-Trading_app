#include "Stock.h"

Stock::Stock(std::string symbol, float price) : symbol(symbol), price(price) {}

bool Stock::operator==(const Stock& other) const {
    return symbol == other.symbol;
}
