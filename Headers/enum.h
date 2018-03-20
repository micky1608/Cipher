//
// Created by mteau on 20/03/2018.
//

#ifndef DECRYPTION_ENUM_H
#define DECRYPTION_ENUM_H

enum Mode { ENCRYPTION , DECRYPTION };

enum Algorithm { SUBSTITUTION , CAESAR , VIGENERE, AUTO, PLAYFAR };

union Key {
    int keyInteger;
    char *keyString;
    char * keyFileName;
};

#endif //DECRYPTION_ENUM_H
