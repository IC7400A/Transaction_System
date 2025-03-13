#include "../../include/cpp/account.h"
#include "../../include/cpp/logger.h"

#include <iostream>

using namespace std;

Account::Account(int id, double initialBalance) {
    this->accountId = id;
    this->balance = initialBalance;
}

int Account::getAccountId() const {
    return accountId;
}

double Account::getBalance() const {
    return balance;
}

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        Logger::logTransaction(accountId, "DEPOSIT", amount);
        cout << "✅ Deposit successful! New balance: $" << balance << endl;
    } else {
        cout << "❌ Error: Deposit amount must be positive!\n";
    }
}

bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        Logger::logTransaction(accountId, "WITHDRAW", amount);
        cout << "✅ Withdrawal successful! New balance: $" << balance << endl;
        return true;
    } else {
        cout << "❌ Error: Insufficient balance or invalid amount!\n";
        return false;
    }
}

bool Account::transfer(Account &recipient, double amount) {
    if (withdraw(amount)) {
        recipient.deposit(amount);
        Logger::logTransaction(accountId, "TRANSFER", amount, recipient.getAccountId());
        cout << "✅ Transfer successful! Sent $" << amount << " to Account #" << recipient.getAccountId() << endl;
        return true;
    }
    return false;
}
