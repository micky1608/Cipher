//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#include "../Headers/substitution.h"


struct String substitutionEncrypt(struct String originalString , char *key) {
    //TODO
}



//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************


struct String substitutionDecrypt(struct String encryptedString , char *key) {
    //TODO
}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

/**
 * Init an array of the substitutions between all the letters using the corresponding file.
 * @param link a pointer towards the array we want to init
 * @param fileName the name of the file containing the substitutions. This file must be built like this :
 *          each line contains the original letter, a colon and the encrypted letter associated.
 *          For example( A:E ) means that the A is ciphered with the E.
 */
void initArrayLink(struct SubstitutionLink **link , char *fileName) {
    //TODO
}

//**********************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************

int checkArrayLink (struct SubstitutionLink link) {
    //TODO
}




