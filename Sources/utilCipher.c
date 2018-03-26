//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#include "../Headers/utilCipher.h"
#include "../Headers/utilEnum.h"
#include "../Headers/caesar.h"

/**
 * Take an array containing the arguments entered by the user when launching the program and return structure with those information.
 * @param args
 * @param length
 * @return
 */
struct InfoCipher initInfoCipherFromArgs(char *args[]) {

    struct InfoCipher infoCipher;

    /* *************************************** CHOOSE BETWEEN BETWEEN ENCRYPTION AND DECRYPTION *************************************** */
    if(strcmp(args[1] , "-e") == 0)
        infoCipher.mode = ENCRYPTION;
    else if(strcmp(args[1] , "-d") == 0)
        infoCipher.mode = DECRYPTION;
    else
        error("The choice between encryption and decryption is not correct : Please select '-e' or '-d'");

    /* *************************************** CHOOSE THE ALGORITHM *************************************** */

    if(strcmp(args[2] , "-s") == 0)
        infoCipher.algo = SUBSTITUTION;
    else if(strcmp(args[2] , "-c") == 0)
        infoCipher.algo = CAESAR;
    else if(strcmp(args[2] , "-v") == 0)
        infoCipher.algo = VIGENERE;
    else if(strcmp(args[2] , "se") == 0)
        infoCipher.algo = SELFENCRYPTION;
    else if(strcmp(args[2] , "-p" ) == 0)
        infoCipher.algo = PLAYFAIR;
    else
        error("The algorithm provided is not correct : Please choose between '-s', '-c', '-v', '-se' and '-p'");

    /* *************************************** SAVE THE ORIGINAL FILE NAME *************************************** */

    infoCipher.originalFileName = args[3];

    /* *************************************** SAVE THE KEY *************************************** */

    infoCipher.key = args[4];

    return infoCipher;
}

/**
 * Display the information about the cipher in the default output file.
 * @param infoCipher
 */
void showRecapCipher (struct InfoCipher infoCipher) {

    char *stringMode = stringFromMode(infoCipher.mode);
    char *stringAlgo = stringFromAlgo(infoCipher.algo);

    fprintf(output , "RECAP OF THE INFO :\n");
    fprintf(output , "\tMODE : %s\n" , stringMode);
    fprintf(output , "\tALGO : %s\n" , stringAlgo);
    fprintf(output , "\tORIGINAL FILE : %s\n" , infoCipher.originalFileName);
    fprintf(output , "\tKEY : %s\n" , infoCipher.key);

    free(stringMode);
    free(stringAlgo);
}

/**
 * Once we have all the information to perform the program, this method is called.
 * @param originalText
 * @param mode
 * @param algo
 * @param key
 */
void work(struct String originalString , enum Mode mode , enum Algorithm algo , char *key) {

    struct String result;

    switch (algo) {
        case CAESAR:
            if(mode == ENCRYPTION)
                result = caesarEncrypt(originalString , key);
            else if(mode == DECRYPTION)
                result = caesarDecrypt(originalString , key);
            break;
        case SUBSTITUTION:
            //TODO
            break;
        case VIGENERE:
            if(mode == ENCRYPTION)
                result = vigenereEncrypt(originalString , key);
            else if(mode == DECRYPTION)
                result = vigenereDecrypt(originalString , key);
            break;
        case SELFENCRYPTION:
            //TODO
            break;
        case PLAYFAIR:
            if(mode == ENCRYPTION)
                result = playfairEncrypt(originalString , key);
            else if(mode == DECRYPTION)
                result = playfairDecrypt(originalString , key);
            break;
    }

    fprintf(output , "\nRESULT :\n%s\n" , result.text);

    free(result.text);



}


