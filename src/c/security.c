#include "../../include/c/security.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PASSWORD_LENGTH 100
#define PASSWORD_FILE "data/accounts.db"

bool registerUser(int accountId, const char *password) {
    if (accountId <= 0 || password == NULL || strlen(password) == 0) {
        fprintf(stderr, "Error: Invalid account ID or empty password.\n");
        return false;
    }

    FILE *file = fopen(PASSWORD_FILE, "a");
    if (!file) {
        perror("Error opening password database for writing");
        return false;
    }

    fprintf(file, "%d %s\n", accountId, password);
    fclose(file);
    return true;
}

bool authenticateUser(int accountId, const char *password) {
    if (accountId <= 0 || password == NULL) {
        fprintf(stderr, "Error: Invalid account ID or null password.\n");
        return false;
    }

    FILE *file = fopen(PASSWORD_FILE, "r");
    if (!file) {
        perror("Error opening password database for reading");
        return false;
    }

    int storedId;
    char storedPassword[MAX_PASSWORD_LENGTH];

    while (fscanf(file, "%d %99s", &storedId, storedPassword) == 2) {
        if (storedId == accountId && strcmp(storedPassword, password) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}
