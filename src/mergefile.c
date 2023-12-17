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
#include <dirent.h>
#include <ctype.h>
#include "file.h"

void mergeFile(char *inputFileName, char *outputFileName){
    unsigned char *buffer = (unsigned char *) malloc((1048576) * sizeof(unsigned char)); // 1 MiB buffer
    FILE *mergedFile = fopen(outputFileName, "wb");
    FILE *splitFileOpen = NULL;
    unsigned long long splitFileSize = 0;
    unsigned long long i = 0;
    /*
     * Calculate the number of split files
     */
   /*
    struct dirent *dirEntry;
    DIR *dir = opendir(".");
    unsigned long long numberOfSplitFiles = 0;
    if (dir == NULL){
        fprintf(stderr, "Unable to open the working directory\n");
        exit(EXIT_FAILURE);
    } else{
        while(dirEntry = readdir(dir) != NULL){
            for(unsigned long long i = 0; i <= strlen(dirEntry->d_name); i++){
                if(dirEntry->d_name[i] == '.' && isdigit(dirEntry->d_name[i + 1] == 1)){
                    numberOfSplitFiles++;
                    break;
                }
            }  
        }
        closedir(dir);
    } 
    */
    //char *temp = (char *) malloc ((strlen(outputFileName) + numberOfSplitFiles + 1));
    /* for(unsigned long long i = 0; i < numberOfSplitFiles; i++){
        sprintf(temp, "%s.%llu", outputFileName, i);
        splitFileOpen = fopen(temp, "rb");
        if(splitFileOpen == NULL){
            break;
        }
        fseeko(splitFileOpen, 0, SEEK_END);
        splitFileSize = ftello(splitFileOpen);
        printf("%llu\n", splitFileSize);
        fseeko(splitFileOpen, 0, SEEK_SET);
        fread(buffer, splitFileSize, 1, splitFileOpen);
        fwrite(buffer, splitFileSize, 1, mergedFile);
        fclose(splitFileOpen);
    } */
    char *temp = (char *) malloc(strlen(inputFileName) + 50);
    while(1){
        sprintf(temp, "%s.%llu", inputFileName, i);
        splitFileOpen = fopen(temp, "rb");
        if(splitFileOpen == NULL){
            break;
        }
        splitFileSize = fileSize(splitFileOpen);
        printf("%llu\n", splitFileSize);
        fread(buffer, splitFileSize, 1, splitFileOpen);
        fwrite(buffer, splitFileSize, 1, mergedFile);
        fclose(splitFileOpen);
        i++;
    }
    free(buffer);
    free(temp);
    fclose(mergedFile);
}
