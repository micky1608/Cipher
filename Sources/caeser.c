//
// Created by TEAUDORS Mickael on 20/03/2018.
//



#include "../Headers/caesar.h"


struct String caesarEncrypt(struct String originalString , char *key) {

    // create a String to store the result of the encryption
    struct String encryptedString;
    encryptedString.length = originalString.length;

    // allocate memory for the text
    char *encryptedText = (char*) malloc(sizeof(char)*(originalString.length + 1));

    // get the integer key for the algorithm from the string key
    // the key must be between 0 and 25
    int keyNum = keyNumberFromKeyString(key);

    // check if the key is valid
    if(keyNum < 0 || keyNum > 25)
        keyNum = keyNum%26;

    // variable to store the alphabet position of the original letter and the one of the encrypted letter
    // 'A' has a position of 0
    int originalPosition , encryptedPosition;

    // encrypt letter by letter
    for(int i=0 ; i<originalString.length ; i++) {

        // if the letter is in lower case
        if(originalString.text[i] >= 'a' && originalString.text[i] <= 'z') {

            originalPosition = originalString.text[i] - 'a';
            encryptedPosition = (originalPosition + keyNum)%26;

            encryptedText[i] = (char)('a' + encryptedPosition);
        }

        //if the letter is in upper case
        else if(originalString.text[i] >= 'A' && originalString.text[i] <= 'Z') {
            originalPosition = originalString.text[i] - 'A';
            encryptedPosition = (originalPosition + keyNum)%26;

           encryptedText[i] = (char)('A' + encryptedPosition);
        }

            // else the character is not modified
        else
            encryptedText[i] = originalString.text[i];

    } //for

    free(key);

    encryptedText[encryptedString.length] = '\0';

    encryptedString.text = encryptedText;

    return encryptedString;

}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

struct String caesarDecrypt(struct String encryptedString , char *key) {



    struct String originalString;
    originalString.length = encryptedString.length;
    char *originalText = (char*)malloc(sizeof(char) * (encryptedString.length + 1));

    // get the integer key for the algorithm from the string key
    // the key must be between 0 and 25
    int keyNum = keyNumberFromKeyString(key);

    // check if the key is valid
    if(keyNum < 0 || keyNum > 25)
        keyNum = keyNum%26;


    int encryptedPosition , originalPosition;

    for(int i=0 ; i<encryptedString.length ; i++) {

        // if the letter is in lower case
        if(encryptedString.text[i] >= 'a' && encryptedString.text[i] <= 'z') {

            encryptedPosition = encryptedString.text[i] - 'a';
            originalPosition = (encryptedPosition - keyNum)%26;

            originalText[i] = (char)('a' + originalPosition);
        }

            //if the letter is in upper case
        else if(encryptedString.text[i] >= 'A' && encryptedString.text[i] <= 'Z') {

            encryptedPosition = encryptedString.text[i] - 'A';
            originalPosition = (encryptedPosition - keyNum)%26;

            originalText[i] = (char)('A' + originalPosition);
        }

            // else the character is not modified
        else
            originalText[i] = encryptedString.text[i];
    } //for

    free(key);

    originalText[originalString.length] = '\0';
    originalString.text = originalText;

    return originalString;
}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

int keyNumberFromKeyString (char *keyString) {

    // set errno to 0 to make the difference between success and fail of the 'strtol' function
    errno = 0;

    char *endptr;

    int keyNum = strtol(keyString , &endptr , 10);

    if(errno == ERANGE) {
        if(keyNum == LONG_MIN)
            error("Your key is too small" , NULL);
        if(keyNum == LONG_MAX)
            error("Your key is too high" , NULL);
    }

    if(errno != 0 && keyNum == 0)
        error("Problem converting the string" , NULL);

    if(endptr == keyString) error("Your key isn't valid, please check that it only contains figures" , NULL);

    return keyNum;
}

