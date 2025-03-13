#include <iostream>
#include "../../include/cpp/user_auth.h"
#include "../../include/cpp/database.h"
#include "../../include/cpp/logger.h"

using namespace std;

Database db;

UserAuth::UserAuth() {}

bool UserAuth::login(int accountId, const string &password) {
    if (db.authenticateUser(accountId, password)) {
        Logger::logAuth(accountId, true);
        cout << "✅ Login successful! Welcome, Account #" << accountId << "!" << endl;
        return true;
    } else {
        Logger::logAuth(accountId, false);
        cout << "❌ Invalid credentials! Login failed." << endl;
        return false;
    }
}

int UserAuth::createAccount(const string &ownerName, const string &password, double initialBalance) {
    int accountId = generateAccountNumber();

    if (db.createAccount(accountId, ownerName, password, initialBalance)) {
        cout << "✅ Account successfully created! Your new account number is: " << accountId << endl;
        return accountId;
    } else {
        cout << "❌ Account creation failed!" << endl;
        return -1;
    }
}

int UserAuth::generateAccountNumber() {
    srand(time(0));
    int accountId;
    do {
        accountId = 100 + (rand() % 900);
    } while (db.accountExists(accountId));
    return accountId;
}
