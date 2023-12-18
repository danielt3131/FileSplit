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
#include <unistd.h>
#include <ncurses.h>
#include "file.h"
#include "message.h"
#include "selection.h"
#define MAX_FILENAME_LENGTH 512
#define DEFAULT_CHUNK_SIZE 1048576
#define ERROR_OUTPUT 1
#define SPLIT_FILE 1
#define MERGE_FILE 2

// CLI arguments -> InputFile, OutputFile, mode selector, FileChunkSize
int main (int argc, char **argv){
    char *inputFileName = (char *) malloc(MAX_FILENAME_LENGTH);
    char *outputFileName = (char *) malloc(MAX_FILENAME_LENGTH);
    unsigned long long fileChunkSize = DEFAULT_CHUNK_SIZE;
    if (argc > 3){
        if (inputFileName == NULL){
            fprintf(stderr, "Unable to allocate memory. Now terminating\n");
            return (EXIT_FAILURE);
        }
        if (outputFileName == NULL){
            free(inputFileName);
            fprintf(stderr, "Unable to allocate memory. Now terminating\n");
            return (EXIT_FAILURE);
        }
        strncpy(inputFileName, argv[1], MAX_FILENAME_LENGTH);
        strncpy(outputFileName, argv[2], MAX_FILENAME_LENGTH);
        if (argc > 4){
            fileChunkSize = atoll(argv[4]);
        }
        if (atoi(argv[3]) == SPLIT_FILE){
            splitFile(inputFileName, outputFileName, fileChunkSize);
            free(inputFileName);
            free(outputFileName);
            return (EXIT_SUCCESS);
        } else if (atoi(argv[3]) == MERGE_FILE){
            mergeFile(inputFileName, outputFileName);
            free(inputFileName);
            free(outputFileName);
            return (EXIT_SUCCESS);
        } else{
            fprintf(stderr, "Wrong command line arguments\n");
            free(inputFileName);
            free(outputFileName);
            return (EXIT_FAILURE);
        }
    } else {
        // Init ncurses
        initscr();
        start_color();
        if(has_colors() == false){
            endwin();
            printf("Terminal doesn't support colors\n");
            exit(EXIT_FAILURE);
        }
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
            endwin();
        }
    }
    return 0;
}