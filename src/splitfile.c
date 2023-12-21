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
#include "file.h"

int splitFile(char *inputFileName, char *outputFileName, unsigned long long fileChunkSize){
    unsigned char *buffer = (unsigned char *) malloc((fileChunkSize) * sizeof(unsigned char));
    if(buffer == NULL){
        fprintf(stderr, "Unable to allocate memory\n");
        return(ALLOCATION_ERROR);
    }
    FILE *inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL){
        fprintf(stderr, "Unable to locate the file to split\n");
        free(buffer);
        return(FILE_READ_ERROR);
    }
    unsigned long long inputFileSize = fileSize(inputFile);
    unsigned long long numberOfChunks = inputFileSize / fileChunkSize;
    size_t tempSize = strlen(outputFileName) + numberOfChunks + 2;
    char *temp = (char *) malloc(tempSize);
    if(temp == NULL){
        fprintf(stderr, "Unable to allocate memory\n");
        free(buffer);
        return(ALLOCATION_ERROR);
    }
    unsigned long long i;
    for (i = 0; i < numberOfChunks; i++){
        fread(buffer, fileChunkSize, 1, inputFile);
        snprintf(temp, tempSize, "%s.%llu", outputFileName, i);
        FILE *output = fopen(temp, "wb");
        fwrite(buffer, fileChunkSize, 1, output);
        fclose(output);
        // printf("%llu\n", i);
    }
    // printf("%llu\n", (inputFileSize % fileChunkSize));
    // printf("%llu\n", (inputFileSize - (numberOfChunks * fileChunkSize)));
    if (inputFileSize % fileChunkSize != 0){
        unsigned long long remainderChunkSize = inputFileSize % fileChunkSize;
        fread(buffer, remainderChunkSize, 1, inputFile);
        snprintf(temp, tempSize, "%s.%llu", outputFileName, i);
        FILE *output = fopen(temp, "wb");
        fwrite(buffer, remainderChunkSize, 1, output);
        fclose(output);
    }
    fclose(inputFile);
    free(buffer);
    free(temp);
    return(EXIT_SUCCESS);
}
