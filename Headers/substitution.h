//
// Created by TEAUDORS Mickael on 20/03/2018.
//

#ifndef CIPHER_SUBSTITUTION_H
#define CIPHER_SUBSTITUTION_H

#include "structures.h"
#include "files.h"
#include "global.h"

struct String substitutionEncrypt(struct String originalString , char *key);
struct String substitutionDecrypt(struct String encryptedString , char *key);
void initArrayLink(struct SubstitutionLink **link , char *fileName);

#endif //CIPHER_SUBSTITUTION_H
