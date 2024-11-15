#include "TradingApp.h"

int main() {
    TradingApp app;
    std::string accountID;
    float initialBalance;

    std::cout << "Enter your account ID: ";
    std::cin >> accountID;
    std::cout << "Enter initial balance: $";
    std::cin >> initialBalance;

    app.createAccount(accountID, initialBalance);
    app.run();

    return 0;
}
