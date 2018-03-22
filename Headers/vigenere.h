//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#ifndef CIPHER_VIGENERE_H
#define CIPHER_VIGENERE_H

#include "../Headers/structures.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

struct String vigenereEncrypt(struct String, char*);
struct String vigenereDecrypt(struct String, char*);
char* vigenereKeyGoodSize (char *, int);


#endif //CIPHER_VIGENERE_H
