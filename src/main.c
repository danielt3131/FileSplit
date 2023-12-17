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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#define MAX_FILENAME_LENGTH 100
#define DEFAULT_CHUNK_SIZE 1048576
void fileSelection(char *inputFileName, char *outputFileName){
    
    // Allocating inputFileName from the heap
    //inputFileName = (char *) malloc(MAX_FILENAME_LENGTH);
    if (inputFileName == NULL){
        fprintf(stderr, "Unable to allocate memory. Now terminating\n");
        exit(EXIT_FAILURE);
    }
    // Allocationg outputFileName from the heap
    //outputFileName = (char *) malloc(MAX_FILENAME_LENGTH);
    if (outputFileName == NULL){
        free(inputFileName);
        fprintf(stderr, "Unable to allocate memory. Now terminating\n");
        exit(EXIT_FAILURE);
    }
    // Flush stdin
    fgets(inputFileName, MAX_FILENAME_LENGTH, stdin);
    printf("Please type in the name of the input file\n");
    fgets(inputFileName, MAX_FILENAME_LENGTH, stdin);
    // Remove LF
    inputFileName[(strlen(inputFileName) - 1)] = '\0';
    printf("Please type in the name of the output file\n");
    fgets(outputFileName, MAX_FILENAME_LENGTH, stdin);
    // Remove LF
    outputFileName[(strlen(outputFileName) - 1)] = '\0';
}

void chunkSelection(unsigned long long *chunkSize){
    printf("Enter in the size you want each file slice to be\n");
    scanf("%llu", chunkSize);
}

// CLI arguments -> InputFile, OutputFile, mode selector, FileChunkSize
int main (int argc, char **argv){
    char *inputFileName = (char *) malloc(MAX_FILENAME_LENGTH);
    char *outputFileName = (char *) malloc(MAX_FILENAME_LENGTH);
    unsigned long long fileChunkSize = DEFAULT_CHUNK_SIZE;
    if (argc > 3){
        inputFileName = (char *) malloc(strlen(argv[1]) + 1);
        if (inputFileName == NULL){
            fprintf(stderr, "Unable to allocate memory. Now terminating\n");
            return (EXIT_FAILURE);
        }
        outputFileName = (char *) malloc(strlen(argv[2]) + 1);
        if (outputFileName == NULL){
            free(inputFileName);
            fprintf(stderr, "Unable to allocate memory. Now terminating\n");
            return (EXIT_FAILURE);
        }
        strcpy(inputFileName, argv[1]);
        strcpy(outputFileName, argv[2]);
        if (argv > 4){
            fileChunkSize = atoll(argv[4]);
        }
        if (atoi(argv[3]) == 1){
            splitFile(inputFileName, outputFileName, fileChunkSize);
        } else if (atoi(argv[3]) == 2){
            mergeFile(inputFileName, outputFileName);
        } else{
            fprintf(stderr, "Wrong command line arguments\n");
            free(inputFileName);
            free(outputFileName);
            return (EXIT_FAILURE);
        }
    } else {
        printf("Welcome to file splitter\n");
        printf("Press 1 to split a file\n");
        printf("Press 2 to merge a file\n");
        printf("Press any other key to quit\n");
        char selector = getc(stdin);
        if(selector == '1'){
            fileSelection(inputFileName, outputFileName);
            chunkSelection(&fileChunkSize);
            if(splitFile(inputFileName, outputFileName, fileChunkSize) == 1){
                fprintf(stderr, "There was an error in splitFile\n");
            }
            free(inputFileName);
            free(outputFileName);
        } else if(selector == '2'){
            fileSelection(inputFileName, outputFileName);
            if(mergeFile(inputFileName, outputFileName) == 1){
                fprintf(stderr, "There was an error in mergeFile\n");
            }
            free(inputFileName);
            free(outputFileName);
        } else{
            printf("Try again\n");
            free(inputFileName);
            free(outputFileName);
        }
    }
    return 0;
}