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

struct InfoCipher initInfoCipherFromArgs(char*[]);

void showRecapCipher (struct InfoCipher);

#endif //DECRYPTION_UTILCIPHER_H

