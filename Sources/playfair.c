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
    initOriginalString(&originalString);
    showMatrix(matrix);
    printf("ORIGINAL STRING : '%s'\n" , originalString.text);

    int rowLetter1 , rowLetter2 , colLetter1 , colLetter2 , rowLetter1Enc , colLetter1Enc , rowLetter2Enc , colLetter2Enc;

    for(int i=0 ; i < originalString.length ; i+=2) {
        // get the positions of the letters at index i and i+1
        posLetter(matrix , originalString.text[i] , originalString.text[i+1] , &rowLetter1 , &colLetter1 , &rowLetter2 , &colLetter2);

        if(rowLetter1 == rowLetter2) {
            rowLetter1Enc = rowLetter1;
            colLetter1Enc = colLetter1 - 1;
            if(colLetter1Enc == -1) colLetter1Enc = 4;

            rowLetter2Enc = rowLetter2;
            colLetter2Enc = colLetter2 - 1;
            if(colLetter2Enc == -1) colLetter2Enc = 4;
        }

        else if(colLetter1 == colLetter2) {
            rowLetter1Enc = rowLetter1 - 1;
            colLetter1Enc = colLetter1;
            if(rowLetter1Enc == -1) rowLetter1Enc = 4;

            rowLetter2Enc = rowLetter2 - 1;
            colLetter2Enc = colLetter2;
            if(rowLetter2Enc == -1) rowLetter2Enc = 4;
        }
        else {
            rowLetter1Enc = rowLetter1;
            colLetter1Enc = colLetter2;

            rowLetter2Enc = rowLetter2;
            colLetter2Enc = colLetter1;
        }

        encryptedText[i] = matrix[5*rowLetter1Enc + colLetter1Enc];
        encryptedText[i+1] = matrix[5*rowLetter2Enc + colLetter2Enc];
    }

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

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

void initOriginalString (struct String *originalString) {

    toUpperCase(&(originalString->text) , originalString->length);

    if(originalString->length % 2 == 0) return;

    int lengthNewText = originalString->length + 1;

    char *newText = (char*)malloc(sizeof(char) * (lengthNewText + 1));

    strcpy(newText , originalString->text);

    // insert a parasite letter to have an even length
    newText[lengthNewText - 1] = 'W';
    newText[lengthNewText] = '\0';


    free(originalString->text);
    originalString->text = newText;
    originalString->length = lengthNewText;
}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************
/**
 * Change the value of rowLetter1, colLetter1, rowLetter2, colLetter 2 according to the positions of letter1 and letter2 in the matrix
 * @param matrix
 * @param letter1
 * @param letter2
 * @param rowLetter1
 * @param colLetter1
 * @param rowLetter2
 * @param colLetter2
 */
void posLetter(char *matrix , char letter1 , char letter2 , int *rowLetter1 , int *colLetter1 , int *rowLetter2 , int *colLetter2) {

    // little array to know if the position of a letter is already configured
    // posLetter[0] : letter1
    // posLetter[1] : letter2
    // 0 : the letter is not configured
    // the letter is already configured
    short posLetterOk[2];
    posLetterOk[0] = 0; posLetterOk[1] = 0;

    // the matrix doesn't contains 'X' but the case with 'W' also represents 'X
    if(letter1 == 'X') letter1 = 'W';
    if(letter2 == 'X') letter2 = 'W';

    for(int row=0 ; row < 5 ; row++) {
        for(int col=0 ; col<5 ; col++) {
            if (matrix[col + 5*row] == letter1) {
                *rowLetter1 = row;
                *colLetter1 = col;
                posLetterOk[0] = 1;
            }

            if (matrix[col + 5*row] == letter2) {
                *rowLetter2 = row;
                *colLetter2 = col;
                posLetterOk[1] = 1;
            }

            if(posLetterOk[0] == 1 && posLetterOk[1] == 1) return;
        }
    }
}


//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

void showMatrix(char matrix[5][5]) {
    printf("***************** SHOW MATRIX *****************\n");
    
    for(int j = 0 ; j<5 ; j++) {
        for(int i=0 ; i<5 ; i++)
            printf("%c\t" , matrix[j][i]);
        printf("\n");
    }
    
}

