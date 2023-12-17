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
#define MAX_FILENAME_LENGTH 100
#define DEFAULT_CHUNK_SIZE 1048576
#define ERROR_OUTPUT 1
#define SPLIT_FILE 1
#define MERGE_FILE 2
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

void completedMergeMsg(char *inputFileName, char *outputFileName){
    clear();
    printw("The file(s) of %s have been merged into %s\n", inputFileName, outputFileName);
    refresh();
    free(inputFileName);
    free(outputFileName);
    sleep(5);
    endwin();
}

void completedSplitMsg(char *inputFileName, char *outputFileName){
    clear();
    printw("The file of %s have been splited into %s\n", inputFileName, outputFileName);
    refresh();
    free(inputFileName);
    free(outputFileName);
    sleep(5);
    endwin();
}

void errorMsg(short type, char *inputFileName, char *outputFileName){
    switch (type){
    case SPLIT_FILE:
        attron(COLOR_PAIR(ERROR_OUTPUT));
        printw("There was an error in splitFile\n");
        refresh();
        sleep(5);
        free(inputFileName);
        free(outputFileName);
        endwin();
        break;
    case MERGE_FILE:
        attron(COLOR_PAIR(ERROR_OUTPUT));
        printw("There was an error in mergeFile\n");
        refresh();
        sleep(5);
        free(inputFileName);
        free(outputFileName);
        endwin();
        break;
    default:
        break;
    }
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
        if (argc > 4){
            fileChunkSize = atoll(argv[4]);
        }
        if (atoi(argv[3]) == SPLIT_FILE){
            splitFile(inputFileName, outputFileName, fileChunkSize);
        } else if (atoi(argv[3]) == MERGE_FILE){
            mergeFile(inputFileName, outputFileName);
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
                // attron(COLOR_PAIR(ERROR_OUTPUT));
                // printw("There was an error in mergeFile\n");
                // refresh();
                // sleep(5);
                // free(inputFileName);
                // free(outputFileName);
                // endwin();
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