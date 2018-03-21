//
// Created by TEAUDORS Mickael on 20/03/2018.
//


#include "../Headers/files.h"

/**
 * Get a the text of a file in a structure.
 * @param fileName
 * @return
 */
struct String readFile(char *fileName) {

    struct String stringText;
    char *text;

    int fd = open(fileName , O_RDONLY);

    if(fd == -1) error("Can't open file for reading");

    size_t size = fileSize(fileName);

    text = (char*)malloc(sizeof(char)*(size + 1));

    int nbRead = read(fd , text , size);

    fprintf(output , "\nINFO READING : File size : %d\tNumber of read characters : %d\n" , size , nbRead);

    text[size] = '\0';

    stringText.text = text;
    stringText.length = nbRead;

    return stringText;
}

/**
 * Set a file as the default output file.
 * @param fileName
 */
void changeDefaultOutput (char *fileName) {

    // open the file
    int fd = open(fileName , O_WRONLY | O_TRUNC);

    if(fd == -1) error("Don't manage to open the file for the redirection of the output");

    output = fdopen(fd , "w");

    if(output == NULL) error("The file chosen to redirect the output can't be converted correctly");
}

/**
 * This function will be called if the user doesn't specify any file to redirect the output.
 * In this case, we just initiate the output by opening the standard output file.
 */
void initOutput() {

    output = fdopen(1 , "w");

    if(output == NULL) error("The file chosen to redirect the output can't be converted correctly");
}

/**
 * Get the size of a file using its name.
 * @param fileName
 * @return
 */
size_t fileSize (char *fileName) {

    struct stat infoFile;

    int fd = open(fileName , O_RDONLY);

    if(fd == -1) error("Can't get the size of the file");

    if( fstat(fd , &infoFile) != 0 )
        error("Can't get the stat structure");

    close(fd);

    return infoFile.st_size;
}



