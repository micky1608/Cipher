//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#include "../Headers/playfair.h"

struct String playfairEncrypt (struct String originalString , char *key) {

    struct String encryptedString;

    // init the matrix which will not contain any 'X'
    // we consider that the 'X' is in the same case that 'W'
    char *matrix = (char*)malloc(sizeof(char) * 25);
    initMatrix(&matrix , key);

    // transform the initial text in uppercase and add a parasite letter if the length is not even
    // the parasite letter is 'W'
    initOriginalString(&originalString);

    // allocation of memory for the encrypted text
    encryptedString.length = originalString.length;
    char *encryptedText = (char*)malloc(sizeof(char) * (originalString.length) + 1);

    // show the matrix either in the console or in the file chosen by the user to redirect the out stream
    // this line can be deleted
    showMatrix(matrix);

    // variable to store the positions of each letters in the matrix
    // rows and columns start at 0 and finish at 4
    int rowLetter1 , rowLetter2 , colLetter1 , colLetter2 , rowLetter1Enc , colLetter1Enc , rowLetter2Enc , colLetter2Enc;

    // iterate throughout the text reading letters by 2
    for(int i=0 ; i < originalString.length ; i+=2) {

        // get the positions of the letters at index i and i+1
        posLetter(matrix , originalString.text[i] , originalString.text[i+1] , &rowLetter1 , &colLetter1 , &rowLetter2 , &colLetter2);

        // if the two letters are on the same row
        // then we just shift to the right
        if(rowLetter1 == rowLetter2) {
            rowLetter1Enc = rowLetter1;
            colLetter1Enc = colLetter1 + 1;
            if(colLetter1Enc == 5) colLetter1Enc = 0;

            rowLetter2Enc = rowLetter2;
            colLetter2Enc = colLetter2 +1;
            if(colLetter2Enc == 4) colLetter2Enc = 0;
        }

            // if the two letters are on the same column
            // then we just shift to the bottom
        else if(colLetter1 == colLetter2) {
            rowLetter1Enc = rowLetter1 + 1;
            colLetter1Enc = colLetter1;
            if(rowLetter1Enc == 4) rowLetter1Enc = 0;

            rowLetter2Enc = rowLetter2 + 1;
            colLetter2Enc = colLetter2;
            if(rowLetter2Enc == 4) rowLetter2Enc = 0;
        }

        // else we apply the main rule of the algorithm
        else {
            rowLetter1Enc = rowLetter1;
            colLetter1Enc = colLetter2;

            rowLetter2Enc = rowLetter2;
            colLetter2Enc = colLetter1;
        }

        // when the positions of the two encrypted letters are known
        // we add those letters in the encrypted text
        encryptedText[i] = matrix[5*rowLetter1Enc + colLetter1Enc];
        encryptedText[i+1] = matrix[5*rowLetter2Enc + colLetter2Enc];

    } // for

    free(key); free(matrix);
    encryptedText[encryptedString.length] = '\0';
    encryptedString.text = encryptedText;
    return encryptedString;
}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

struct String playfairDecrypt (struct String encryptedString , char *key) {
    struct String originalString;

    // init the matrix which will not contain any 'X'
    // we consider that the 'X' is in the same case that 'W'
    char *matrix = (char*)malloc(sizeof(char) * 25);
    initMatrix(&matrix , key);

    // allocation of memory for the original text
    originalString.length = encryptedString.length;
    char *originalText = (char*)malloc(sizeof(char) * (originalString.length + 1));

    // transform the encrypted in uppercase
    toUpperCase(&encryptedString.text , strlen(encryptedString.text));

    // OPTION : show the matrix either in the console or the file where the output stream is redirected
    showMatrix(matrix);

    // positions of the letters in the matrix
    // rows and columns start at 0 and finish at 4
    int rowLetter1Enc , colLetter1Enc , rowLetter2Enc , colLetter2Enc , rowLetter1 , colLetter1 , rowLetter2 , colLetter2;

    // iterate throughout the encrypted text
    for(int i=0 ; i<encryptedString.length ; i+=2) {
        // get the positions of the letters at index i and i+1
        posLetter(matrix , encryptedString.text[i] , encryptedString.text[i+1] , &rowLetter1Enc , &colLetter1Enc , &rowLetter2Enc , &colLetter2Enc);

        // if the two letters are on the same row
        // then we just shift to the left
        if(rowLetter1Enc == rowLetter2Enc) {
            rowLetter1 = rowLetter1Enc;
            colLetter1 = colLetter1Enc - 1;
            if(colLetter1 == -1) colLetter1 = 4;

            rowLetter2 = rowLetter2Enc;
            colLetter2 = colLetter2Enc - 1;
            if(colLetter2 == -1) colLetter2 = 4;
        }

            // if the two letters are on the same column
            // then we just shift to the top
        else if(colLetter1Enc == colLetter2Enc) {
            rowLetter1 = rowLetter1Enc - 1;
            colLetter1 = colLetter1Enc;
            if(rowLetter1 == -1) rowLetter1 = 4;

            rowLetter2 = rowLetter2Enc - 1;
            colLetter2 = colLetter2Enc;
            if(rowLetter2 == -1) rowLetter2 = 4;
        }

        // else we apply the main rule of the algorithm
        else {
            rowLetter1 = rowLetter1Enc;
            colLetter1 = colLetter2Enc;

            rowLetter2 = rowLetter2Enc;
            colLetter2 = colLetter1Enc;
        }

        // when the positions of the two original letters are known
        // we add those letters in the original text
        originalText[i] = matrix[5 * rowLetter1 + colLetter1];
        originalText[i+1] = matrix[5*rowLetter2 + colLetter2];


    }

    free(key); free(matrix);
    originalText[originalString.length] = '\0';
    originalString.text = originalText;
    return originalString;

}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************
/**
 * Fill the matrix according to the playfair algorithm method using the word given as a key
 * @param matrice
 * @param keyWord
 */
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

        if(letter != 'X') {
            // check it is not already in
            if(letterInMatrice[letter - 'A'] == 0) {

                // add in the matrix
                *(*matrice + indexColumn + 5*indexRow) = letter;

                // indicate that this letter is now in the matrix
                letterInMatrice[letter - 'A'] = 1;

                // increment index
                indexColumn++;
                if(indexColumn == 5) {
                    indexColumn = 0;
                    indexRow++;
                }
            }
        }
    }

    // now add the missing letters
    for(char c = 'A' ; c <= 'Z' ; c++) {

        if(c != 'X') {

                // add in the matrix if it is not yet
                if(letterInMatrice[c - 'A'] == 0) {
                    *(*matrice + indexColumn + 5*indexRow) = c;

                    // indicate that the letter was added in the matrix
                    letterInMatrice[c - 'A'] = 1;

                    // increment index
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
/**
 * Transform the text to upper case and add a parasite letter if the length is odd
 * @param originalString
 */
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
    // 1 : the letter is already configured
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

void showMatrix(char *matrix) {
    printf("***************** SHOW MATRIX *****************\n");
    
    for(int j = 0 ; j<5 ; j++) {
        for(int i=0 ; i<5 ; i++)
            printf("%c\t" , matrix[5*j + i]);
        printf("\n");
    }
    
}

