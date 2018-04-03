//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#include "../Headers/self-cipher.h"


struct String selfCipherEncrypt (struct String originalString , char *key) {

    struct String encryptedString;
    encryptedString.length = originalString.length;
    char *encryptedText = (char*)malloc(sizeof(char) * (encryptedString.length + 1));
    key = selfCipherInitKeyForEncryption(key, originalString.text);

    int originalposition , keyPosition , encryptedPosition;

    for(int i=0 ; i<originalString.length ; i++) {
        originalposition = originalString.text[i] - 'A';
        keyPosition = key[i] - 'A';
        encryptedPosition = (originalposition + keyPosition) % 26;
        encryptedText[i] = 'A' + encryptedPosition;
    }

    free(key);
    encryptedText[encryptedString.length] = '\0';
    encryptedString.text = encryptedText;
    return encryptedString;

}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

struct String selfCipherDecrypt (struct String encryptedString , char *key) {
    struct String originalString;
    originalString.length = encryptedString.length;
    char *originalText = (char*)malloc(sizeof(char) * (originalString.length + 1));



    int originalposition , keyPosition , encryptedPosition , counterKey = 0 , keySize;
    keySize = strlen(key);

    toUpperCase(&key , keySize);

    for(int i=0 ; i<encryptedString.length ; i++) {
        encryptedPosition = encryptedString.text[i] - 'A';
        keyPosition = key[counterKey] - 'A';
        originalposition = encryptedPosition - keyPosition;
        originalposition = (originalposition < 0) ? originalposition+26 : originalposition;
        originalText[i] = 'A' + originalposition;

        counterKey++;
        if(counterKey == keySize) {
            for(int k=0 ; k<keySize ; k++) {
                key[k] = originalText[(i + 1) - keySize + k];
            }
            counterKey = 0;
        }

    }

    free(key);
    originalText[originalString.length] = '\0';
    originalString.text = originalText;
    return originalString;
}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

char* selfCipherInitKeyForEncryption(char *originalKey, char *originalText) {

    int i;
    int originalKeyLength = strlen(originalKey);
    int originalTextLength = strlen(originalText);

    if(containsOnlyLetters(originalKey , originalKeyLength) == -1)
        error("Key must contain only letters");

    toUpperCase(&originalKey , originalKeyLength);

    if(originalKeyLength == originalTextLength) return originalKey;

    char *newKey = (char*)malloc(sizeof(char) * (originalTextLength + 1));

    if(originalKeyLength > originalTextLength) {
        for(int i=0 ; i<originalTextLength ; i++)
            newKey[i] = originalKey[i];
    }
    else if(originalKeyLength < originalTextLength) {
        int counterNewKey = 0;

        for(i=0 ; i<originalKeyLength ; i++) {
            newKey[counterNewKey] = originalKey[i];
            counterNewKey++;
        }

        i=0;

        while(counterNewKey < originalTextLength) {
            newKey[counterNewKey] = originalText[i];
            i++;
            counterNewKey++;
        }
    }


    free(originalKey);
    newKey[originalTextLength] = '\0';
    return newKey;


}
