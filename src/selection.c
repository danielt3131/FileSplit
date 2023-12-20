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
#include "file.h"
#include "message.h"
#define MAX_FILENAME_LENGTH 512
#define DEFAULT_CHUNK_SIZE 1048576
#define ERROR_OUTPUT 1
#define SPLIT_FILE 1
#define MERGE_FILE 2


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
int modeSelection(){
    // Init ncurses
    initscr();
    start_color();
    if(has_colors() == false){
        endwin();
        fprintf(stderr, "Terminal doesn't support colors\n");
        return(EXIT_FAILURE);
    }
    char *inputFileName = (char *) malloc(MAX_FILENAME_LENGTH);
    char *outputFileName = (char *) malloc(MAX_FILENAME_LENGTH);
    unsigned long long fileChunkSize = DEFAULT_CHUNK_SIZE;
    init_pair(ERROR_OUTPUT, COLOR_RED, COLOR_BLACK);
    printw("Welcome to file splitter\n");
    printw("Press 1 to split a file\n");
    printw("Press 2 to merge a file\n");
    printw("Press any other key to quit\n");
    refresh();
    char selector = getch();
    clear();
    if(selector == '1'){
        fileSelection(inputFileName, outputFileName);
        chunkSelection(&fileChunkSize);
        if(splitFile(inputFileName, outputFileName, fileChunkSize) == 1){
            errorMsg(1, inputFileName, outputFileName);
        } else {
            completedSplitMsg(inputFileName, outputFileName);
        }
    } else if(selector == '2'){
        fileSelection(inputFileName, outputFileName);
        if(mergeFile(inputFileName, outputFileName) == 1){
            errorMsg(2, inputFileName, outputFileName);
        } else {
            completedMergeMsg(inputFileName, outputFileName);
        }
    } else{
        printw("Try again\n");
        refresh();
        free(inputFileName);
        free(outputFileName);
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}