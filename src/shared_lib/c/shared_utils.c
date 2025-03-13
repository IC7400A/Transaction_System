#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../../../include/shared_lib/c/shared_utils.h"

int generate_account_number() {
    srand(time(NULL));
    return 100 + (rand() % 900);
}

void safe_input(char *buffer, int size) {
    if (fgets(buffer, size, stdin)) {
        char *newline = strchr(buffer, '\n');
        if (newline) {
            *newline = '\0';
        }
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
