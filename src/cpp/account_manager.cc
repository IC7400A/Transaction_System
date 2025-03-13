#include <iostream>
#include <fstream>
#include "../../include/cpp/account_manager.h"
#include "../../include/c/utils.h"
#include "../../include/c/security.h"
#include "../../include/cpp/database.h"

using namespace std;

int AccountManager::generateAccountNumber() {
    static int accountNumber = 1000;
    return accountNumber++;
}

int AccountManager::createAccount() {
    int accountId = generateAccountNumber();
    string password, ownerName;
    double initialBalance = 0.0;

    cout << "Enter your name: ";
    cin >> ownerName;
    cout << "Enter a password for your new account: ";
    cin >> password;

    if (password.empty()) {
        cerr << "❌ Error: Password cannot be empty.\n";
        return -1;
    }

    if (password.length() < 6) {
        cerr << "❌ Error: Password must be at least 6 characters long.\n";
        return -1;
    }

    if (db.createAccount(accountId, ownerName, password, initialBalance)) {
        cout << "✅ Account created successfully! Your account number is: " << accountId << endl;
        return accountId;
    } else {
        cerr << "❌ Error: Could not create account.\n";
        return -1;
    }
}

bool AccountManager::authenticate(int accountId, const string &password) {
    if (accountId <= 0 || password.empty()) {
        cerr << "❌ Error: Invalid account ID or password.\n";
        return false;
    }
    return db.authenticateUser(accountId, password);
}

double AccountManager::getBalance(int accountId) {
    if (accountId <= 0) {
        cerr << "❌ Error: Invalid account ID.\n";
        return -1.0;
    }
    return db.getAccountBalance(accountId);
}

bool AccountManager::updateBalance(int accountId, double newBalance) {
    if (accountId <= 0 || newBalance < 0) {
        cerr << "❌ Error: Invalid account ID or negative balance.\n";
        return false;
    }
    return db.updateAccountBalance(accountId, newBalance);
}
