#ifndef SHARED_TRANSACTION_H
#define SHARED_TRANSACTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h> 
#include <stddef.h>   

bool deposit(int accountId, double amount);
bool withdraw(int accountId, double amount);
bool transfer(int senderId, int receiverId, double amount);

#ifdef __cplusplus
}
#endif

#endif // SHARED_TRANSACTION_H
