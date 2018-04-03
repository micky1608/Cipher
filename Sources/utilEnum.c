//
// Created by TEAUDORS Mickael on 20/03/2018.
//


#include "../Headers/utilEnum.h"


char* stringFromMode(enum Mode mode) {
    char* result = (char*)malloc(11 * sizeof(char));
    if(mode == ENCRYPTION)
        strcpy(result , "encryption");
    else if(mode == DECRYPTION)
        strcpy(result , "decryption");

    result[10] = '\0';

    return result;

}

char* stringFromAlgo (enum Algorithm algo) {
    char *result = (char*)malloc(16*sizeof(char));

    if(algo == SUBSTITUTION)
        strcpy(result , "substitution");
    else if(algo == CAESAR)
        strcpy(result , "caesar");
    else if(algo == VIGENERE)
        strcpy(result , "vigenere");
    else if(algo == SELFCIPHER)
        strcpy(result , "self-encryption");
    else if(algo == PLAYFAIR)
        strcpy(result , "playfair");

    return result;
}

