//
// Created by TEAUDORS Mickael on 26/03/2018.
//

#include "../Headers/utilString.h"

void toUpperCase( char **word , int wordLength ) {

    for(int i=0 ; i<wordLength ; i++) {

        if(*(*word + i) >= 'a' && *(*word + i) <= 'z')
            *(*word + i) -= 32;

    }
}

int containsOnlyLetters( char *word , int wordLength) {

    for(int i=0 ; i<wordLength ; i++) {
        if(word[i] < 'A' || word[i] > 'z') return -1;

        if(word[i] > 'Z' && word[i] < 'a') return -1;
    }

    return 1;

}

void trim (char **text , int length) {
    int nbSpace = 0;

    for(int i=0 ; i<length ; i++) {
        if(*(*text + i) == ' ') {
            nbSpace++;

            for(int j=i ; j<length - 1 ; j++)
                *(*text + j) = *(*text + j + 1);

        }
    }

    *(*text + length - nbSpace) = '\0';
}
