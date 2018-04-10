//
// Created by TEAUDORS Mickael on 20/03/2018.
//


#include "../Headers/vigenere.h"



struct String vigenereEncrypt(struct String originalString , char *key ) {

    struct String encryptedString;
    encryptedString.length = originalString.length;
    char *encryptedText = (char*)malloc(sizeof(char) * (originalString.length + 1));

    key = vigenereKeyGoodSize(key , originalString.length);

    int originalPosition , keyPosition;

    for(int i=0 ; i<originalString.length ; i++) {

        // if the original letter is in upper case
        if(originalString.text[i] >= 'A' && originalString.text[i] <= 'Z') {

            // if the key is in lower case need to transform in upper case
            if(key[i] >= 'a' && key[i] <= 'z')
                key[i] -= 32;

            originalPosition = originalString.text[i] - 'A';
            keyPosition = key[i] - 'A';
            encryptedText[i] = (char)('A' + (originalPosition + keyPosition) % 26);

        }

        // the original letter is in lower case
        else if (originalString.text[i] >= 'a' && originalString.text[i] <= 'z') {

            // if the key is in upper case need to transform in lower case
            if(key[i] >= 'A' && key[i] <= 'Z')
                key[i] += 32;

            originalPosition = originalString.text[i] - 'a';
            keyPosition = key[i] - 'a';
            encryptedText[i] = (char)('a' + (originalPosition + keyPosition)%26);
        }

        else
            encryptedText[i] = originalString.text[i];


    }

    free(key);
    encryptedText[encryptedString.length] = '\0';
    encryptedString.text = encryptedText;
    return encryptedString;

}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

struct String vigenereDecrypt(struct String encryptedString , char *key) {

    struct String originalString;
    originalString.length = encryptedString.length;
    char *originalText = (char*)malloc(sizeof(char) * (encryptedString.length + 1));
    key = vigenereKeyGoodSize(key , encryptedString.length);

    int encryptedPosition , keyPosition , originalPosition;

    for(int i=0 ; i<encryptedString.length ; i++) {

        // if the encrypted letter is in upper case
        if(encryptedString.text[i] >= 'A' && encryptedString.text[i] <= 'Z') {

            // if the key is in lower case need to transform in upper case
            if(key[i] >= 'a' && key[i] <= 'z')
                key[i] -= 32;

            encryptedPosition = encryptedString.text[i] - 'A';
            keyPosition = key[i] - 'A';
            originalPosition = (encryptedPosition - keyPosition) % 26;
            originalPosition = (originalPosition < 0) ? originalPosition + 26 : originalPosition;
            originalText[i] = (char)('A' + originalPosition);

        }

            // the original letter is in lower case
        else if (encryptedString.text[i] >= 'a' && encryptedString.text[i] <= 'z') {

            // if the key is in upper case need to transform in lower case
            if(key[i] >= 'A' && key[i] <= 'Z')
                key[i] += 32;

            encryptedPosition = encryptedString.text[i] - 'a';
            keyPosition = key[i] - 'a';
            originalPosition = (encryptedPosition - keyPosition);
            originalPosition = (originalPosition < 0) ? originalPosition + 26 : originalPosition;
            originalText[i] = (char)('a' + originalPosition);

        }

        else
            originalText[i] = encryptedString.text[i];
    }

    free(key);
    originalText[originalString.length] = '\0';
    originalString.text = originalText;
    return originalString;

}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************


char* vigenereKeyGoodSize (char *key , int finalSize) {

    int originalSize = strlen(key);

    if(containsOnlyLetters(key , originalSize) == -1)
        error("Key must contain only letters" , key);

    if(originalSize == finalSize)
        return key;

    else {

        char* newKey = (char*)malloc(sizeof(char) * (finalSize + 1));

        if(originalSize > finalSize) {
            for(int i=0 ; i<finalSize ; i++)
                newKey[i] = key[i];
        }

        else if(originalSize < finalSize) {
            int counter = 0;

            for(int i=0 ; i<finalSize ; i++) {
                newKey[i] = key[counter];
                counter = (counter + 1)%originalSize;
            }
        }

        newKey[finalSize] = '\0';
        free(key);
        return newKey;
    }

}
