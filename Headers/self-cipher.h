//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#ifndef CIPHER_SELF_ENCRYPTION_H
#define CIPHER_SELF_ENCRYPTION_H

#include <stdlib.h>
#include "../Headers/structures.h"
#include "utilString.h"
#include "error.h"
#include "string.h"
#include "global.h"

struct String selfCipherEncrypt (struct String , char *);
struct String selfCipherDecrypt (struct String , char *);
char* selfCipherInitKeyForEncryption(char *originalKey, char *originalText);

#endif //CIPHER_SELF_ENCRYPTION_H
