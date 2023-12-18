/*
 * Copyright (c) 2023 Daniel J. Thompson.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 or later.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file.h"
#include <limits.h>

int mergeFile(char *inputFileName, char *outputFileName){
    size_t tempSize = strlen(inputFileName) + 50;
    char *temp = (char *) malloc(tempSize);
    if(temp == NULL){
        return(EXIT_FAILURE);
    }
    snprintf(temp, tempSize, "%s.0", inputFileName);
    // Calculate the size of the needed buffer by opening the first file slice, then closing the file slice
    FILE *splitFileOpen = fopen(temp, "rb");
    if (splitFileOpen == NULL){
        free(temp);
        return(EXIT_FAILURE);
    }
    unsigned long long bufferSize = fileSize(splitFileOpen);
    fclose(splitFileOpen);
    unsigned char *buffer = (unsigned char *) malloc((bufferSize) * sizeof(unsigned char));
    if(buffer == NULL){
        free(temp);
        return(EXIT_FAILURE);
    }
    FILE *mergedFile = fopen(outputFileName, "wb");
    if (mergedFile == NULL){
        free(temp);
        free(buffer);
        return(EXIT_FAILURE);
    }
    unsigned long long splitFileSize = 0;
    unsigned long long i = 0;
    while(1){
        if (i == ULLONG_MAX){
            fprintf(stderr, "The number of file segments to merge have exceeded the 64 bit unsigned limit\n");
            fprintf(stderr, "TLDR -> too fucken many file segments to merge.  Now terminating\n");
            fclose(mergedFile);
            free(temp);
            free(buffer);
            return(EXIT_FAILURE);
        }
        snprintf(temp, tempSize, "%s.%llu", inputFileName, i);
        splitFileOpen = fopen(temp, "rb");
        if(splitFileOpen == NULL){
            break;
        }
        splitFileSize = fileSize(splitFileOpen);
        // printf("%llu\n", splitFileSize);
        fread(buffer, splitFileSize, 1, splitFileOpen);
        fwrite(buffer, splitFileSize, 1, mergedFile);
        fclose(splitFileOpen);
        i++;
    }
    free(buffer);
    free(temp);
    fclose(mergedFile);
    return(EXIT_SUCCESS);
}
