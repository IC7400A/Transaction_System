#include <iostream>
#include "../../../include/shared_lib/cpp/shared_transaction.h"
#include "../../../include/cpp/logger.h"
#include "../../../include/cpp/database.h"

using namespace std;

bool shared_deposit(int accountId, double amount) {
    if (amount <= 0) {
        cout << "❌ Invalid deposit amount!" << endl;
        return false;
    }

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

bool shared_withdraw(int accountId, double amount) {
    if (amount <= 0) {
        cout << "❌ Invalid withdrawal amount!" << endl;
        return false;
    }

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

bool shared_transfer(int senderId, int recipientId, double amount) {
    if (amount <= 0) {
        cout << "❌ Invalid transfer amount!" << endl;
        return false;
    }

    if (!db.accountExists(recipientId)) {
        cout << "❌ Target account does not exist!" << endl;
        return false;
    }

    double senderBalance = db.getAccountBalance(senderId);
    if (amount > senderBalance) {
        cout << "❌ Insufficient funds!" << endl;
        return false;
    }

    double recipientBalance = db.getAccountBalance(recipientId);

    if (db.updateAccountBalance(senderId, senderBalance - amount) &&
        db.updateAccountBalance(recipientId, recipientBalance + amount)) {
        Logger::logTransaction(senderId, "TRANSFER", amount, recipientId);
        cout << "✅ Transfer successful! Sent $" << amount << " to Account #" << recipientId << endl;
        return true;
    } else {
        cout << "❌ Transfer failed! Database update error." << endl;
        return false;
    }
}
