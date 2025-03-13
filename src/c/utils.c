#include "../../include/c/utils.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* trim(char *str) {
    if (str == NULL) return NULL;

    while (isspace((unsigned char)*str)) str++;

    if (*str == '\0') return str;

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';
    return str;
}

bool isValidNumber(const char *str) {
    if (str == NULL || *str == '\0') return false;

    char *endptr;
    strtod(str, &endptr);

    return (*endptr == '\0');
}
