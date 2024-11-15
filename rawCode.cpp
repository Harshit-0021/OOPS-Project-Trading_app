#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>  // For std::remove

using namespace std;

// Stock class to represent stock information
class Stock {
public:
    string symbol;
    float price;  // Use float for stock price

    Stock(string symbol, float price) : symbol(symbol), price(price) {}

    bool operator==(const Stock& other) const {
        return symbol == other.symbol;
    }
};

// Account class for managing the user's account balance and stock holdings
class Account {
private:
    string accountID;
    float balance;  // Use float for account balance
    vector<pair<Stock, float>> holdings;  // Store stock and quantity as a pair
    vector<pair<Stock, float>> purchasePrices; // Store purchase price and quantity for profit/loss calculation

public:
    Account(string accountID, float initialBalance)
        : accountID(accountID), balance(initialBalance) {}

    string getAccountID() {
        return accountID;
    }

    float getBalance() {
        return balance;
    }

    vector<pair<Stock, float>> getHoldings() {
        return holdings;
    }

    void deposit(float amount) {
        balance += amount;
        cout << "Deposited $" << fixed << setprecision(2) << amount << " to your account.\n";
    }

    bool canBuyStock(const Stock& stock, float quantity) {
        return balance >= stock.price * quantity;  // Check if balance is sufficient for the purchase
    }

    bool canSellStock(const Stock& stock, float quantity) {
        for (auto& holding : holdings) {
            if (holding.first == stock && holding.second >= quantity) {
                return true;  // User has enough shares to sell
            }
        }
        return false;  // No enough shares in holdings
    }

    void buyStock(const Stock& stock, float quantity, string& transactionStatus) {
        if (!canBuyStock(stock, quantity)) {
            transactionStatus = "Failed";
            cout << "Insufficient balance to buy " << quantity << " shares of " << stock.symbol << ".\n";
            return;
        }
        balance -= stock.price * quantity;  // Deduct from balance
        holdings.push_back({stock, quantity});
        purchasePrices.push_back({stock, stock.price});  // Store the purchase price for profit/loss calculation
        transactionStatus = "Success";
        cout << "Bought " << quantity << " shares of " << stock.symbol << " at $" << fixed << setprecision(2) << stock.price << " per share.\n";
    }

    void sellStock(const Stock& stock, float quantity, string& transactionStatus) {
        if (!canSellStock(stock, quantity)) {
            transactionStatus = "Failed";
            cout << "You don't have enough shares of " << stock.symbol << " to sell.\n";
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
                    holdings.erase(remove(holdings.begin(), holdings.end(), holding), holdings.end());
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
                cout << "Sold " << quantity << " shares of " << stock.symbol << " at $" << fixed << setprecision(2) << stock.price << " per share.\n";
                break;
            }
        }

        if (totalProfitOrLoss >= 0) {
            cout << "You made a profit of $" << fixed << setprecision(2) << totalProfitOrLoss << " on this transaction.\n";
        } else {
            cout << "You made a loss of $" << fixed << setprecision(2) << -totalProfitOrLoss << " on this transaction.\n";
        }
    }

    float calculateTotalStockWorth() {
        float totalWorth = 0.0f;
        for (const auto& holding : holdings) {
            totalWorth += holding.first.price * holding.second;  // Price * Quantity
        }
        return totalWorth;
    }

    void displayAccountInfo() {
        // Pretty headers and spacing
        cout << "\n===========================================\n";
        cout << "             Account Information           \n";
        cout << "===========================================\n";
        cout << "Account ID: " << accountID << "\n";
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << "\n";

        float totalStockWorth = calculateTotalStockWorth();
        cout << "Total Stock Worth: $" << fixed << setprecision(2) << totalStockWorth << "\n";  // Display total worth of stocks in portfolio

        cout << "\nStock Holdings:\n";
        cout << "-------------------------------------------\n";
        if (holdings.empty()) {
            cout << "No stocks in your portfolio.\n";
        } else {
            // Display holdings with alignment
            cout << left << setw(10) << "Symbol" 
                 << setw(15) << "Quantity"
                 << setw(15) << "Price/Share"
                 << setw(20) << "Total Worth" << "\n";
            cout << "-------------------------------------------\n";
            for (const auto& holding : holdings) {
                cout << left << setw(10) << holding.first.symbol 
                     << setw(15) << holding.second
                     << setw(15) << fixed << setprecision(2) << holding.first.price
                     << setw(20) << fixed << setprecision(2) << holding.first.price * holding.second << "\n";
            }
        }
        cout << "-------------------------------------------\n";
    }
};

// Transaction class to log all transactions
class Transaction {
public:
    enum class Type { DEPOSIT, BUY, SELL };

private:
    string accountID;
    Type type;
    string symbol;
    float amount;  // Use float for the transaction amount
    string date;
    string status;  // New member to store the status (Success or Failed)

public:
    Transaction(string accountID, Type type, string symbol, float amount, string date, string status)
        : accountID(accountID), type(type), symbol(symbol), amount(amount), date(date), status(status) {}

    void displayTransaction() const {
        cout << "--------------------------------------------------\n";
        cout << left << setw(20) << "Transaction Type" 
             << setw(20) << "Account ID" 
             << setw(15) << "Symbol" 
             << setw(15) << "Amount"
             << setw(10) << "Status"
             << "Date\n";
        cout << "--------------------------------------------------\n";
        cout << left << setw(20) << (type == Type::DEPOSIT ? "Deposit" : (type == Type::BUY ? "Buy" : "Sell"))
             << setw(20) << accountID 
             << setw(15) << symbol
             << "$" << setw(14) << fixed << setprecision(2) << amount
             << setw(10) << status
             << date << "\n";
        cout << "--------------------------------------------------\n";
    }
};

// Main trading application class to handle user interaction
class TradingApp {
private:
    Account* currentAccount;
    vector<Transaction> transactionHistory;

public:
    TradingApp() : currentAccount(nullptr) {}

    // Create account
    void createAccount(const string& accountID, float initialBalance) {
        currentAccount = new Account(accountID, initialBalance);
        cout << "===========================================\n";
        cout << "Account created successfully for " << accountID << " with initial balance: $" << fixed << setprecision(2) << initialBalance << "\n";
        cout << "===========================================\n";
    }

    // Log transaction
    void logTransaction(const Transaction& transaction) {
        transactionHistory.push_back(transaction);
    }

    // Get current date in IST (Indian Standard Time)
    string getCurrentDate() {
        // Get current time in UTC
        time_t t = time(0);
        struct tm* now = gmtime(&t);  // Get UTC time

        // Adjust for IST (UTC + 5:30)
        now->tm_hour += 5;  // Add 5 hours
        now->tm_min += 30;   // Add 30 minutes

        // Handle overflow if minutes exceed 60 or hours exceed 24
        if (now->tm_min >= 60) {
            now->tm_min -= 60;
            now->tm_hour++;
        }
        if (now->tm_hour >= 24) {
            now->tm_hour -= 24;
            now->tm_mday++;
        }

        // Format the date into a readable string
        char buf[80];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", now);
        return string(buf);
    }

    // Run the application
    void run() {
        bool exit = false;
        while (!exit) {
            int choice;
            cout << "\n===========================================\n";
            cout << "             Trading App Menu             \n";
            cout << "===========================================\n";
            cout << "1. View Account Info\n";
            cout << "2. Deposit Money\n";
            cout << "3. Buy Stock\n";
            cout << "4. Sell Stock\n";
            cout << "5. View Transaction History\n";
            cout << "6. Exit\n";
            cout << "===========================================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    currentAccount->displayAccountInfo();
                    break;
                case 2: {
                    float amount;
                    cout << "Enter deposit amount: $";
                    cin >> amount;
                    currentAccount->deposit(amount);
                    logTransaction(Transaction(currentAccount->getAccountID(), Transaction::Type::DEPOSIT, "", amount, getCurrentDate(), "Success"));
                    break;
                }
                case 3: {
                    string symbol;
                    float price;
                    float quantity;
                    cout << "Enter stock symbol: ";
                    cin >> symbol;
                    cout << "Enter stock price: $";
                    cin >> price;
                    cout << "Enter quantity (can be fractional): ";
                    cin >> quantity;
                    Stock stock(symbol, price);

                    string transactionStatus;
                    currentAccount->buyStock(stock, quantity, transactionStatus);
                    logTransaction(Transaction(currentAccount->getAccountID(), Transaction::Type::BUY, symbol, price * quantity, getCurrentDate(), transactionStatus));
                    break;
                }
                case 4: {
                    string symbol;
                    float price;
                    float quantity;
                    cout << "Enter stock symbol: ";
                    cin >> symbol;
                    cout << "Enter stock price: $";
                    cin >> price;
                    cout << "Enter quantity (can be fractional): ";
                    cin >> quantity;
                    Stock stock(symbol, price);

                    string transactionStatus;
                    currentAccount->sellStock(stock, quantity, transactionStatus);
                    logTransaction(Transaction(currentAccount->getAccountID(), Transaction::Type::SELL, symbol, price * quantity, getCurrentDate(), transactionStatus));
                    break;
                }
                case 5:
                    cout << "\nTransaction History:\n";
                    for (const auto& transaction : transactionHistory) {
                        transaction.displayTransaction();
                    }
                    break;
                case 6:
                    exit = true;
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                    break;
            }
        }
    }
};

// Main function to start the application
int main() {
    TradingApp app;
    string accountID;
    float initialBalance;

    cout << "Enter your account ID: ";
    cin >> accountID;
    cout << "Enter initial balance: $";
    cin >> initialBalance;

    app.createAccount(accountID, initialBalance);
    app.run();

    return 0;
}
