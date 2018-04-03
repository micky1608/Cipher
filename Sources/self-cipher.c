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

/**
 * initialise the key to allow encryption with the self cipher algorithm. The key will be changed to upper case if it is not.
 * Besides, the size of the key will be adapted to the size of the text.
 * The key must contain only letters.
 * @param originalKey
 * @param originalText
 * @return
 */
char* selfCipherInitKeyForEncryption(char *originalKey, char *originalText) {

    int i;
    int originalKeyLength = strlen(originalKey);
    int originalTextLength = strlen(originalText);

    // if there are other characters except letters, the program stop because the algorithm is unusable
    if(containsOnlyLetters(originalKey , originalKeyLength) == -1)
        error("Key must contain only letters");

    // change the key to upper case
    toUpperCase(&originalKey , originalKeyLength);

    // if the key size is already the same that the text size, there are no more changes to do
    if(originalKeyLength == originalTextLength) return originalKey;

    // memory allocation for the key with the good size
    char *newKey = (char*)malloc(sizeof(char) * (originalTextLength + 1));

    // if the key is too long, it is just cut
    if(originalKeyLength > originalTextLength) {
        for(int i=0 ; i<originalTextLength ; i++)
            newKey[i] = originalKey[i];
    }

    // if the key is shorter than the text, then we complete the key with the beginning of the text
    else if(originalKeyLength < originalTextLength) {
        int counterNewKey = 0;

        // first we copy the original key
        for(i=0 ; i<originalKeyLength ; i++) {
            newKey[counterNewKey] = originalKey[i];
            counterNewKey++;
        }

        i=0;

        // complete with the beginning of the text
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
