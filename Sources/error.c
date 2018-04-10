//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#include "../Headers/error.h"

void error(char *message , char *param) {
    if(param == NULL)
        fprintf(stderr , message);

    else
        fprintf(stderr , "%s -> %s" , message , param);

    perror(" ");

    exit(EXIT_FAILURE);
}

