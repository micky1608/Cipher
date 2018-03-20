//
// Created by mteau on 20/03/2018.
//

#ifndef DECRYPTION_STRUCTURES_H
#define DECRYPTION_STRUCTURES_H


struct InfoCipher {
    enum Mode mode;
    enum Algorithm algo;
    char *originalFileName;
    union Key key;
};

#endif //DECRYPTION_STRUCTURES_H
