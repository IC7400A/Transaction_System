#ifndef SECURITY_H
#define SECURITY_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool authenticateUser(int accountId, const char* password);
bool registerUser(int accountId, const char* password);

#ifdef __cplusplus
}
#endif

#endif // SECURITY_H
