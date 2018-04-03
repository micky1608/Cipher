/**
 * TEAUDORS Mickaël
 * This program has two main purposes.
 * The first is to decrypt a given text assuming that you have the key and you know the algorithm used to encrypt the text.
 * The second is to encrypt a text choosing the algoritm and the key.
 * The algorithms supported by this program : substitution, caesar, Vigenère, self-encryption, playfair
 */


#include "../Headers/main.h"
#include "../Headers/utilString.h"


/**
 * args[1] : choose between encryption and decryption
            * -e : encrypt
            * -d : decrypt
 * args[2] : choose the algorithm
            * -s : substitution
            * -c : cesar
            * -v : vigenere
            * -se : self-encryption
            * -p : playfair
 * args[3] : name of the file containing the original text, either the encrypted text if we want to decrypt or the original text if we want to encrypt.
 * args[4] : the key, either a figure (cesar), a word (vigenere) or the name of a file containing the substitution (substitution).
            * for the caeser algorithm, the key must be in the interval [0;25]. If it is not, the key used will be 'yourKey'%26
 * args[5] : (OPTIONAL) name of the file to display the result. If not specified, the result will be displayed on the console.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc , char *args[]) {

    /* ******************************** Check the arguments ********************************/

    if(argc < 5 || argc > 6)
        error("Arguments are not corrects ! Please read the documentation before launching the programm");

    /* ******************************** Initiate the output file ********************************/

    if(argc == 6)
        changeDefaultOutput(args[5]);
    else
        initOutput();

    /* ******************************** Recap Cipher information ********************************/

    struct InfoCipher infoCipher = initInfoCipherFromArgs(args);

    showRecapCipher(infoCipher);

    /* ******************************** Read the original file ********************************/

    struct String originalString = readFile(infoCipher.originalFileName);

    /* ******************************** Start the work ********************************/

    work(originalString , infoCipher.mode , infoCipher.algo , infoCipher.key);

    /* ******************************** Free resources ********************************/

    free(originalString.text);
    free(output);

    /* ******************************** Exit the program ********************************/

    exit(EXIT_SUCCESS);
}