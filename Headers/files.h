//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#ifndef CIPHER_FILES_H
#define CIPHER_FILES_H

#include <fcntl.h>
#include <sys/stat.h>
#include "error.h"
#include "global.h"

char* readFile(char*);

void initOutput();

void changeDefaultOutput(char*);

size_t fileSize (char *);

#endif //CIPHER_FILES_H
