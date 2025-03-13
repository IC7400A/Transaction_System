#include "../../include/cpp/transaction.h"
#include "../../include/cpp/database.h"
#include "../../include/cpp/logger.h"

#include <iostream>

using namespace std;

Transaction::Transaction(int accountId) {
    this->accountId = accountId;
}

bool Transaction::deposit(double amount) {
    if (amount <= 0) {
        cout << "❌ Invalid deposit amount!" << endl;
        return false;
    }

    Database db;
    double currentBalance = db.getAccountBalance(accountId);
    double newBalance = currentBalance + amount;

    if (db.updateAccountBalance(accountId, newBalance)) {
        Logger::logTransaction(accountId, "DEPOSIT", amount);
        cout << "✅ Deposit successful! New balance: $" << newBalance << endl;
        return true;
    } else {
        cout << "❌ Error updating balance!" << endl;
        return false;
    }
}

bool Transaction::withdraw(double amount) {
    if (amount <= 0) {
        cout << "❌ Invalid withdrawal amount!" << endl;
        return false;
    }

    Database db;
    double currentBalance = db.getAccountBalance(accountId);
    if (amount > currentBalance) {
        cout << "❌ Insufficient funds!" << endl;
        return false;
    }

    double newBalance = currentBalance - amount;
    if (db.updateAccountBalance(accountId, newBalance)) {
        Logger::logTransaction(accountId, "WITHDRAW", amount);
        cout << "✅ Withdrawal successful! New balance: $" << newBalance << endl;
        return true;
    } else {
        cout << "❌ Error updating balance!" << endl;
        return false;
    }
}

bool Transaction::transfer(int recipientId, double amount) {
    if (amount <= 0) {
        cout << "❌ Invalid transfer amount!" << endl;
        return false;
    }

    Database db;
    if (!db.accountExists(recipientId)) {
        cout << "❌ Target account does not exist!" << endl;
        return false;
    }

    double senderBalance = db.getAccountBalance(accountId);
    if (amount > senderBalance) {
        cout << "❌ Insufficient funds!" << endl;
        return false;
    }

    double recipientBalance = db.getAccountBalance(recipientId);

    if (db.updateAccountBalance(accountId, senderBalance - amount) &&
        db.updateAccountBalance(recipientId, recipientBalance + amount)) {
        Logger::logTransaction(accountId, "TRANSFER", amount, recipientId);
        cout << "✅ Transfer successful! Sent $" << amount << " to Account #" << recipientId << endl;
        return true;
    } else {
        cout << "❌ Transfer failed! Database update error." << endl;
        return false;
    }
}
