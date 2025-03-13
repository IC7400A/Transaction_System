#include <iostream>
#include <limits>
#include "../../include/cpp/account_manager.h"
#include "../../include/cpp/logger.h"
#include "../../include/cpp/database.h"

using namespace std;

extern Database db;

AccountManager accountManager;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMenu() {
    cout << "\n===== BANKING SYSTEM MENU =====" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

void displayAccountMenu(int accountId) {
    cout << "\n===== ACCOUNT MENU (ID: " << accountId << ") =====" << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Transfer Money" << endl;
    cout << "5. Logout" << endl;
    cout << "Enter your choice: ";
}

void handleAccountOperations(int accountId) {
    bool isLoggedIn = true;

    while (isLoggedIn) {
        displayAccountMenu(accountId);
        int choice;
        cin >> choice;

        if (cin.fail()) {
            cout << "❌ Invalid input! Please enter a valid option." << endl;
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                double balance = accountManager.getBalance(accountId);
                cout << "💰 Current Balance: $" << balance << endl;
                break;
            }
            case 2: {
                double amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                if (amount > 0) {
                    accountManager.updateBalance(accountId, accountManager.getBalance(accountId) + amount);
                    Logger::logTransaction(accountId, "DEPOSIT", amount);
                    cout << "✅ Deposit successful!" << endl;
                } else {
                    cout << "❌ Invalid amount!" << endl;
                }
                break;
            }
            case 3: {
                double amount;
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                double balance = accountManager.getBalance(accountId);

                if (amount > 0 && amount <= balance) {
                    accountManager.updateBalance(accountId, balance - amount);
                    Logger::logTransaction(accountId, "WITHDRAW", amount);
                    cout << "✅ Withdrawal successful!" << endl;
                } else {
                    cout << "❌ Insufficient balance or invalid amount!" << endl;
                }
                break;
            }
            case 4: {
                int recipientId;
                double amount;
                cout << "Enter recipient account number: ";
                cin >> recipientId;
                cout << "Enter transfer amount: ";
                cin >> amount;
                double senderBalance = accountManager.getBalance(accountId);

                if (amount > 0 && senderBalance >= amount && db.accountExists(recipientId)) {
                    accountManager.updateBalance(accountId, senderBalance - amount);
                    accountManager.updateBalance(recipientId, accountManager.getBalance(recipientId) + amount);
                    Logger::logTransaction(accountId, "TRANSFER", amount, recipientId);
                    cout << "✅ Transfer successful!" << endl;
                } else {
                    cout << "❌ Transfer failed! Check amount and recipient ID." << endl;
                }
                break;
            }
            case 5:
                cout << "🔒 Logging out..." << endl;
                isLoggedIn = false;
                break;
            default:
                cout << "❌ Invalid choice! Please try again." << endl;
        }
    }
}

int main() {
    db.connect();

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        if (cin.fail()) {
            cout << "❌ Invalid input! Please enter a valid option." << endl;
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                int newAccountId = accountManager.createAccount();
                if (newAccountId != -1) {
                    cout << "✅ Your new account number is: " << newAccountId << endl;
                } else {
                    cout << "❌ Account creation failed!" << endl;
                }
                break;
            }
            case 2: {
                int accountId;
                string password;
                cout << "Enter Account Number: ";
                cin >> accountId;
                cout << "Enter Password: ";
                cin >> password;

                if (accountManager.authenticate(accountId, password)) {
                    Logger::logAuth(accountId, true);
                    cout << "✅ Login successful! Welcome, Account #" << accountId << "!" << endl;
                    handleAccountOperations(accountId);
                } else {
                    Logger::logAuth(accountId, false);
                    cout << "❌ Invalid credentials! Login failed." << endl;
                }
                break;
            }
            case 3:
                cout << "👋 Exiting... Thank you for using our banking system!" << endl;
                return 0;
            default:
                cout << "❌ Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
