//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#ifndef CIPHER_PLAYFAIR_H
#define CIPHER_PLAYFAIR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "utilString.h"
#include "error.h"
#include "global.h"

struct String playfairEncrypt (struct String, char*);
struct String playfairDecrypt (struct String, char*);
void initMatrix (char **matrice , char *keyWord);
void showMatrix(char matrix[5][5]);
void initOriginalString (struct String *originalString);
void posLetter(char *matrix , char letter1 , char letter2 , int *rowLetter1 , int *colLetter1 , int *rowLetter2 , int *colLetter2);

#endif //CIPHER_PLAYFAIR_H
