//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#ifndef DECRYPTION_UTILCIPHER_H
#define DECRYPTION_UTILCIPHER_H

#include <stdio.h>
#include "structures.h"
#include "enum.h"
#include "error.h"
#include "global.h"
#include "vigenere.h"

struct InfoCipher initInfoCipherFromArgs(char*[]);

void showRecapCipher (struct InfoCipher);

void work(struct String, enum Mode, enum Algorithm, char *);

#endif //DECRYPTION_UTILCIPHER_H

