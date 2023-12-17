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
#include <ncurses.h>
#include <stdlib.h>
#include "selection.h"
#define MAX_FILENAME_LENGTH 100
#define DEFAULT_CHUNK_SIZE 1048576
#define ERROR_OUTPUT 1

void fileSelection(char *inputFileName, char *outputFileName){
    if (inputFileName == NULL){
        fprintf(stderr, "Unable to allocate memory. Now terminating\n");
        exit(EXIT_FAILURE);
    }
    if (outputFileName == NULL){
        free(inputFileName);
        fprintf(stderr, "Unable to allocate memory. Now terminating\n");
        exit(EXIT_FAILURE);
    }
    refresh();
    printw("Please type in the name of the input file\n");
    refresh();
    getnstr(inputFileName, MAX_FILENAME_LENGTH);
    clear();
    printw("Please type in the name of the output file\n");
    refresh();
    getnstr(outputFileName, MAX_FILENAME_LENGTH);
    clear();
}

void chunkSelection(unsigned long long *chunkSize){
    printw("Do you want to set the size for each file slice the default value is %d\n", DEFAULT_CHUNK_SIZE);
    printw("If so then press 1 otherwise press any other key\n");
    char selector = getch();
    if (selector == '1'){
        printw("Enter in the size you want each file slice to be\n");
        scanw("%llu", chunkSize);
    }
    clear();
}