//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#include "../Headers/substitution.h"


struct String substitutionEncrypt(struct String originalString , char *key) {

    struct String encryptedString;
    encryptedString.length = originalString.length;
    char *encryptedText = (char*)malloc(sizeof(char) * (encryptedString.length + 1));

    struct SubstitutionLink *link = (struct SubstitutionLink *) malloc(sizeof(struct SubstitutionLink) * 26);
    initArrayLink(&link , key);

    for(int i=0 ; i<originalString.length ; i++) {

        char originalCharacter = originalString.text[i];

        if(originalCharacter >= 'A' && originalCharacter <= 'Z')
           encryptedText[i] = link[originalCharacter - 'A'].encryptedLetter;
        else
            encryptedText[i] = originalCharacter;

    }




    encryptedText[encryptedString.length] = '\0';
    encryptedString.text = encryptedText;
    free(link);
    free(key);
    return encryptedString;
}



//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************


struct String substitutionDecrypt(struct String encryptedString , char *key) {

    struct String originalString;
    originalString.length = encryptedString.length;
    char *originalText = (char*)malloc(sizeof(char) * (originalString.length + 1));

    struct SubstitutionLink *link = (struct SubstitutionLink *)malloc(sizeof(struct SubstitutionLink) * 26);
    initArrayLink(&link , key);

    char encryptedCharacter;
    int k=0;

    for(int i=0 ; i<encryptedString.length ; i++) {
        encryptedCharacter  = encryptedString.text[i];

        if(encryptedCharacter >= 'A' && encryptedCharacter <= 'Z') {

            while(k<26 && link[k].encryptedLetter != encryptedCharacter) k++;

            originalText[i] = link[k].originalLetter;

            k=0;
        }
        else {
            originalText[i] = encryptedCharacter;
        }
    }

    free(link);
    free(key);
    originalText[originalString.length] = '\0';
    originalString.text = originalText;
    return originalString;
}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

/**
 * Init an array of the substitutions between all the letters using the corresponding file.
 * @param link a pointer towards the array we want to init
 * @param fileName the name of the file containing the substitutions. This file must be built like this :
 *          each line contains the original letter, a colon and the encrypted letter associated.
 *          For example( A:E ) means that the A is ciphered with the E.
 *          All the letters are in UPPER CASE and the original letters are stored by alphabetical order. Thus, the alphabet can be read by taking every first character of each line.
 */
void initArrayLink(struct SubstitutionLink **link , char *fileName) {

    struct String fileContent = readFile(fileName);
    char originalLetter , encryptedLetter;

    // create an array to check that an encrypted letter is not used multiple times
    // 0 : the letter is not used yet
    // 1 : the letter is used
    int encryptedLetterUsed[26];
    for(int i=0 ; i<26 ; i++) encryptedLetterUsed[i] = 0;

    for(int i=0 ; i<26 ; i++) {

        if(i==25 || fileContent.text[4*i + 3] == '\n') {

            // get the original letter
            originalLetter = fileContent.text[4*i];

            // check the character is correct
            if(originalLetter >= 'A' && originalLetter <= 'Z') {

                //check that the letters are in the good order
                if(originalLetter == 'A' + i) {

                    // get the encrypted letter corresponding to the original letter
                    encryptedLetter = fileContent.text[4*i + 2];

                    // check the character is valid
                    if(encryptedLetter >= 'A' && encryptedLetter <= 'Z') {

                        // check the letter is not used yet
                        if(encryptedLetterUsed[encryptedLetter - 'A'] == 0) {

                            // store the link in the array
                            (*link + i)->originalLetter = originalLetter;
                            (*link + i)->encryptedLetter = encryptedLetter;

                            // mark this letter as used
                            encryptedLetterUsed[encryptedLetter - 'A'] = 1;
                        }
                        else {
                            error("Multiple encryption with the same letter" , NULL);
                        }
                    }
                    else {
                        error("Encrypted letter not valid" , NULL);
                    }
                }
                else {
                    error("Letters not in alphabetical order OR file not complete" , NULL);
                }
            }
            else {
                error("Each line must start with a letter" , NULL);
            }
        }
        else {
            fprintf(output , "Line error : %d\tchar : '%c'\n" , i , fileContent.text[4*i + 3]);
            error("Line with incorrect length" , NULL);
        }

    }

    free(fileContent.text);
}






