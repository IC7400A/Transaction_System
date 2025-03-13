#ifndef USER_AUTH_H
#define USER_AUTH_H

#include <string>
#include "database.h"
#include "logger.h"

class UserAuth {
public:
    UserAuth();
    bool login(int accountId, const std::string& password);
    int createAccount(const std::string& ownerName, const std::string& password, double initialBalance);
    int generateAccountNumber();
};

#endif // USER_AUTH_H
