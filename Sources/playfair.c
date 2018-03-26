//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#include "../Headers/playfair.h"

struct String playfairEncrypt (struct String originalString , char *key) {

    struct String encryptedString;
    char *encryptedText = (char*)malloc(sizeof(char) * (originalString.length) + 1);
    encryptedString.length = originalString.length;
    char *matrix = (char*)malloc(sizeof(char) * 25);
    initMatrix(&matrix , key);
    showMatrix(matrix);
    

    //TODO

    free(key); free(matrix);
    encryptedText[encryptedString.length] = '\0';
    encryptedString.text = encryptedText;
    return encryptedString;
}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

struct String playfairDecrypt (struct String encryptedString , char *key) {
        //TODO
}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

void initMatrix (char **matrice , char *keyWord) {

    // get the size of the key
    int keyWordSize = strlen(keyWord);

    if(containsOnlyLetters(keyWord , keyWordSize) == -1)
        error("La cle ne doit contenir que des lettres");

    // transform the key to upper case if it is not
    toUpperCase(&keyWord , keyWordSize);

    // a short table that indicate if each letter is already in the matrix
    // 0 : the is not yet
    // 1 : the letter is already
    // by default : no letter in the matrix
    short letterInMatrice[26];
    for(int i=0 ; i<26 ; i++) letterInMatrice[i] = 0;

    int indexRow = 0 , indexColumn = 0;

    for(int i=0 ; i< keyWordSize ; i++) {
        // get the letter to add in the matrix
        char letter = keyWord[i];

        // check it is not already in
        if(letterInMatrice[letter - 'A'] == 0) {

            // add in the matrix
            *(*matrice + indexColumn + 5*indexRow) = letter;

            letterInMatrice[letter - 'A'] = 1;

            indexColumn++;
            if(indexColumn == 5) {
                indexColumn = 0;
                indexRow++;
            }
        }
    }

    // now add the missing letters
    for(char c = 'A' ; c <= 'Z' ; c++) {

        if(c != 'X') {

                if(letterInMatrice[c - 'A'] == 0) {
                    *(*matrice + indexColumn + 5*indexRow) = c;

                    letterInMatrice[c - 'A'] = 1;

                    indexColumn++;
                    if(indexColumn == 5) {
                        indexColumn = 0;
                        indexRow++;
                    }
                }

        }
    }
}

void showMatrix(char matrix[5][5]) {
    printf("***************** SHOW MATRIX *****************\n");
    
    for(int j = 0 ; j<5 ; j++) {
        for(int i=0 ; i<5 ; i++)
            printf("%c\t" , matrix[j][i]);
        printf("\n");
    }
    
}

