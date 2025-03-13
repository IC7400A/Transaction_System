#include "../../include/cpp/database.h"
#include <fstream>
#include <iostream>

using namespace std;

#define USER_DB "data/users.db"
#define ACCOUNT_DB "data/accounts.db"

Database db;

bool Database::connect() {
    ofstream userFile(USER_DB, ios::app);  
    ofstream accountFile(ACCOUNT_DB, ios::app); 
    if (!userFile.is_open()) {
        cerr << "❌ Error: Could not open user database file!" << endl;
        return false;
    }
    if (!accountFile.is_open()) {
        cerr << "❌ Error: Could not open account database file!" << endl;
        return false;
    }
    userFile.close();
    accountFile.close();
    return true;
}

bool Database::accountExists(int accountId) {
    ifstream file(ACCOUNT_DB);
    if (!file.is_open()) {
        cerr << "❌ Error: Could not open account database file!" << endl;
        return false;
    }
    int storedId;
    double balance;

    while (file >> storedId >> balance) {
        if (storedId == accountId) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

double Database::getAccountBalance(int accountId) {
    ifstream file(ACCOUNT_DB);
    if (!file.is_open()) {
        cerr << "❌ Error: Could not open account database file!" << endl;
        return -1;
    }
    int storedId;
    double balance;

    while (file >> storedId >> balance) {
        if (storedId == accountId) {
            file.close();
            return balance;
        }
    }
    file.close();
    return -1;
}

bool Database::updateAccountBalance(int accountId, double newBalance) {
    ifstream file(ACCOUNT_DB);
    ofstream tempFile("data/temp.db");
    if (!file.is_open() || !tempFile.is_open()) {
        cerr << "❌ Error: Could not open account database files!" << endl;
        return false;
    }

    int storedId;
    double balance;
    bool updated = false;

    while (file >> storedId >> balance) {
        if (storedId == accountId) {
            tempFile << storedId << " " << newBalance << endl;
            updated = true;
        } else {
            tempFile << storedId << " " << balance << endl;
        }
    }

    file.close();
    tempFile.close();
    if (updated) {
        remove(ACCOUNT_DB);
        rename("data/temp.db", ACCOUNT_DB);
    } else {
        remove("data/temp.db");
    }
    return updated;
}

bool Database::createAccount(int accountId, const string& ownerName, const string& password, double initialBalance) {
    if (accountExists(accountId)) return false;

    ofstream userFile(USER_DB, ios::app);
    ofstream accountFile(ACCOUNT_DB, ios::app);
    if (!userFile.is_open() || !accountFile.is_open()) {
        cerr << "❌ Error: Could not open database files for creating account!" << endl;
        return false;
    }

    userFile << accountId << " " << ownerName << " " << password << endl;
    accountFile << accountId << " " << initialBalance << endl;

    userFile.close();
    accountFile.close();
    return true;
}

bool Database::authenticateUser(int accountId, const string& password) {
    ifstream file(USER_DB);
    if (!file.is_open()) {
        cerr << "❌ Error: Could not open user database file!" << endl;
        return false;
    }
    int storedId;
    string storedOwnerName, storedPassword;

    while (file >> storedId >> storedOwnerName >> storedPassword) {
        if (storedId == accountId && storedPassword == password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
