#ifndef DATABASE_H
#define DATABASE_H

#include <string>

class Database {
public:
    bool connect();
    bool accountExists(int accountId);
    double getAccountBalance(int accountId);
    bool updateAccountBalance(int accountId, double newBalance);
    bool createAccount(int accountId, const std::string& ownerName, const std::string& password, double initialBalance);
    bool authenticateUser(int accountId, const std::string& password);
};

extern Database db;

#endif  // DATABASE_H
