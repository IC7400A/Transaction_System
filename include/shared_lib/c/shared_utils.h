#ifndef SHARED_UTILS_H
#define SHARED_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <ctype.h>  
#include <string.h> 

int generateAccountNumber();
void trim(char *str);
bool isValidNumber(const char *str);

#ifdef __cplusplus
}
#endif

#endif // SHARED_UTILS_H
