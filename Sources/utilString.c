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
