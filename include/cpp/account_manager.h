#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include <string>
#include "database.h"

class AccountManager {
public:
    int createAccount();
    bool authenticate(int accountId, const std::string& password);
    double getBalance(int accountId);
    bool updateBalance(int accountId, double newBalance);

private:
    int generateAccountNumber();
};

#endif // ACCOUNT_MANAGER_H
