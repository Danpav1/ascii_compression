#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

/*
* @author Daniel Pavenko
* @date 04/08/24
* Programming assignment for OS class that zips files.
*/

#define DATA_LIMIT 1048576 // arbitrarly large size just in case

char* dynamicBuffer = NULL; // buffer for file contents
size_t bufferSize = 0; // current size of the buffer

// func. prototypes
void compress(char* fileData, size_t length);
void fileParser(char *fileName);

// main
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    // process each file
    for (int i = 1; i < argc && argv[i] != NULL; i++) {
        fileParser(argv[i]);
    }

    // now compress the concatenated content
    if (dynamicBuffer) {
        compress(dynamicBuffer, bufferSize);
        free(dynamicBuffer);
    }

    return 0;
}

// parses all files and adds them to buffer
void fileParser(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file in fileParser");
	exit(1);
    }

    char tempData[DATA_LIMIT]; // temporary buffer for reading
    size_t bytesRead;
    while ((bytesRead = fread(tempData, sizeof(char), DATA_LIMIT - 1, file)) > 0) {
        // resize the dynamicBuffer to accommodate new content
        char *newBuffer = realloc(dynamicBuffer, bufferSize + bytesRead);
        if (!newBuffer) {
            printf("Failed to allocate memory in fileParser");
            fclose(file);
            free(dynamicBuffer);
            exit(1);
        }
        dynamicBuffer = newBuffer;

        // append new content to dynamicBuffer
        memcpy(dynamicBuffer + bufferSize, tempData, bytesRead);
        bufferSize += bytesRead;
    }

    // ensure theres no extra null character
    if (bufferSize > 0 && dynamicBuffer[bufferSize - 1] == '\0') {
        bufferSize--;
    }

    fclose(file);
}

// handles and prints compression to ascii
void compress(char* fileData, size_t length) {
    if (fileData == NULL || length == 0) return; // check for NULL pointer or empty length

    int matches = 1; // start with one match
    char currentChar = *fileData; // current character for comparison

    // iterate through data until reaching the end
    for (size_t i = 1; i < length; i++) {
        if (fileData[i] == currentChar) {
            matches++; // increment match count if the same
        } else {
            // write the 4-byte integer in binary format
            fwrite(&matches, sizeof(int), 1, stdout);
            // write the single character
            fwrite(&currentChar, sizeof(char), 1, stdout);

            // reset for the next character sequence
            currentChar = fileData[i];
            matches = 1;
        }
    }

    // After the loop, handle the last character sequence
    fwrite(&matches, sizeof(int), 1, stdout);
    fwrite(&currentChar, sizeof(char), 1, stdout);
}
