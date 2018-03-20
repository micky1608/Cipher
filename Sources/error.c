//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#include "../Headers/error.h"

void error(char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

