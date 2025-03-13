#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include "database.h"
#include "logger.h"

class Transaction {
public:
    explicit Transaction(int accountId);
    bool deposit(double amount);
    bool withdraw(double amount);
    bool transfer(int recipientId, double amount);

private:
    int accountId;
};

#endif // TRANSACTION_H
