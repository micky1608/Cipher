//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#ifndef DECRYPTION_STRUCTURES_H
#define DECRYPTION_STRUCTURES_H

#include "enum.h"


struct InfoCipher {
    enum Mode mode;
    enum Algorithm algo;
    char *originalFileName;
    char *key;
};

struct String {
    char *text;
    int length;
};

#endif //DECRYPTION_STRUCTURES_H
