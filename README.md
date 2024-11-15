# Stock Trading Application in C++

## Overview

This is a console-based trading application built in C++, designed to simulate a stock trading environment. The application allows users to perform basic trading operations and The application is designed to help users understand how stock trading works, while also keeping track of their profits and losses. The program stores transaction history and allows users to check the total worth of their stock holdings, ensuring that each transaction is calculated with the current stock price.

### Key Features:
- **Account Management**: Create a user account with an initial balance and view account information.
- **Stock Trading**: Buy and sell stocks by providing the stock symbol, price, and quantity.
- **Transaction History**: View details of all transactions, including deposits, stock purchases, and sales.
- **Profit/Loss Calculation**: Calculate and display profit or loss for each sale transaction based on purchase price.
- **Stock Portfolio**: View a detailed breakdown of stock holdings and their total worth.
- **Insufficient Funds Check**: Prevent buying or selling stocks if the balance or stock quantity is insufficient.

## Technologies Used
- **C++:** The core programming language for building the application.
- **Object-Oriented Programming (OOP)**: Utilized for structuring the application with classes such as Account, Stock, Transaction, etc.
- **Date Handling**: Uses system time to capture the current date and timestamp for transactions in Indian Standard Time (IST).
- **No Database**: All data (transactions, holdings, etc.) are stored in memory during the session, and no database is used for persistence.
  
## Features

1. **Create Account**: Users can create an account with an initial balance.
2. **Deposit Money**: Add funds to the account to enable buying stocks.
3. **View Account Info**: Displays current balance, total stock worth, and detailed stock holdings.
4. **Buy Stock**: Users can purchase stocks by specifying the stock symbol, price per share, and quantity.
5. **Sell Stock**: Users can sell stocks from their portfolio. The app tracks the profit or loss made based on the buying price and selling price.
6. **Transaction History**: Displays a log of all transactions with details such as type (deposit, buy, or sell), amount, status (success or failure), and date.

## Example Usage
- **Create an Account**: Enter an account ID and an initial balance.
- **Deposit Money**: Deposit funds into your account.
- **Buy Stocks**: Provide a stock symbol, price per share, and quantity.
- **Sell Stocks**: Sell stock shares and see the profit or loss.
- **View Transaction History**: See a list of all transactions, including successful and failed ones.

## Future Enhancements
- **Database Integration**: Adding database support (like MySQL or SQLite) for persistent data storage.
- **Real-Time Stock Data**: Integrating with APIs for real-time stock prices.
- **Graphical User Interface (GUI)**: Developing a GUI for a better user experience.

## description of files

- **Stock.h and Stock.cpp**: For the Stock class.
- **Account.h and Account.cpp**: For the Account class.
- **Transaction.h and Transaction.cpp**: For the Transaction class.
- **TradingApp.h and TradingApp.cpp**: For the TradingApp class and the main logic.
