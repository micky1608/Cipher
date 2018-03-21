//
// Created by TEAUDORS Mickael on 20/03/2018.
//


#include <limits.h>
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

            encryptedText[i] = 'a' + encryptedPosition;
        }

        //if the letter is in upper case
        else if(originalString.text[i] >= 'A' && originalString.text[i] <= 'Z') {
            originalPosition = originalString.text[i] - 'A';
            encryptedPosition = (originalPosition + keyNum)%26;

           encryptedText[i] = 'A' + encryptedPosition;
        }

            // else the character is not modified
        else
            encryptedText[i] = originalString.text[i];

    } //for

    encryptedText[encryptedString.length] = '\0';

    encryptedString.text = encryptedText;

    return encryptedString;

}

struct String caesarDecrypt(struct String encryptedString , char *key) {
    //TODO
}

int keyNumberFromKeyString (char *keyString) {

    // set errno to 0 to make the difference between success and fail of the 'strtol' function
    errno = 0;

    char *endptr;

    int keyNum = strtol(keyString , &endptr , 10);

    if(errno == ERANGE) {
        if(keyNum == LONG_MIN)
            error("Your key is too small");
        if(keyNum == LONG_MAX)
            error("Your key is too high");
    }

    if(errno != 0 && keyNum == 0)
        error("Problem converting the string");

    if(endptr == keyString) error("Your key doesn't contain any figure");

    return keyNum;
}

