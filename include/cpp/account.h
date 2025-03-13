#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
private:
    int accountId;
    double balance;

public:
    Account(int id, double initialBalance);
    int getAccountId() const;
    double getBalance() const;
    void deposit(double amount);
    bool withdraw(double amount);
    bool transfer(Account &recipient, double amount);
};

#endif // ACCOUNT_H
