//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#include "../Headers/utilCipher.h"

/**
 * Take an array containing the arguments entered by the user when launching the program and return structure with those information.
 * The first argument, which is the name of the program, is not in the array.
 * @param args
 * @param length
 * @return
 */
struct InfoCipher initInfoCipherFromArgs(char *args[] , int length) {

    struct InfoCipher infoCipher;

    /* *************************************** CHOOSE BETWEEN BETWEEN ENCRYPTION AND DECRYPTION *************************************** */
    if(strcmp(args[0] , "-e"))
        infoCipher.mode = ENCRYPTION;
    else if(strcmp(args[0] , "-d"))
        infoCipher.mode = DECRYPTION;
    else
        error("The choice between encryption and decryption is not correct : Please select '-e' or '-d'");

    /* *************************************** CHOOSE THE ALGORITHM *************************************** */

    if(strcmp(args[1] , "-s"))
        infoCipher.algo = SUBSTITUTION;
    else if(strcmp(args[1] , "-c"))
        infoCipher.algo = CAESAR;
    else if(strcmp(args[1] , "-v"))
        infoCipher.algo = VIGENERE;
    else if(strcmp(args[1] , "se"))
        infoCipher.algo = SELFENCRYPTION;
    else if(strcmp(args[1] , "-p" ))
        infoCipher.algo = PLAYFAIR;
    else
        error("The algorithm provided is not correct : Please choose between '-s', '-c', '-v', '-se' and '-p'");

    /* *************************************** SAVE THE ORIGINAL FILE NAME *************************************** */

    infoCipher.originalFileName = args[2];

    /* *************************************** SAVE THE KEY *************************************** */

    if(infoCipher.algo == CAESAR)
        infoCipher.key.keyInteger = atoi(args[3]);
    else if(infoCipher.algo == VIGENERE || infoCipher.algo == SELFENCRYPTION || infoCipher.algo == PLAYFAIR)
        infoCipher.key.keyString = args[3];
    else if(infoCipher.algo == SUBSTITUTION)
        infoCipher.key.keyFileName = args[3];


    return infoCipher;

}


