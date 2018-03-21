//
// Created by mteau on 20/03/2018.
//

#ifndef CIPHER_CAESAR_H
#define CIPHER_CAESAR_H

#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "error.h"
#include "structures.h"
#include "global.h"

struct String caesarEncrypt(struct String originalText , char *key);
struct String caesarDecrypt(struct String encryptedText , char *key);

int keyNumberFromKeyString (char *);

#endif //CIPHER_CAESAR_H
